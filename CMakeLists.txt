cmake_minimum_required(VERSION 3.0)
project(waybar-bluetooth_battery_parse)

# 设置编译参数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# 添加头文件目录
include_directories(include)

# 获取src目录下的所有源文件
file(GLOB SOURCE_FILES "src/*.c")

# 生成可执行文件
add_executable(waybar-bluetooth_battery_parse ${SOURCE_FILES})

# 指定安装路径
install(TARGETS waybar-bluetooth_battery_parse DESTINATION /usr/local/bin)
