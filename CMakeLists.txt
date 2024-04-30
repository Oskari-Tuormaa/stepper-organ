cmake_minimum_required(VERSION 3.20)

include(pico-sdk/pico_sdk_init.cmake)
set(PICO_BOARD pico_w)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

project(stepper-organ)

pico_sdk_init()

add_executable(${PROJECT_NAME} src/main.cpp src/stepper_ctrl.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_include_directories(${PROJECT_NAME} PRIVATE include)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pio
    pico_cyw43_arch_none)
