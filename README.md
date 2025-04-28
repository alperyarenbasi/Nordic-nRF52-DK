# Nordic nRF52 DK Lab Exercises

This repository contains the lab code, documentation and examples for working with the Nordic Semiconductor nRF52 Development Kit (DK), as part of the TTK4235 “Tilpassede Datasystemer” course at NTNU.

## Contents

- `lab_3-0.0.16/`  
  Source code and configuration for Lab 3 (version 0.0.16), including example firmware and linker scripts.
- `main.pdf`  
  PDF of the lab assignment and hardware specification.
- `.gitignore`  
  Git ignore rules for build artifacts and IDE files.
- `README.md` (this file)

## Prerequisites

- **Hardware**  
  - Nordic nRF52 Development Kit board (e.g. nRF52832-DK or nRF52840-DK)  
  - USB cable for power and UART/SEGGER J-Link interface  
- **Toolchain**  
  - GNU Arm Embedded Toolchain (arm-none-eabi-gcc, version ≥ 10)  
  - Nordic nRF5 SDK (compatible with your board—e.g. v17.0.2)  
  - SEGGER J-Link software (for flashing and debugging)  
  - Python 3 (for optional scripts)  
- **Utilities**  
  - `make` or `ninja` (depending on project build files)  
  - `openocd` (if you prefer to use it instead of J-Link Commander)  
  - Serial terminal emulator (e.g. `picocom` or `minicom`)

## Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/alperyarenbasi/Nordic-nRF52-DK.git
   cd Nordic-nRF52-DK
   ```

2. **Open the lab specification**  
   Read the assignment in `main.pdf` to understand the objectives, hardware connections and required exercises.

3. **Build the firmware**  
   ```bash
   cd lab_3-0.0.16
   and then cd into on of the 3 directories (tasks) 
   make 
   ```
   (Or follow the instructions in the lab folder’s `README` or `Makefile`.)

4. **Flash to the board**  
   ```bash
   make flash
   ```
   This uses SEGGER J-Link Commander under the hood to program the nRF52’s flash.

5. **Monitor serial output**  
   Once your board is powered and running, open a serial terminal at 9600 baud:
   ```bash
   picocom -b 9600 /dev/ttyACM0
   ```
   (Replace `/dev/ttyACM0` with the device your board enumerates as.)

