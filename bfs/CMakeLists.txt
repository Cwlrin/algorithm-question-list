# 获取所有.cpp文件
file(GLOB_RECURSE SOURCES "*.cpp")

# 定义一个函数来清理文件名，使其适合作为目标名称
function(clean_filename_for_target input output)
    string(REGEX REPLACE "[^A-Za-z0-9_]" "" _cleaned_name "${input}")
    set(${output} "${_cleaned_name}" PARENT_SCOPE)
endfunction()

# 遍历所有源文件并为每个文件创建一个可执行文件
foreach(SOURCE IN LISTS SOURCES)
    # 获取不带路径和扩展名的文件名作为目标名称
    get_filename_component(TARGET_NAME ${SOURCE} NAME_WE)

    # 清理目标名称以适配CMake要求
    clean_filename_for_target("${TARGET_NAME}" CLEANED_TARGET_NAME)

    # 添加可执行文件
    add_executable(${CLEANED_TARGET_NAME} ${SOURCE})

    # 如果有共同的链接库或包含路径，可以在foreach循环外定义，然后在这里链接它们
    # target_link_libraries(${CLEANED_TARGET_NAME} PRIVATE your_library)
endforeach()