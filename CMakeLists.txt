cmake_minimum_required(VERSION 3.9)
project(RSA)

set(CMAKE_CXX_STANDARD 11)

set(SRCS
        src/main.cpp
        src/NumerosPrimos.h
        src/NumerosPrimos.cpp src/Claves.cpp src/Claves.h src/RSA.cpp src/RSA.h)

add_executable(RSA
    ${SRCS})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake)

#Adding GMP support
find_package(GMP REQUIRED)
target_link_libraries(RSA ${GMP_LIBRARIES})
