cmake_minimum_required(VERSION 3.10.2)
project(waybar-bluetooth_battery_parse)

# set include path and src to build
INCLUDE_DIRECTORIES(./include)
AUX_SOURCE_DIRECTORY(./src DIR_SRC)

# set output dir
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY output)

# if( CMAKE_RUNTIME_OUTPUT_DIRECTORY )
# 	set( executableOutputPath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
# elseif( EXECUTABLE_OUTPUT_PATH )
# 	set( executableOutputPath ${EXECUTABLE_OUTPUT_PATH} )
# else()
# 	set( executableOutputPath ${CMAKE_CURRENT_BINARY_DIR} )
# endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
# if(CMAKE_EXPORT_COMPILE_COMMANDS)
#   set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
#       ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
# endif()
add_executable(waybar-bluetooth_battery_parse ${DIR_SRC})
