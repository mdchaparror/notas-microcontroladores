cmake_minimum_required(VERSION 3.12)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico_sdk_init.cmake)
project(blink)
pico_sdk_init()

add_executable(main
    main.c
)



 # enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
target_link_libraries(main pico_stdlib)

# initialize the Raspberry Pi Pico SDK

# rest of your project