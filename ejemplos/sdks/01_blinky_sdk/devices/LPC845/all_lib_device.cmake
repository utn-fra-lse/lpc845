# Copy variable into project config.cmake to use software component
#set.board.lpcxpresso845max
#  # description: Board_project_template lpcxpresso845max
#  set(CONFIG_USE_board_project_template true)

#set.board.lpc845breakout
#  # description: Board_project_template lpc845breakout
#  set(CONFIG_USE_board_project_template true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#set.CMSIS
#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_GPIO.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_GPIO true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX_LIB true)

#set.device.LPC845
#  # description: Rte_device
#  set(CONFIG_USE_device_RTE true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Inputmux_connections Driver
#  set(CONFIG_USE_driver_inputmux_connections true)

#  # description: Power driver
#  set(CONFIG_USE_driver_power true)

#  # description: Reset Driver
#  set(CONFIG_USE_driver_reset true)

#  # description: swm_connections Driver
#  set(CONFIG_USE_driver_swm_connections true)

#  # description: syscon_connections Driver
#  set(CONFIG_USE_driver_syscon_connections true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Used to include slave core binary into master core binary.
#  set(CONFIG_USE_utility_incbin true)

#  # description: common Driver
#  set(CONFIG_USE_driver_common true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Devices_project_template LPC845
#  set(CONFIG_USE_device_project_template true)

#  # description: Device LPC845_cmsis
#  set(CONFIG_USE_device_CMSIS true)

#  # description: Device LPC845_system
#  set(CONFIG_USE_device_system true)

#  # description: Device LPC845_startup
#  set(CONFIG_USE_device_startup true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: WWDT Driver
#  set(CONFIG_USE_driver_wwdt true)

#  # description: WKT Driver
#  set(CONFIG_USE_driver_wkt true)

#  # description: SYSCON Driver
#  set(CONFIG_USE_driver_syscon true)

#  # description: SWM Driver
#  set(CONFIG_USE_driver_swm true)

#  # description: SCT Driver
#  set(CONFIG_USE_driver_sctimer true)

#  # description: PINT Driver
#  set(CONFIG_USE_driver_pint true)

#  # description: MRT Driver
#  set(CONFIG_USE_driver_mrt true)

#  # description: USART Driver
#  set(CONFIG_USE_driver_lpc_miniusart true)

#  # description: SPI Driver
#  set(CONFIG_USE_driver_lpc_minispi true)

#  # description: IOCON Driver
#  set(CONFIG_USE_driver_lpc_iocon_lite true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_lpc_i2c true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_lpc_i2c_dma true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_lpc_gpio true)

#  # description: DMA Driver
#  set(CONFIG_USE_driver_lpc_dma true)

#  # description: DAC Driver
#  set(CONFIG_USE_driver_lpc_dac true)

#  # description: CRC Driver
#  set(CONFIG_USE_driver_lpc_crc true)

#  # description: ADC Driver
#  set(CONFIG_USE_driver_lpc_adc true)

#  # description: LPC_ACOMP Driver
#  set(CONFIG_USE_driver_lpc_acomp true)

#  # description: INPUTMUX Driver
#  set(CONFIG_USE_driver_inputmux true)

#  # description: IAP Driver
#  set(CONFIG_USE_driver_iap true)

#  # description: CTimer Driver
#  set(CONFIG_USE_driver_ctimer true)

#  # description: CAPT Driver
#  set(CONFIG_USE_driver_capt true)

#  # description: Component miniusart_adapter
#  set(CONFIG_USE_component_miniusart_adapter true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component ctimer_adapter
#  set(CONFIG_USE_component_ctimer_adapter true)

#  # description: Component mrt_adapter
#  set(CONFIG_USE_component_mrt_adapter true)

#  # description: Component pwm_ctimer_adapter
#  set(CONFIG_USE_component_pwm_ctimer_adapter true)

#  # description: Component mem_manager
#  set(CONFIG_USE_component_mem_manager true)

#  # description: Component mem_manager_legacy
#  set(CONFIG_USE_component_mem_manager_legacy true)

#  # description: Component mem_manager_light
#  set(CONFIG_USE_component_mem_manager_light true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component led
#  set(CONFIG_USE_component_led true)

#  # description: Component lpc_i2c_adapter
#  set(CONFIG_USE_component_lpc_i2c_adapter true)

