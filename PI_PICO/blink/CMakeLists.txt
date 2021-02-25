cmake_minimum_required(VERSION 3.1)

include(~/linuxTools/pico-sdk/external/pico_sdk_import.cmake)

project(blink)

pico_sdk_init()

add_executable(main
    main.c
)


pico_add_extra_outputs(main)
target_link_libraries(main pico_stdlib)

