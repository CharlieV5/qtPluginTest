# 构建主机应用程序
add_executable(qt_plugin_host
    main.cpp
    hostwindow.h
    hostwindow.cpp
)

# 链接 Qt 库
target_link_libraries(qt_plugin_host
    PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# 包含头文件目录，包括接口目录
target_include_directories(qt_plugin_host
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../interfaces # 包含接口头文件
)

set_target_properties(qt_plugin_host PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
