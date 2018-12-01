cmake_minimum_required(VERSION 2.8.11)
project(BotMe)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

add_executable(botMe ${SOURCES})
