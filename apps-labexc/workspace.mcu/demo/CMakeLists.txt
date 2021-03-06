cmake_minimum_required(VERSION 3.12)
project(demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Debug)
include_directories(mbed)
include_directories(mbed/drivers)
include_directories(mbed/hal)
include_directories(mbed/platform)
include_directories(mbed/TARGET_K64F)
include_directories(mbed/TARGET_K64F/TARGET_Freescale)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers)
include_directories(mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM)
include_directories(part-support)

add_executable(demo
        Debug/mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/subdir.mk
        Debug/makefile
        Debug/objects.mk
        Debug/sources.mk
        Debug/subdir.mk
        mbed/drivers/AnalogIn.h
        mbed/drivers/AnalogOut.h
        mbed/drivers/BusIn.h
        mbed/drivers/BusInOut.h
        mbed/drivers/BusOut.h
        mbed/drivers/CAN.h
        mbed/drivers/DigitalIn.h
        mbed/drivers/DigitalInOut.h
        mbed/drivers/DigitalOut.h
        mbed/drivers/Ethernet.h
        mbed/drivers/FlashIAP.h
        mbed/drivers/I2C.h
        mbed/drivers/I2CSlave.h
        mbed/drivers/InterruptIn.h
        mbed/drivers/InterruptManager.h
        mbed/drivers/LowPowerTicker.h
        mbed/drivers/LowPowerTimeout.h
        mbed/drivers/LowPowerTimer.h
        mbed/drivers/MbedCRC.h
        mbed/drivers/PortIn.h
        mbed/drivers/PortInOut.h
        mbed/drivers/PortOut.h
        mbed/drivers/PwmOut.h
        mbed/drivers/RawSerial.h
        mbed/drivers/Serial.h
        mbed/drivers/SerialBase.h
        mbed/drivers/SerialWireOutput.h
        mbed/drivers/SPI.h
        mbed/drivers/SPISlave.h
        mbed/drivers/TableCRC.h
        mbed/drivers/Ticker.h
        mbed/drivers/Timeout.h
        mbed/drivers/Timer.h
        mbed/drivers/TimerEvent.h
        mbed/drivers/UARTSerial.h
        mbed/hal/analogin_api.h
        mbed/hal/analogout_api.h
        mbed/hal/buffer.h
        mbed/hal/can_api.h
        mbed/hal/can_helper.h
        mbed/hal/crc_api.h
        mbed/hal/critical_section_api.h
        mbed/hal/dma_api.h
        mbed/hal/Driver_Common.h
        mbed/hal/Driver_Storage.h
        mbed/hal/ethernet_api.h
        mbed/hal/flash_api.h
        mbed/hal/flash_data.h
        mbed/hal/gpio_api.h
        mbed/hal/gpio_irq_api.h
        mbed/hal/i2c_api.h
        mbed/hal/itm_api.h
        mbed/hal/lp_ticker_api.h
        mbed/hal/pinmap.h
        mbed/hal/port_api.h
        mbed/hal/pwmout_api.h
        mbed/hal/rtc_api.h
        mbed/hal/serial_api.h
        mbed/hal/sleep_api.h
        mbed/hal/spi_api.h
        mbed/hal/ticker_api.h
        mbed/hal/trng_api.h
        mbed/hal/us_ticker_api.h
        mbed/platform/ATCmdParser.h
        mbed/platform/Callback.h
        mbed/platform/CallChain.h
        mbed/platform/CircularBuffer.h
        mbed/platform/critical.h
        mbed/platform/CriticalSectionLock.h
        mbed/platform/CThunk.h
        mbed/platform/DeepSleepLock.h
        mbed/platform/DirHandle.h
        mbed/platform/FileBase.h
        mbed/platform/FileHandle.h
        mbed/platform/FileLike.h
        mbed/platform/FilePath.h
        mbed/platform/FileSystemHandle.h
        mbed/platform/FileSystemLike.h
        mbed/platform/FunctionPointer.h
        mbed/platform/LocalFileSystem.h
        mbed/platform/mbed_application.h
        mbed/platform/mbed_assert.h
        mbed/platform/mbed_critical.h
        mbed/platform/mbed_debug.h
        mbed/platform/mbed_error.h
        mbed/platform/mbed_error_hist.h
        mbed/platform/mbed_interface.h
        mbed/platform/mbed_mem_trace.h
        mbed/platform/mbed_mktime.h
        mbed/platform/mbed_poll.h
        mbed/platform/mbed_power_mgmt.h
        mbed/platform/mbed_preprocessor.h
        mbed/platform/mbed_retarget.h
        mbed/platform/mbed_rtc_time.h
        mbed/platform/mbed_semihost_api.h
        mbed/platform/mbed_sleep.h
        mbed/platform/mbed_stats.h
        mbed/platform/mbed_toolchain.h
        mbed/platform/mbed_wait_api.h
        mbed/platform/NonCopyable.h
        mbed/platform/platform.h
        mbed/platform/PlatformMutex.h
        mbed/platform/rtc_time.h
        mbed/platform/ScopedLock.h
        mbed/platform/semihost_api.h
        mbed/platform/SingletonPtr.h
        mbed/platform/sleep.h
        mbed/platform/Stream.h
        mbed/platform/toolchain.h
        mbed/platform/Transaction.h
        mbed/platform/wait_api.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/dma_api_hal.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/gpio_object.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/objects.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/PeripheralPins.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/PortNames.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/cmsis.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/cmsis_nvic.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/fsl_device_registers.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/MK64F12.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/MK64F12_features.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/system_MK64F12.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_adc16.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_clock.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_cmp.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_cmt.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_common.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_crc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_dac.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_dmamux.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_dspi.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_dspi_edma.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_edma.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_enet.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_ewm.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_flash.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_flexbus.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_flexcan.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_ftm.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_gpio.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_i2c.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_i2c_edma.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_llwu.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_lptmr.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_pdb.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_pit.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_pmc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_port.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_rcm.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_rnga.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_rtc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sai.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sai_edma.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sdhc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sim.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_smc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sysmpu.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_uart.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_uart_edma.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_vref.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_wdog.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/crc.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/device.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/fsl_clock_config.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/fsl_phy.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/PeripheralNames.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/PinNames.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/dma_reqs.h
        mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/peripheral_clock_defines.h
        mbed/TARGET_K64F/TARGET_Freescale/mbed_rtx.h
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/analogin_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/analogout_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/crc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/dma_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/flash_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_adc16.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_clock.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_clock_config.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_cmp.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_cmt.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_common.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_crc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dac.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dmamux.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dspi.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dspi_edma.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_edma.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_enet.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_ewm.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flash.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flexbus.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flexcan.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_ftm.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_gpio.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_i2c.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_i2c_edma.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_llwu.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_lptmr.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pdb.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_phy.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pit.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pmc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rcm.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rnga.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rtc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sai.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sai_edma.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sdhc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sim.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_smc.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sysmpu.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_uart.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_uart_edma.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_vref.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_wdog.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/gpio_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/gpio_irq_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/i2c_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/libmbed.a
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/lp_ticker.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_board.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_crc_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_overrides.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_retarget.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_sdk_boot.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_tz_context.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/PeripheralPins.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/pinmap.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/port_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/pwmout_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/rtc_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/serial_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/sleep.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/spi_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/startup_MK64F12.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/storage_driver.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/system_MK64F12.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/trng_api.o
        mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/us_ticker.o
        mbed/TARGET_K64F/arm_math.h
        mbed/TARGET_K64F/cmsis_armcc.h
        mbed/TARGET_K64F/cmsis_armclang.h
        mbed/TARGET_K64F/cmsis_compiler.h
        mbed/TARGET_K64F/cmsis_gcc.h
        mbed/TARGET_K64F/cmsis_iccarm.h
        mbed/TARGET_K64F/cmsis_version.h
        mbed/TARGET_K64F/core_armv8mbl.h
        mbed/TARGET_K64F/core_armv8mml.h
        mbed/TARGET_K64F/core_cm0.h
        mbed/TARGET_K64F/core_cm0plus.h
        mbed/TARGET_K64F/core_cm23.h
        mbed/TARGET_K64F/core_cm3.h
        mbed/TARGET_K64F/core_cm33.h
        mbed/TARGET_K64F/core_cm4.h
        mbed/TARGET_K64F/core_cm7.h
        mbed/TARGET_K64F/core_cmSecureAccess.h
        mbed/TARGET_K64F/core_sc000.h
        mbed/TARGET_K64F/core_sc300.h
        mbed/TARGET_K64F/mbed_cmsis_conf.h
        mbed/TARGET_K64F/mbed_lib.json
        mbed/TARGET_K64F/mpu_armv7.h
        mbed/TARGET_K64F/mpu_armv8.h
        mbed/TARGET_K64F/RTE_Components.h
        mbed/TARGET_K64F/tz_context.h
        mbed/mbed.h
        mbed/targets.json
        part-support/devices/MK64F12/mcuxpresso/FTFE_4K.cfx
        part-support/devices/MK64F12/MK64F12.xml
        part-support/docs/images/device.jpg
        part-support/docs/images/FRDM-K64F.gif
        part-support/FRDM-K64F_manifest_v3_3.xml
        "demo JLink Debug.launch"
        "demo JLink Release.launch"
        libdemo.a
        main-demo.cpp
        Makefile
        makefile.targets
        mbed.bld
        mbed_config.h)
