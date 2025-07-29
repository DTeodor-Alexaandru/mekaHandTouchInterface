cmake_minimum_required(VERSION 3.16)
add_compile_definitions(TINYUSB_DESC_DYN=1)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(mcuInterface)
