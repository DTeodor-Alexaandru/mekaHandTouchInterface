# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/teodor/esp/esp-idf/components/bootloader/subproject"
  "/home/teodor/test-23-07-2025/build/bootloader"
  "/home/teodor/test-23-07-2025/build/bootloader-prefix"
  "/home/teodor/test-23-07-2025/build/bootloader-prefix/tmp"
  "/home/teodor/test-23-07-2025/build/bootloader-prefix/src/bootloader-stamp"
  "/home/teodor/test-23-07-2025/build/bootloader-prefix/src"
  "/home/teodor/test-23-07-2025/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/teodor/test-23-07-2025/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/teodor/test-23-07-2025/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
