cmake_minimum_required(VERSION 2.8.11)
project(client)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "*.cpp")
include_directories(.)

find_package(Threads)
find_package( Boost 1.62 COMPONENTS system REQUIRED )

add_executable(client ${SOURCES})

target_link_libraries( client ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( client LINK_PUBLIC ${Boost_LIBRARIES} )
