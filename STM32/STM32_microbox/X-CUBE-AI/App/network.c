/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon May 16 23:22:51 2022
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 1
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "e2376d7cf57ac58b873d77ef58d3ea82"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.1.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon May 16 23:22:51 2022"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv1d_11_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv1d_10_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv1d_9_scratch0_array;   /* Array #2 */
AI_STATIC ai_array dense_3_bias_array;   /* Array #3 */
AI_STATIC ai_array dense_3_weights_array;   /* Array #4 */
AI_STATIC ai_array conv1d_11_bias_array;   /* Array #5 */
AI_STATIC ai_array conv1d_11_weights_array;   /* Array #6 */
AI_STATIC ai_array conv1d_10_bias_array;   /* Array #7 */
AI_STATIC ai_array conv1d_10_weights_array;   /* Array #8 */
AI_STATIC ai_array conv1d_9_bias_array;   /* Array #9 */
AI_STATIC ai_array conv1d_9_weights_array;   /* Array #10 */
AI_STATIC ai_array input_0_output_array;   /* Array #11 */
AI_STATIC ai_array conv1d_9_output_array;   /* Array #12 */
AI_STATIC ai_array conv1d_10_output_array;   /* Array #13 */
AI_STATIC ai_array conv1d_11_output_array;   /* Array #14 */
AI_STATIC ai_array dense_3_output_array;   /* Array #15 */
AI_STATIC ai_array dense_3_nl_output_array;   /* Array #16 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv1d_11_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv1d_10_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv1d_9_scratch0;   /* Tensor #2 */
AI_STATIC ai_tensor dense_3_bias;   /* Tensor #3 */
AI_STATIC ai_tensor dense_3_weights;   /* Tensor #4 */
AI_STATIC ai_tensor conv1d_11_bias;   /* Tensor #5 */
AI_STATIC ai_tensor conv1d_11_weights;   /* Tensor #6 */
AI_STATIC ai_tensor conv1d_10_bias;   /* Tensor #7 */
AI_STATIC ai_tensor conv1d_10_weights;   /* Tensor #8 */
AI_STATIC ai_tensor conv1d_9_bias;   /* Tensor #9 */
AI_STATIC ai_tensor conv1d_9_weights;   /* Tensor #10 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #11 */
AI_STATIC ai_tensor conv1d_9_output;   /* Tensor #12 */
AI_STATIC ai_tensor conv1d_10_output;   /* Tensor #13 */
AI_STATIC ai_tensor conv1d_11_output;   /* Tensor #14 */
AI_STATIC ai_tensor dense_3_output;   /* Tensor #15 */
AI_STATIC ai_tensor dense_3_nl_output;   /* Tensor #16 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv1d_9_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv1d_10_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv1d_11_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_3_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_3_nl_chain;   /* Chain #4 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv1d_9_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv1d_10_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv1d_11_layer; /* Layer #2 */
AI_STATIC ai_layer_dense dense_3_layer; /* Layer #3 */
AI_STATIC ai_layer_nl dense_3_nl_layer; /* Layer #4 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_11_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_10_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 250, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_9_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2000, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 50, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_11_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_11_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2500, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_10_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 50, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_10_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10000, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_9_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 100, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_9_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3000, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 900, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_9_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1400, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_10_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 100, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv1d_11_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_nl_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_11_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 25, 1, 1), AI_STRIDE_INIT(4, 4, 4, 100, 100),
  1, &conv1d_11_scratch0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_10_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 50, 1, 5), AI_STRIDE_INIT(4, 4, 4, 200, 200),
  1, &conv1d_10_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_9_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 1, 20), AI_STRIDE_INIT(4, 4, 4, 400, 400),
  1, &conv1d_9_scratch0_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_3_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 25, 2, 1, 1), AI_STRIDE_INIT(4, 4, 100, 200, 200),
  1, &dense_3_weights_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_11_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 25, 1, 1), AI_STRIDE_INIT(4, 4, 4, 100, 100),
  1, &conv1d_11_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_11_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 50, 1, 2, 25), AI_STRIDE_INIT(4, 4, 200, 200, 400),
  1, &conv1d_11_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_10_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 50, 1, 1), AI_STRIDE_INIT(4, 4, 4, 200, 200),
  1, &conv1d_10_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_10_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 100, 1, 2, 50), AI_STRIDE_INIT(4, 4, 400, 400, 800),
  1, &conv1d_10_weights_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_9_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 1, 1), AI_STRIDE_INIT(4, 4, 4, 400, 400),
  1, &conv1d_9_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_9_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 1, 10, 100), AI_STRIDE_INIT(4, 4, 12, 12, 120),
  1, &conv1d_9_weights_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 300), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &input_0_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_9_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 1, 14), AI_STRIDE_INIT(4, 4, 4, 400, 400),
  1, &conv1d_9_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_10_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 50, 1, 2), AI_STRIDE_INIT(4, 4, 4, 200, 200),
  1, &conv1d_10_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv1d_11_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 25, 1, 1), AI_STRIDE_INIT(4, 4, 4, 100, 100),
  1, &conv1d_11_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_3_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_nl_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_3_nl_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv1d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv1d_9_weights, &conv1d_9_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_9_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv1d_9_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv1d_10_layer, AI_STATIC,
  .tensors = &conv1d_9_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(1, 20), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 20), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv1d_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv1d_10_weights, &conv1d_10_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_10_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv1d_10_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv1d_11_layer, AI_STATIC,
  .tensors = &conv1d_10_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(1, 5), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 5), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv1d_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv1d_11_weights, &conv1d_11_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_11_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv1d_11_layer, 6,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &dense_3_layer, AI_STATIC,
  .tensors = &conv1d_11_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(1, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv1d_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_3_weights, &dense_3_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_3_layer, 9,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_3_nl_layer, AI_STATIC,
  .tensors = &dense_3_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_3_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_3_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_3_nl_layer, 9,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_3_nl_layer, AI_STATIC,
  .tensors = &dense_3_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 62908, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 13600, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &dense_3_nl_output),
  &conv1d_9_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv1d_11_scratch0_array.data = AI_PTR(activations + 0);
    conv1d_11_scratch0_array.data_start = AI_PTR(activations + 0);
    conv1d_10_scratch0_array.data = AI_PTR(activations + 0);
    conv1d_10_scratch0_array.data_start = AI_PTR(activations + 0);
    conv1d_9_scratch0_array.data = AI_PTR(activations + 0);
    conv1d_9_scratch0_array.data_start = AI_PTR(activations + 0);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv1d_9_output_array.data = AI_PTR(activations + 8000);
    conv1d_9_output_array.data_start = AI_PTR(activations + 8000);
    conv1d_10_output_array.data = AI_PTR(activations + 1000);
    conv1d_10_output_array.data_start = AI_PTR(activations + 1000);
    conv1d_11_output_array.data = AI_PTR(activations + 100);
    conv1d_11_output_array.data_start = AI_PTR(activations + 100);
    dense_3_output_array.data = AI_PTR(activations + 0);
    dense_3_output_array.data_start = AI_PTR(activations + 0);
    dense_3_nl_output_array.data = AI_PTR(NULL);
    dense_3_nl_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_3_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_3_bias_array.data = AI_PTR(weights + 62900);
    dense_3_bias_array.data_start = AI_PTR(weights + 62900);
    dense_3_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_3_weights_array.data = AI_PTR(weights + 62700);
    dense_3_weights_array.data_start = AI_PTR(weights + 62700);
    conv1d_11_bias_array.format |= AI_FMT_FLAG_CONST;
    conv1d_11_bias_array.data = AI_PTR(weights + 62600);
    conv1d_11_bias_array.data_start = AI_PTR(weights + 62600);
    conv1d_11_weights_array.format |= AI_FMT_FLAG_CONST;
    conv1d_11_weights_array.data = AI_PTR(weights + 52600);
    conv1d_11_weights_array.data_start = AI_PTR(weights + 52600);
    conv1d_10_bias_array.format |= AI_FMT_FLAG_CONST;
    conv1d_10_bias_array.data = AI_PTR(weights + 52400);
    conv1d_10_bias_array.data_start = AI_PTR(weights + 52400);
    conv1d_10_weights_array.format |= AI_FMT_FLAG_CONST;
    conv1d_10_weights_array.data = AI_PTR(weights + 12400);
    conv1d_10_weights_array.data_start = AI_PTR(weights + 12400);
    conv1d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv1d_9_bias_array.data = AI_PTR(weights + 12000);
    conv1d_9_bias_array.data_start = AI_PTR(weights + 12000);
    conv1d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv1d_9_weights_array.data = AI_PTR(weights + 0);
    conv1d_9_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1064055,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}


#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

