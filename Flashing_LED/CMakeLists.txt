cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(flash_LED_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(flashLED
    main.c
)

pico_enable_stdio_usb(flashLED 1)
pico_enable_stdio_uart(flashLED 1)

pico_add_extra_outputs(flashLED)

target_link_libraries(flashLED pico_stdlib)