# Supervised Learning Algorithms for Car Accident Classification
This repository contains the internship work for master's degree in Computer and Automation Engineering at Università Politecnica delle Marche (Ancona, Italy). It consists in a comparison of different methods for car accident classification using convolutional neural networks, based on accelerometers' recordings datasets from in-vehicle inertial sensors (accelerometers). The repository also contains two applications for edge-ai on STM32 microcontroller.

## Datasets
The recordings have been generated by two different devices: Microbox and Infobox; each recording is created whenever the devices detect, according to their decision algorithm, a crash.

- The Infobox device has 3 hardware revisions. The data have been preprocessed to generate series of 1200 samples along 3 seconds (400 Hz). The Infobox series take into consideration only x and y axes. Infobox devices also store pre-crash sensors values, in addition to on-crash and post-crash data.

- The Microbox device has a single hardware revision. The Microbox series have a length of 300 samples along 3 seconds (100 Hz), and take into consideration all three axes (x, y and z). Microbox only stores on-crash and post-crash sensor data. They do not provide pre-crash information.

## Notebooks
The repository contains the colab notebooks used to train and test the convolutional neural networks. In each notebook, must be specified in the cell commented as "Clone the repository" the clone command to a repository containing the data (or another way to get the data). The cloned repository must have the following structure:

```
fc_crash-detection
└── crash-dataset-csv
    ├── infobox
    │   ├── true
    │   │   └── *.csv
    │   └── false
    │       └── *.csv
    └── microbox
        ├── true
        │   └── *.csv
        └── false
            └── *.csv
```
The names and structure can be modified, assuming that the dataset path in the cell "Set params" is modified accordingly. In that cell must be also specified the other parameters, such as the results path, the name of the model, the path where to save the test set (must contain a "true" folder and a "false" folder), and other parameters. In the cell "Define some functions" are defined the methods to extract the data and other utility functions. Those can be modified, allowing to use any temporal series dataset.

The characteristics of each notebook will be briefly illustrated. Each notebook can be used in different modes, specifying the parameter "mode".

| Notebook                    | Description                                                                                 |
|-----------------------------|---------------------------------------------------------------------------------------------|
| 1d cnn microbox             | Microbox time or frequency domain series (3 channels)                                       |
| 1d cnn infobox              | Infobox time or frequency domain series (2 channels)                                        |
| Norm 1d cnn microbox        | Microbox time or frequency domain series with module (1 channel)                            |
| Norm 1d cnn infobox         | Infobox time or frequency domain series with module (1 channel)                             |
| Data aug 1d cnn microbox    | Microbox time or frequency domain series with random rotations (3 channels)                 |
| Data aug 1d cnn infobox     | Infobox time or frequency domain series with random rotations (2 channels)                  |
| 2d cnn microbox             | Microbox time domain series using 4 methods to represent time series as images (3 channels) |
| Hyper tuning 1d cnn infobox | Hyper tuning on the infobox convolutional neural network                                    |

## Models
The repository contains the trained models. It will be described how each model was obtained.

| Model                               | Obtained by                                       |
|-------------------------------------|---------------------------------------------------|
| microbox xyz 300 23                 | 1d cnn microbox using time mode                   |
| microbox fft xyz 300 4              | 1d cnn microbox using fft mode                    |
| infobox xy 1200 15                  | 1d cnn infobox using time mode                    |
| infobox fft xy 1200 3               | 1d cnn infobox using fft mode                     |
| microbox xyz 300 norm 2             | Norm 1d cnn microbox using time mode              |
| microbox fft xyz 300 norm 5         | Norm 1d cnn microbox using fft mode               |
| infobox xy 1200 norm 1              | Norm 1d cnn infobox using time mode               |
| infobox fft xy 1200 norm 10         | Norm 1d cnn infobox using fft mode                |
| microbox fft xyz 300 data aug 11    | Data aug 1d cnn microbox using fft mode           |
| infobox fft xy 1200 data aug 1      | Data aug 1d cnn infobox  using fft mode           |
| microbox recuplot xyz 300 8         | 2d cnn microbox using recurrence plot mode        |
| microbox paired recuplot xyz 300 8  | 2d cnn microbox using paired recurrence plot mode |
| microbox spectrogram xyz 300 10     | 2d cnn microbox using spectrogram mode            |
| microbox scaleogram xyz 300 21      | 2d cnn microbox using scaleogram mode             |

## Results
The repository contains the results of the trainings and the tests. For each model described above, the following have been saved:

- Metrics: Test accuracy, Test loss, Test AUC, Precision, Recall, and F1-score.
- Confusion matrix.
- Train and validation accuracy graph.
- Train and validation loss graph.

There is also a file called Results.ods that summarize all the results.

## STM32
The repository also contains two applications for edge-ai on STM32 microcontroller. The device for which the applications were developed is the STM32F429I-DISC1. The applications allow the classification on the STM32 microcontroller, using the microbox xyz 300 23 model (STM32 microbox application) and the infobox xy 1200 15 model (STM32 infobox application).

The applications get the data to classify from a USB drive, that must have the following structure:

```
USB drive
├── infobox
│   ├── true
│   │   └── *.csv
│   └── false
│       └── *.csv
└── microbox
    ├── true
    │   └── *.csv
    └── false
        └── *.csv
```
The correct csv files format is generated when saving the test set using the 1d cnn microbox and the 1d cnn infobox notebooks. The parameters defined in the file main.h have to be specified correctly. When saving the test set using the notebooks, the BTR parameter is also printed to screen.

The applications classify each test series and display the results on the integrated LCD display, showing:

- Accuracy.
- Inference time.
- Number of true negatives.
- Number of false positives.
- Number of false negatives.
- Number of true positives.
- Precision.
- Recall.
- F1-score.
