############################################################################
# boards/arm/stm32wl5/nucleo-wl55jc/cpu2/Makefile
#
# Build M0+ (CPU2) bare-metal IPCC firmware independently of NuttX.
#
# Usage (from this directory):
#   make          — compile and link → build/cm0plus_uart_main.bin
#   make flash    — flash to CPU2 flash region (0x08020000) via OpenOCD
#   make clean    — remove all build artifacts
#   make size     — show section sizes
#
# Directory layout:
#   debug/        → intermediate .o files
#   build/        → .elf, .bin, .map
############################################################################

TARGET   = cm0plus_radio_main

# Output directories
DEBUG_DIR = debug
BUILD_DIR = build

# Final build artifacts
ELF      = $(BUILD_DIR)/$(TARGET).elf
BIN      = $(BUILD_DIR)/$(TARGET).bin
MAP      = $(BUILD_DIR)/$(TARGET).map

# Toolchain
CC       = arm-none-eabi-gcc
AS       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy
SIZE     = arm-none-eabi-size

# Linker script
LDSCRIPT = wl55jc_cm0plus.ld

# CPU flags — Cortex-M0+ thumb only (no Thumb-2 extensions)
CPU      = -mcpu=cortex-m0plus -mthumb

WL_FW := ../STM32Cube_FW_WL_V1.6.0

# Compiler flags
CFLAGS = $(CPU) \
          -O2 \
          -Wall \
          -Wextra \
          -g \
          -fdata-sections \
          -ffunction-sections \
          -DUSE_HAL_DRIVER \
          -DSTM32WL55xx \
          -DCORE_CM0PLUS \
          -I. \
          -Icore \
          -Icore/src \
          -Icore/inc \
          -Istartup \
          -Istm32_hal \
		  -Isubghz \
          -Isystem \
		  -ISubGHz_Phy/App \
		  -Istaff \
		  -IUtilities \
		  -IUtilities/misc \
		  -IUtilities/timer \
		  -IMiddlewares \
		  -IMiddlewares/stm32_radio_driver \
	  	  -ISubGHz_Phy/Target \
          -I$(WL_FW)/Drivers/CMSIS/Device/ST/STM32WLxx/Include \
          -I$(WL_FW)/Drivers/CMSIS/Include \
          -I$(WL_FW)/Drivers/STM32WLxx_HAL_Driver/Inc

# Assembler flags
ASFLAGS = $(CPU) -g

# Linker flags
LDFLAGS = $(CPU) \
           -T $(LDSCRIPT) \
           -Wl,--gc-sections \
           -Wl,-Map=$(MAP) \
           --specs=nano.specs \
           --specs=nosys.specs \
           -nostartfiles

# Source files
C_SRCS = \
core/src/cm0plus_radio_main.c \
core/src/error_handler.c \
core/src/uart_debug.c \
core/src/tim_delay.c \
system/system_stm32wlxx.c \
core/Src/stm32wlxx_it.c \
stm32_hal/stm32wlxx_hal.c \
stm32_hal/stm32wlxx_hal_rcc.c \
stm32_hal/stm32wlxx_hal_subghz.c \
stm32_hal/stm32wlxx_hal_cortex.c \
stm32_hal/stm32wlxx_hal_gpio.c \
subghz/subghz.c \
SubGHz_Phy/App/app_subghz_phy.c \
staff/sys_app.c \
SubGHz_Phy/App/subghz_phy_app.c \
SubGHz_Phy/Target/radio_board_if.c \
Middlewares/stm32_radio_driver/radio.c \
Middlewares/stm32_radio_driver/radio_driver.c \
Middlewares/stm32_radio_driver/radio_fw.c \
Middlewares/stm32_radio_driver/wl_lr_fhss.c \
Middlewares/stm32_radio_driver/lr_fhss_mac.c \
Utilities/timer/stm32_timer.c \
Utilities/misc/stm32_systime.c \
Utilities/misc/stm32_mem.c \
Utilities/trace/adv_trace/stm32_adv_trace.c \
Utilities/sequencer/stm32_seq.c \
Utilities/lpm/tiny_lpm/stm32_lpm.c \
Utilities/timer/stm32_timer_if.c \
Utilities/timer/timer_if_stub.c \
core/src/cw_function.c 

S_SRCS = \
startup/startup_cm0plus.s

# Object files
#
# Objects are placed under debug/ while preserving their source paths.
#
# Example:
#   core/src/cm0plus_uart_main.c
#       ->
#   debug/core/src/cm0plus_uart_main.o
#
C_OBJS = $(C_SRCS:%.c=$(DEBUG_DIR)/%.o)
S_OBJS = $(S_SRCS:%.s=$(DEBUG_DIR)/%.o)

ALL_OBJS = $(C_OBJS) $(S_OBJS)

# ── Default target ─────────────────────────────────────────────────────────

all: $(BIN)

# ── Link ───────────────────────────────────────────────────────────────────

$(ELF): $(ALL_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# ── Binary ─────────────────────────────────────────────────────────────────

$(BIN): $(ELF)
	@mkdir -p $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@
	@echo ""
	@echo "╔════════════════════════════════════════════╗"
	@echo "║  Built: $(BIN)"
	@echo "║  Flash target: 0x08020000                 ║"
	@echo "╚════════════════════════════════════════════╝"
	@$(SIZE) $(ELF)

# ── Compile C ──────────────────────────────────────────────────────────────
#
# Source:
#   core/src/foo.c
#
# Object:
#   debug/core/src/foo.o
#

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ── Assemble ───────────────────────────────────────────────────────────────
#
# Source:
#   startup/foo.s
#
# Object:
#   debug/startup/foo.o
#

$(DEBUG_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# ── Flash via OpenOCD ──────────────────────────────────────────────────────

flash: $(BIN)
	openocd \
	  -f interface/stlink.cfg \
	  -f target/stm32wlx.cfg \
	  -c "init" \
	  -c "targets" \
	  -c "reset halt" \
	  -c "halt" \
	  -c "flash probe 0" \
	  -c "program $(BIN) 0x08020000 verify" \
	  -c "reset run" \
	  -c "exit"

# ── Size report ────────────────────────────────────────────────────────────

size: $(ELF)
	$(SIZE) $<

# ── Clean ──────────────────────────────────────────────────────────────────

clean:
	rm -rf $(DEBUG_DIR) $(BUILD_DIR)

.PHONY: all flash size clean