#  # description: Component i2c_adapter_interface
#  set(CONFIG_USE_component_i2c_adapter_interface true)

#  # description: Component i2c_mux_pca954x
#  set(CONFIG_USE_component_i2c_mux_pca954x true)

#  # description: Component enable_pca9544
#  set(CONFIG_USE_component_enable_pca9544 true)

#  # description: Component enable_pca9548
#  set(CONFIG_USE_component_enable_pca9548 true)

#  # description: Component at_least_one_i2c_mux_device_enabled
#  set(CONFIG_USE_component_at_least_one_i2c_mux_device_enabled true)

#  # description: Component lpc_gpio_adapter
#  set(CONFIG_USE_component_lpc_gpio_adapter true)

#  # description: Component rt_gpio_adapter
#  set(CONFIG_USE_component_rt_gpio_adapter true)

#  # description: Component lpc_crc_adapter
#  set(CONFIG_USE_component_lpc_crc_adapter true)

#  # description: Component button
#  set(CONFIG_USE_component_button true)

#set.component.osa
#  # description: Component osa template config
#  set(CONFIG_USE_component_osa_template_config true)

#  # description: Component osa
#  set(CONFIG_USE_component_osa true)

#  # description: Component osa_bm
#  set(CONFIG_USE_component_osa_bm true)

#  # description: Component common_task
#  set(CONFIG_USE_component_common_task true)

#set.middleware.fmstr
#  # description: Common FreeMASTER driver code.
#  set(CONFIG_USE_middleware_fmstr true)

#  # description: FreeMASTER driver code for 32bit platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_gen32le true)

#  # description: FreeMASTER driver code for DSC platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_56f800e true)

#  # description: FreeMASTER driver code for S32 platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s32 true)

#  # description: FreeMASTER driver code for Power Architecture 32bit platform.
#  set(CONFIG_USE_middleware_fmstr_platform_pa32 true)

#  # description: FreeMASTER driver code for S12Z platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s12z true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/NN
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/lpc845breakout/project_template
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/lpcxpresso845max/project_template
  ${CMAKE_CURRENT_LIST_DIR}/../../components/button
  ${CMAKE_CURRENT_LIST_DIR}/../../components/common_task
  ${CMAKE_CURRENT_LIST_DIR}/../../components/crc
  ${CMAKE_CURRENT_LIST_DIR}/../../components/gpio
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c/muxes
  ${CMAKE_CURRENT_LIST_DIR}/../../components/led
  ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
  ${CMAKE_CURRENT_LIST_DIR}/../../components/mem_manager
  ${CMAKE_CURRENT_LIST_DIR}/../../components/osa
  ${CMAKE_CURRENT_LIST_DIR}/../../components/panic
  ${CMAKE_CURRENT_LIST_DIR}/../../components/pwm
  ${CMAKE_CURRENT_LIST_DIR}/../../components/reset
  ${CMAKE_CURRENT_LIST_DIR}/../../components/rng
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer
  ${CMAKE_CURRENT_LIST_DIR}/../../components/timer_manager
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/freemaster
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/project_template
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/utilities
  ${CMAKE_CURRENT_LIST_DIR}/utilities/debug_console_lite
  ${CMAKE_CURRENT_LIST_DIR}/utilities/incbin
)

