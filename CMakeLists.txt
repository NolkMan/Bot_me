cmake_minimum_required(VERSION 2.8.11)
project(BotMe)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(Threads)
find_package( Boost 1.62 COMPONENTS system REQUIRED )

add_executable(botMe ${SOURCES})
target_link_libraries( botMe ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( botMe LINK_PUBLIC ${Boost_LIBRARIES} )
