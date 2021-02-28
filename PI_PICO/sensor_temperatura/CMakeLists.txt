cmake_minimum_required(VERSION 3.1)

include(~/linuxTools/pico-sdk/external/pico_sdk_import.cmake)

project(sensor_temperatura)

pico_sdk_init()

add_executable(main
    main.c
)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
target_link_libraries(main pico_stdlib hardware_adc)

