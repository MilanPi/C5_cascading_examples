
## Overview

**STM32Cube** is an STMicroelectronics original initiative to ease the developers life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform, delivered for each STM32 series.
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product
   * The STM32 HAL-LL drivers : an abstraction drivers layer, the API ensuring maximized portability across the STM32 portfolio
   * The Parts Drivers of each Nucleo, evaluation or demonstration board provided by this STM32 series
   * A consistent set of middlewares components such as ThreadX, FileX, USBX, NetDuoX, OpenBootloader, USBPD, trustedfirmware, mbed-crypto, Network Library...
   * A full set of software projects (basic examples, applications, and demonstrations) for each board provided for this STM32 series.
   * A development with three Toolchains and Compilers (IAR Embedded Workbench for ARM (EWARM), RealView Microcontroller Development Kit (MDK-ARM), and STM32Cube VS Code).

Two models of publication are proposed for the STM32Cube embedded software:
   * The monolithic **MCU Package** : all STM32Cube software modules of one STM32 series are present (Drivers, Middlewares, Projects, Utilities) in the repo (usual name **STM32Cubexx**, xx corresponding to the STM32 series)
   * The **MCU component** : each STM32Cube software module being part of the STM32Cube MCU Package, are delivered as an individual repo, allowing the user to select and get only the required software functions.

## Description

This **stm32c5xx_hal_driver** MCU component repo is one element of the STM32CubeC5 MCU embedded software package, providing the **HAL-LL Drivers** part.

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32c5xx_hal_driver/blob/master/Release_Notes.html).


## Compatibility information

In this table, you can find the successive versions of this HAL-LL Driver component, in line with the corresponding versions of the full MCU package:

It is **crucial** that you use a consistent set of versions for the CMSIS Core - CMSIS Device - HAL, as mentioned in this table.

HAL Driver | CMSIS Device | CMSIS Core | Was delivered in the full MCU package
---------- | --------------- | ---------- | -------------------------------------
Tag alpha.1.0 | Tag alpha.2.4 | Tag 6.1.0 | Tag alpha.1.0 (and following, if any, till next tag)


The full **STM32CubeC5** MCU package is available [here](https://github.com/STMicroelectronics/STM32CubeC5).