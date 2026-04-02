set(CMAKE_AUTOMOC ON)

cmake_minimum_required(VERSION 3.16)
project(lab6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

set(FFTW3_LIB_DIR "/opt/homebrew/opt/fftw/lib")
set(FFTW3_INCLUDE_DIR "/opt/homebrew/opt/fftw/include")
find_library(FFTW3_LIBRARY NAMES fftw3 PATHS ${FFTW3_LIB_DIR} NO_DEFAULT_PATH)

if(NOT FFTW3_LIBRARY)
    message(FATAL_ERROR "FFTW3 library not found")
endif()

set(SOURCES
    main.cpp
    mainwindow.cpp
    calcfft.cpp
    param.cpp
    sample.cpp
    sample_complex.cpp
    qcustomplot/qcustomplot.cpp
)

set(HEADERS
    mainwindow.h
    calcfft.h
    param.h
    sample.h
    sample_complex.h
    qcustomplot/qcustomplot.h
)

add_executable(lab6 ${SOURCES} ${HEADERS})

target_include_directories(lab6 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FFTW3_INCLUDE_DIR}
)

target_link_libraries(lab6 PRIVATE
    Qt6::Widgets
    Qt6::PrintSupport
    ${FFTW3_LIBRARY}
)
