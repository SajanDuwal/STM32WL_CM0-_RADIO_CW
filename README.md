# STM32WL Cortex-M0+ Bare-Metal CW Radio Driver

A lightweight, **bare-metal CW-RADIO Transmitter driver** written from scratch for the **ARM Cortex-M0+ core** of the **STM32WL microcontroller M0+** . 

## 🚀 Features
* **Cortex-M0+ Optimization:** Specifically configured for the low-power secondary core (CM0+) of the dual-core STM32WL architecture.
* **Efficient Polling-based Transmission:** Simple APIs to transmit single bytes or entire strings over serial.
* **Efficient Interrupt Receiverer:** Simple APIs to Receive single bytes or entire strings over serial.
* **Custom Baud Rate Calculator:** Demonstrates configuring the `USART_BRR` register based on peripheral clock speeds.
* **Ring Buffer and IQR inrerface:** Organize the received bytes from the RX-line interrupt.
* **CW-Transmission:** CW at 18 WPM.

# 📡 USART2 Configuration

The UART driver uses USART2 with the following configuration:

| Parameter | Configuration |
|---|---|
| Peripheral | USART2 |
| TX Pin | PA2 |
| RX Pin | PA3 |
| Alternate Function | AF7 |
| Baud Rate | 115200 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Flow Control | None |

### Pin Configuration

```text
STM32WL55JC2

PA2 ───────────────► USART2_TX

PA3 ◄─────────────── USART2_RX
```

### Example: Triggering CW Transmission
```text
Serial Monitor

Send `0xAA` over USART2 to trigger an 18 WPM CW transmission sequence:

​```
================================
 STM32WL55JC2 CM0+ BARE_METAL 
================================
1. Send 0xAA for CW @ 18WPM
Waiting to receive CMD.....
---- Sent hex encoded message: "AA" ----
Received: 1 bytes
AA 
CW transmission Started
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
​```

## 📁 Repository Structure
To build this project, you need the official STMicroelectronics CMSIS/Device files. The repository expects a specific folder structure where the official firmware package sits right alongside your project directory inside a shared base folder:

```text
base_folder/
├── STM32WL_CM0-_RADIO_BARE_METAL/  <-- (This project folder)
└── STM32Cube_FW_WL_V1.6.0/         <-- (Official ST Firmware package)
```

## 🔧 Building & Flashing

### 1. Prerequisites & Toolchain
Ensure you have the ARM GNU Toolchain installed on your host machine:
```bash
arm-none-eabi-gcc --version
```

### 2. Setup and Cloning Instructions
Instead of downloading a massive full framework zip, you can bypass the heavy overhead by cloning just the required `v1.6.0` firmware package components locally using these commands:

1. **Create and enter your main base folder:**
   ```bash
   mkdir your_base_folder && cd your_base_folder
   ```
2. **Clone this Bare-Metal repository:**
   ```bash
   git clone https://github.com
   ```
3. **Clone the required STM32CubeWL v1.6.0 firmware repository right next to it:**
   ```bash
   git clone --branch v1.6.0 --depth 1 https://github.com/STMicroelectronics/STM32CubeWL.git STM32Cube_FW_WL_V1.6.0
   ```

### 3. Compile the Binary
Navigate into your project folder and compile using the local paths:
```bash
cd STM32WL_CM0-_UART_BARE_METAL
make
```

### 4. Flash to Target
Upload the compiled binary to your microcontoller by running:
```bash
make flash
```

## 📺 Monitoring Output
Connect your serial terminal monitor (like PuTTY, Tera Term, or the Serial Monitor inside VS Code) to the allocated COM port using these parameters:
* **Baud Rate:** 115200 (Default)
* **Data Bits:** 8
* **Parity:** None
* **Stop Bits:** 1
