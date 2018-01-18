cmake_minimum_required(VERSION 3.9)
project(RSA)

set(CMAKE_CXX_STANDARD 11)

set(SRCS
        src/main.cpp
        src/PrimeNumbers.h src/PrimeNumbers.cpp
        src/Keys.h src/Keys.cpp
#        src/RSA.h src/RSA.cpp
        )

add_executable(RSA
    ${SRCS})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake)

#Adding GMP support
find_package(GMP REQUIRED)
target_link_libraries(RSA ${GMP_LIBRARIES})
