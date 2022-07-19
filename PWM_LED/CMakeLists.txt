cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(PWM_LED_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(PWM_LED
    main.c
)

pico_enable_stdio_usb(PWM_LED 1)
pico_enable_stdio_uart(PWM_LED 1)

pico_add_extra_outputs(PWM_LED)

target_link_libraries(PWM_LED pico_stdlib hardware_pwm)