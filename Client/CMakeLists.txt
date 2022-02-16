cmake_minimum_required(VERSION 3.5)

project(RestAPIClient_Linux LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR Source)
set(SOURCES ${SOURCE_DIR}/mongoose.cpp ${SOURCE_DIR}/restapiclient.cpp main.cpp )
include_directories(Include)

add_executable(RestAPIClient_Linux ${SOURCES})
