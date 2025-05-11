# 构建插件共享库
add_library(MyPlugin SHARED
    myplugin.h
    myplugin.cpp
    myplugin.json # 添加元数据文件
)

# 链接 Qt 库
target_link_libraries(MyPlugin
    PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# 包含头文件目录，包括接口目录
target_include_directories(MyPlugin
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../interfaces # 包含接口头文件
)

foreach(config IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${config} config_upper)
    # 可执行文件
    set_target_properties(MyPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${BINARY_OUTPUT_DIR}/${config}/plugins)
    # 动态库
    set_target_properties(MyPlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${config_upper} ${BINARY_OUTPUT_DIR}/${config}/plugins) # Windows DLL通常与EXE同目录
    # 静态库
    set_target_properties(MyPlugin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${LIB_OUTPUT_DIR}/${config}/plugins)
endforeach()
