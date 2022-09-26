cmake_minimum_required(VERSION 3.23)
project(interfaces)

set(CMAKE_CXX_STANDARD 20)

add_executable(interfaces main.cc packet.h CRC.h octopayload.h)
