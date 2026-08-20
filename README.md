# STM32WL Cortex-M0+ Bare-Metal CW Radio Driver

A lightweight **bare-metal CW radio transmitter driver** written for the **ARM Cortex-M0+ core** of the dual-core STM32WL microcontroller.

The project demonstrates direct low-level control of the STM32WL radio subsystem from the CM0+ core without using an RTOS.

## 🚀 Features

- **Cortex-M0+ Bare-Metal**
  - Specifically designed for the low-power secondary CM0+ core of the STM32WL dual-core architecture.

- **Polling-Based Transmission**
  - Simple APIs for transmitting data over the serial interface.

- **Interrupt-Based Receiver**
  - UART reception using interrupts.

- **Ring Buffer**
  - Organizes received bytes from the UART RX interrupt.

- **Custom Baud Rate Configuration**
  - Demonstrates configuring the UART baud-rate register based on the peripheral clock.

- **CW Transmission**
  - Generates an 18 WPM CW transmission sequence using the STM32WL radio.

## 📡 UART Configuration

The UART interface uses the following configuration:

| Parameter | Configuration |
|---|---|
| Peripheral | LPUART1 |
| TX Pin | PA2 |
| RX Pin | PA3 |
| Alternate Function | AF8 |
| Baud Rate | 115200 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Flow Control | None |

### Pin Configuration

```text
STM32WL55JC2

PA2 ───────────────► LPUART1_TX
PA3 ◄─────────────── LPUART1_RX
```

> **Note:** The UART peripheral and alternate-function configuration must match the actual STM32WL board routing used by the project.

## 📡 Triggering CW Transmission

Send the command `0xAA` through the UART interface to trigger the CW transmission sequence.

```text
Serial Monitor
     │
     │  0xAA
     ▼
STM32WL55JC2 CM0+
     │
     ▼
CW Transmission
     │
     ▼
18 WPM
```

## CW Transmission Test

**Command:** `0xAA`  
**Mode:** Continuous Wave (CW)  
**Speed:** 18 WPM  
**Target:** STM32WL55JC2 CM0+

### Result

:white_check_mark: **CW transmission started successfully.**

### UART Output

```text
================================
 STM32WL55JC2 CM0+ BARE-METAL
================================
1. Send 0xAA for CW @ 18 WPM
Waiting to receive CMD.....

---- Sent hex encoded message: "AA" ----

Received: 1 byte
AA

CW transmission started
CW Byte = B1
CW Byte = 34
CW Byte = AA
CW Byte = 5A
CW Byte = FF
CW Byte = B2
CW Byte = 17
CW Byte = 00
CW Byte = 00
CW Byte = 00
```

## 📁 Repository Structure

The project uses the STM32CubeWL firmware package for the required CMSIS, device definitions, and HAL components.

The expected directory structure is:

```text
base_folder/
│
├── STM32WL_CM0_RADIO_BARE_METAL/    ← This project
│
└── STM32Cube_FW_WL_V1.6.0/          ← STM32CubeWL v1.6.0
```

The STM32CubeWL firmware package is intentionally **not included in this repository**.

## 🔧 Building & Flashing

### 1. Prerequisites

Install the ARM GNU Toolchain and verify that it is available:

```bash
arm-none-eabi-gcc --version
```

You will also need:

- GNU Make
- OpenOCD
- STM32WL55JC development board
- USB connection for programming/debugging

### 2. Clone the Repositories

Create a common base directory:

```bash
mkdir your_base_folder
cd your_base_folder
```

Clone this bare-metal project:

```bash
git clone <YOUR_REPOSITORY_URL>
```

Clone the required STM32CubeWL v1.6.0 firmware package next to it:

```bash
git clone --branch v1.6.0 --depth 1 \
https://github.com/STMicroelectronics/STM32CubeWL.git \
STM32Cube_FW_WL_V1.6.0
```

The resulting structure should be:

```text
your_base_folder/
│
├── STM32WL_CM0_RADIO_BARE_METAL/
│
└── STM32Cube_FW_WL_V1.6.0/
```

### 3. Build

Navigate into the project:

```bash
cd STM32WL_CM0_RADIO_BARE_METAL
```

Build the firmware:

```bash
make
```

The build produces:

```text
build/
├── cm0plus_radio_main.elf
├── cm0plus_radio_main.bin
└── cm0plus_radio_main.map
```

### 4. Flash

Flash the CM0+ firmware using:

```bash
make flash
```

The firmware is programmed into the CM0+ flash region:

```text
0x08020000
```

## 📺 Monitoring Output

Connect the board to a serial terminal such as:

- PuTTY
- Tera Term
- VS Code Serial Monitor

Use the following serial configuration:

| Parameter | Configuration |
|---|---|
| Baud Rate | 115200 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Flow Control | None |

After opening the serial terminal, the firmware should display:

```text
================================
 STM32WL55JC2 CM0+ BARE-METAL
================================
1. Send 0xAA for CW @ 18 WPM
Waiting to receive CMD.....
```

Send:

```text
AA
```

as a hexadecimal byte.

The firmware should then start the CW transmission sequence.

## 🧩 Architecture

The firmware is structured approximately as:

```text
                    STM32WL55JC2
                 ┌─────────────────┐
                 │                 │
                 │   Cortex-M4     |
                 |    (NUTTX)      │    
                 ├─────────────────┤
                 │   Cortex-M0+    │
                 │                 │
                 │  Bare-Metal FW  │
                 └────────┬────────┘
                          │
                          ▼
                   Radio Interface
                          │
                          ▼
                   SUBGHZ / HAL
                          │
                          ▼
                    STM32WL Radio
                          │
                          ▼
                     CW Output
```