include_if_use(CMSIS_DSP_Include)
include_if_use(CMSIS_DSP_Source)
include_if_use(CMSIS_Device_API_OSTick)
include_if_use(CMSIS_Device_API_RTOS2)
include_if_use(CMSIS_Driver_Include_CAN)
include_if_use(CMSIS_Driver_Include_Ethernet)
include_if_use(CMSIS_Driver_Include_Ethernet_MAC)
include_if_use(CMSIS_Driver_Include_Ethernet_PHY)
include_if_use(CMSIS_Driver_Include_Flash)
include_if_use(CMSIS_Driver_Include_GPIO)
include_if_use(CMSIS_Driver_Include_I2C)
include_if_use(CMSIS_Driver_Include_MCI)
include_if_use(CMSIS_Driver_Include_NAND)
include_if_use(CMSIS_Driver_Include_SAI)
include_if_use(CMSIS_Driver_Include_SPI)
include_if_use(CMSIS_Driver_Include_USART)
include_if_use(CMSIS_Driver_Include_USB_Device)
include_if_use(CMSIS_Driver_Include_USB_Host)
include_if_use(CMSIS_Driver_Include_WiFi)
include_if_use(CMSIS_Include_core_cm)
include_if_use(CMSIS_NN_Source)
include_if_use(CMSIS_RTOS2_RTX)
include_if_use(CMSIS_RTOS2_RTX_LIB)
include_if_use(board_project_template)
include_if_use(board_project_template)
include_if_use(component_at_least_one_i2c_mux_device_enabled.LPC845)
include_if_use(component_button.LPC845)
include_if_use(component_common_task)
include_if_use(component_ctimer_adapter.LPC845)
include_if_use(component_enable_pca9544.LPC845)
include_if_use(component_enable_pca9548.LPC845)
include_if_use(component_i2c_adapter_interface.LPC845)
include_if_use(component_i2c_mux_pca954x.LPC845)
include_if_use(component_led.LPC845)
include_if_use(component_lists.LPC845)
include_if_use(component_lpc_crc_adapter.LPC845)
include_if_use(component_lpc_gpio_adapter.LPC845)
include_if_use(component_lpc_i2c_adapter.LPC845)
include_if_use(component_mem_manager.LPC845)
include_if_use(component_mem_manager_legacy.LPC845)
include_if_use(component_mem_manager_light.LPC845)
include_if_use(component_miniusart_adapter.LPC845)
include_if_use(component_mrt_adapter.LPC845)
include_if_use(component_osa)
include_if_use(component_osa_bm)
include_if_use(component_osa_template_config)
include_if_use(component_panic.LPC845)
include_if_use(component_pwm_ctimer_adapter.LPC845)
include_if_use(component_reset_adapter.LPC845)
include_if_use(component_rt_gpio_adapter.LPC845)
include_if_use(component_software_crc_adapter.LPC845)
include_if_use(component_software_rng_adapter.LPC845)
include_if_use(component_timer_manager.LPC845)
include_if_use(device_CMSIS.LPC845)
include_if_use(device_RTE.LPC845)
include_if_use(device_project_template.LPC845)
include_if_use(device_startup.LPC845)
include_if_use(device_system.LPC845)
include_if_use(driver_capt.LPC845)
include_if_use(driver_clock.LPC845)
include_if_use(driver_common.LPC845)
include_if_use(driver_ctimer.LPC845)
include_if_use(driver_iap.LPC845)
include_if_use(driver_inputmux.LPC845)
include_if_use(driver_inputmux_connections.LPC845)
include_if_use(driver_lpc_acomp.LPC845)
include_if_use(driver_lpc_adc.LPC845)
include_if_use(driver_lpc_crc.LPC845)
include_if_use(driver_lpc_dac.LPC845)
include_if_use(driver_lpc_dma.LPC845)
include_if_use(driver_lpc_gpio.LPC845)
include_if_use(driver_lpc_i2c.LPC845)
include_if_use(driver_lpc_i2c_dma.LPC845)
include_if_use(driver_lpc_iocon_lite.LPC845)
include_if_use(driver_lpc_minispi.LPC845)
include_if_use(driver_lpc_miniusart.LPC845)
include_if_use(driver_mrt.LPC845)
include_if_use(driver_pint.LPC845)
include_if_use(driver_power.LPC845)
include_if_use(driver_reset.LPC845)
include_if_use(driver_sctimer.LPC845)
include_if_use(driver_swm.LPC845)
include_if_use(driver_swm_connections.LPC845)
include_if_use(driver_syscon.LPC845)
include_if_use(driver_syscon_connections.LPC845)
include_if_use(driver_wkt.LPC845)
include_if_use(driver_wwdt.LPC845)
include_if_use(middleware_fmstr)
include_if_use(middleware_fmstr_platform_56f800e)
include_if_use(middleware_fmstr_platform_gen32le)
include_if_use(middleware_fmstr_platform_pa32)
include_if_use(middleware_fmstr_platform_s12z)
include_if_use(middleware_fmstr_platform_s32)
include_if_use(utilities_misc_utilities.LPC845)
include_if_use(utility_assert_lite.LPC845)
include_if_use(utility_debug_console_lite.LPC845)
include_if_use(utility_incbin.LPC845)
include_if_use(utility_str.LPC845)
