cmake_minimum_required(VERSION 3.9)
project(RSA)

set(CMAKE_CXX_STANDARD 11)

add_executable(RSA
    main.cpp
    NumerosPrimos.cpp
    NumerosPrimos.h)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/)

#Adding GMP support
find_package(GMP REQUIRED)
target_link_libraries(RSA ${GMP_LIBRARIES})
