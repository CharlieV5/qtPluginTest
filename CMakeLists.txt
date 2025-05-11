# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(CTKPluginExample)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets )

set(CMAKE_AUTOUIC ON)  # 自动处理ui文件, 自动处理ui文件是有前提的, 必须在需要编译的头文件(add_executable)中的某个头文件中包含ui_xxx.h(比如#include "ui_model002.h")
set(CMAKE_AUTOMOC ON)  # 自动调用moc(元对象编译器)
set(CMAKE_AUTORCC ON)  # 自动处理资源


# 定义统一的输出目录
set(BINARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/lib)

foreach(config IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${config} config_upper)
    # 可执行文件
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${BINARY_OUTPUT_DIR}/${config})
    # 动态库
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper} ${BINARY_OUTPUT_DIR}/${config}) # Windows DLL通常与EXE同目录
    # 静态库
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${LIB_OUTPUT_DIR}/${config})
endforeach()

include_directories(${CTK_INCLUDE_DIRS})
include_directories(${Qt5_INCLUDE_DIRS})

# set(CMAKE_DEBUG_POSTFIX "_d")

# 添加子目录
add_subdirectory(interfaces)
add_subdirectory(host)
add_subdirectory(my_plugin)

