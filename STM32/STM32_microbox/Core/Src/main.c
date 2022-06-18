/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "network.h"
#include "network_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern ApplicationTypeDef Appli_state;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
__attribute__((section(".ccmram"))) DIR dir;
__attribute__((section(".ccmram"))) FILINFO fno;
__attribute__((section(".ccmram"))) char folder[11];
__attribute__((section(".ccmram"))) char buf[266];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);
static void LCD_Config(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */
  // Variables
  ai_error ai_err;
  ai_i32 nbatch;
  FRESULT res;
  FIL file;
  UINT br;
  uint32_t Tinf1;
  uint32_t Tinf2;
  uint32_t nn_inference_time;
  uint32_t tot_inference_time = 0;
  // Specify classes
  const char* classes_folders[] = {"false", "true"};
  char csv_full[BTR];
  char* csv_line[SERIES_LENGTH + 2];
  char* X_test_str[SERIES_LENGTH * CHANNELS];
  double X_test[SERIES_LENGTH * CHANNELS];
  float y_prob[2];
  int y_pred;
  int y_true = 0;
  int sample = 0;
  int tn = 0;
  int fp = 0;
  int fn = 0;
  int tp = 0;
  int done = 0;

  // Chunk of memory used to hold intermediate values for neural network
  AI_ALIGNED(4) ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];

  // Buffers used to store input and output tensors
  AI_ALIGNED(4) ai_i8 in_data[AI_NETWORK_IN_1_SIZE_BYTES];
  AI_ALIGNED(4) ai_i8 out_data[AI_NETWORK_OUT_1_SIZE_BYTES];

  // Pointer to the model
  ai_handle network = AI_HANDLE_NULL;

  // Initialize wrapper structs that hold pointers to data and info about the data (tensor height, width, channels)
  ai_buffer ai_input[AI_NETWORK_IN_NUM] = AI_NETWORK_IN;
  ai_buffer ai_output[AI_NETWORK_OUT_NUM] = AI_NETWORK_OUT;

  // Set working memory and get weights/biases from model
  ai_network_params ai_params = {
		  AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get()),
		  AI_NETWORK_DATA_ACTIVATIONS(activations)
  };

  // Set pointers wrapper structs to data buffers
  ai_input[0].n_batches = 1;
  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].n_batches = 1;
  ai_output[0].data = AI_HANDLE_PTR(out_data);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_SPI5_Init();
  MX_USART1_UART_Init();
  MX_USB_HOST_Init();
  MX_FATFS_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
  // Start
  sprintf(buf, "LCD config");
  LCD_Config();
  sprintf(buf, "LCD config OK");
  BSP_LCD_DisplayStringAtLine(0,(uint8_t*)"STM32F429I-DISC1");
  BSP_LCD_DisplayStringAtLine(1,(uint8_t*)"Microbox");
  BSP_LCD_DisplayStringAtLine(2,(uint8_t*)"From USB Flash Disk");
  HAL_Delay(2000);
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  // Create instance of neural network
  ai_err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (ai_err.type != AI_ERROR_NONE)
  {
	  sprintf(buf, "Error: could not create NN instance");
	  while(1);
  }

  // Initialize neural network
  if (!ai_network_init(network, &ai_params))
  {
	  sprintf(buf, "Error: could not initialize NN");
	  while(1);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/* USER CODE END WHILE */
	MX_USB_HOST_Process();

	/* USER CODE BEGIN 3 */
	// Handler of application state
	switch(Appli_state){
		case APPLICATION_READY:
			sprintf(buf, "READY");

			// Fill input buffer if there are still series to classify
			if (y_true<2)
			{
				sprintf(buf, "Test: %d/%d    ", sample, N_SAMPLES);
				BSP_LCD_DisplayStringAtLine(0,(uint8_t*)buf);
        // For all the folders
				for (int folders=0;folders<2;folders++)
				{
					sprintf(folder,"/microbox/%s", classes_folders[folders]);
          // If folder found, check for file, open it, read it, and close it
					if (f_chdir(folder)==FR_OK)
					{
						res = f_findfirst(&dir, &fno, "","*.csv");
						while ((res == FR_OK) && (fno.fname[0]))
						{
							sprintf(buf, "Open file %s", fno.fname);
							if (f_open(&file, fno.fname, FA_READ) != FR_OK)
							{
								sprintf(buf, "Open file error");
							}
							f_read(&file, &csv_full, BTR, &br);
							if (br!=BTR)
							{
								sprintf(buf, "Read file error");
							}
							f_close (&file);
              // Divide the file read into tokens, first lines, then values
							int j = 0;
							char* token = strtok(csv_full, "\r\n");
							while( token != NULL )
							{
								csv_line[j]=token;
								j ++;
								token = strtok(NULL, "\r\n");
							}
							int k = 0;
							for (int i = 1;i<SERIES_LENGTH + 1;i++)
							{
								char* token2 = strtok(csv_line[i], ",");
								while( token2 != NULL )
								{
									X_test_str[k]=token2;
									k ++;
									token2 = strtok(NULL, ",");
								}
							}
              // Convert values to double
							for (int i = 0;i<SERIES_LENGTH*CHANNELS;i++)
							{
								X_test[i] = strtod(X_test_str[i], NULL);
							}
              // Fill input buffer for neural network
							for (uint32_t i = 0; i < AI_NETWORK_IN_1_SIZE; i++)
							{
								((ai_float *)in_data)[i] = (ai_float)X_test[i];
							}

							// Perform inference
							Tinf1 = HAL_GetTick();
							nbatch = ai_network_run(network, &ai_input[0], &ai_output[0]);
							if (nbatch != 1)
							{
								sprintf(buf, "Error: could not run inference");
							}
							Tinf2 = HAL_GetTick();
              // Compute inference time
							nn_inference_time = ((Tinf2>Tinf1)?(Tinf2-Tinf1):((1<<24)-Tinf1+Tinf2));
							tot_inference_time = tot_inference_time + nn_inference_time;

							// Read output of neural network
							y_prob[0] = ((float *)out_data)[0];
							y_prob[1] = ((float *)out_data)[1];

							// Make prediction
							if (y_prob[0] > y_prob[1])
							{
								y_pred = 0;
							}
							else
							{
								y_pred = 1;
							}

							// Count tn, fp, fn, tp
							if ((y_pred == y_true) && (y_true == 0))
							{
								tn ++;
							}
							else if ((y_pred == y_true) && (y_true == 1))
							{
								tp ++;
							}
							else if ((y_pred != y_true) && (y_true == 0))
							{
								fp ++;
							}
							else
							{
								fn ++;
							}

							// Print metrics and inference time (milliseconds)
							sample ++;
							sprintf(buf, "Test: %d/%d    ", sample, N_SAMPLES);
							BSP_LCD_DisplayStringAtLine(0,(uint8_t*)buf);
							sprintf(buf, "Accuracy: %f", (float)(tn + tp)/(float)(tn + tp + fn + fp));
							BSP_LCD_DisplayStringAtLine(2,(uint8_t*)buf);
							sprintf(buf, "Inf. time: %ldms", nn_inference_time);
							BSP_LCD_DisplayStringAtLine(4,(uint8_t*)buf);
							sprintf(buf, "True negatives: %d", tn);
							BSP_LCD_DisplayStringAtLine(6,(uint8_t*)buf);
							sprintf(buf, "False positives: %d", fp);
							BSP_LCD_DisplayStringAtLine(7,(uint8_t*)buf);
							sprintf(buf, "False negatives: %d", fn);
							BSP_LCD_DisplayStringAtLine(8,(uint8_t*)buf);
							sprintf(buf, "True positives: %d", tp);
							BSP_LCD_DisplayStringAtLine(9,(uint8_t*)buf);

							res = f_findnext(&dir,&fno);
						}
						f_closedir(&dir);
						sprintf(buf, "Finished %d",res);
					}
					y_true ++;
				}
			}
			else
			{
				// Compute precision, recall, F1-score
				done = 1;
				BSP_LCD_DisplayStringAtLine(0,(uint8_t*)"Test done      ");
				sprintf(buf, "Tot. time: %.3fs", (float)(tot_inference_time)/1000);
				BSP_LCD_DisplayStringAtLine(4,(uint8_t*)buf);
				sprintf(buf, "Precision: %f", (float)tp/(float)(tp+fp));
				BSP_LCD_DisplayStringAtLine(11,(uint8_t*)buf);
				sprintf(buf, "Recall: %f", (float)tp/(float)(tp+fn));
				BSP_LCD_DisplayStringAtLine(12,(uint8_t*)buf);
				sprintf(buf, "F1-score: %f", 2*(float)tp/(float)(tp+fp)*(float)tp/(float)(tp+fn)/((float)tp/(float)(tp+fp)+(float)tp/(float)(tp+fn)));
				BSP_LCD_DisplayStringAtLine(13,(uint8_t*)buf);
			}
		break;
		case APPLICATION_IDLE:
			sprintf(buf, "IDLE");
      // Application is ready but there's no USB connected
			BSP_LCD_DisplayStringAtLine(0,(uint8_t*)"Waiting for USB");
		break;
		case APPLICATION_DISCONNECT:
			sprintf(buf, "DISCONNECT");

			// If test is not finished while USB is disconnected, reset variables
			if (done == 0)
			{
				y_true = 0;
				sample = 0;
				tn = 0;
				fp = 0;
				fn = 0;
				tp = 0;
				for (int i=2;i<10;i++)
				{
					BSP_LCD_ClearStringLine(i);
				}
				BSP_LCD_DisplayStringAtLine(0,(uint8_t*)"Waiting for USB");
			}
		break;
		default:
		break;
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void LCD_Config(void)
{
	/* Initialize the LCD */
	BSP_LCD_Init();

	/* Background Layer Initialization */
	BSP_LCD_LayerDefaultInit(0, LCD_BUFFER);

	/* Set Foreground Layer */
	BSP_LCD_SelectLayer(0);

	/* Enable the LCD */
	BSP_LCD_DisplayOn();

	/* Clear the LCD Background layer */
	BSP_LCD_SetTransparency(0,255);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
