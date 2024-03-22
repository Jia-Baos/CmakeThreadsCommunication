cmake_minimum_required(VERSION 3.27)

# # 指定生成类型
# set(CMAKE_BUILD_TYPE "Debug")

# # 设置编译器
# set(CMAKE_C_COMPILER D:/MinGW-Posix/bin/gcc.exe)
# set(CMAKE_CXX_COMPILER D:/MinGW-Posix/bin/g++.exe)

project(main)

# 引入自定义函数
include(${PROJECT_SOURCE_DIR}/func.cmake)
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 将源代码添加到此项目的可执行文件。
aux_source_directory(${CMAKE_SOURCE_DIR}/11-Demo1 main_files)
add_executable(main ${main_files})

set_target_properties(main
        PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# # 链接库头文件路径
# target_include_directories(main
#        PUBLIC ${CMAKE_SOURCE_DIR}/FMT/include/fmt)

# # 链接库文件路径
# target_link_directories(main
#        PUBLIC ${CMAKE_SOURCE_DIR}/FMT/lib)

# # 链接库文件名称
# target_link_libraries(main
#        PUBLIC
#        debug fmtd
#        optimized fmt
# )