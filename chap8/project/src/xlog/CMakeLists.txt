# xcpp/src/xlog/cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(xlog)

# 当前cmake路径的txt
# 注意是当前的路径，而不是cmake_source_dir（这个可能是父目录的）
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SRC)

# 加入.h文件到编译依赖中
# 但是有点问题，这个
FILE(GLOB H_FILE "${CMAKE_CURRENT_LIST_DIR}/*.h")

# 对外接口的头文件，对应的属性也就是interface
FILE(GLOB H_FILE_I "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

add_library(${PROJECT_NAME} ${SRC} ${H_FILE})

# 设置头文件查找路径
# 在配置安装的时候，出现错误，说的是：INTERFACE_INCLUDE_DIRECTORIES
# ---- 解决方案：将 public --> private
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/
    ${CMAKE_CURRENT_LIST_DIR}
)

# 配置C++参数
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# 默认为debug版
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(MSVC)
    set(CONF_TYPES Debug Release RelWithDebInfo MinSizeRel)

    foreach(t IN LISTS CONF_TYPES)
        set_target_properties(
            ${PROJECT_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${t} ${CMAKE_CURRENT_LIST_DIR}/../../bin # dll、exe、out
            LIBRARY_OUTPUT_DIRECTORY_${t} ${CMAKE_CURRENT_LIST_DIR}/../../lib # .so .dylib .lib
            ARCHIVE_OUTPUT_DIRECTORY_${t} ${CMAKE_CURRENT_LIST_DIR}/../../lib # .lib
            PDB_OUTPUT_DIRECTORY_${t} ${CMAKE_CURRENT_LIST_DIR}/../../bin # pdb
        )
    endforeach(t IN LISTS CONF_TYPES)

    # 配置vs属性 bigobj，就是qt，vs处理的时候甚至是会把图片也一起打包到项目中
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        COMPILE_FLAGS "-bigobj"
    )

    # 设置debug添加d后缀
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "d"
    )

    # 静态库和动态库传递不同的宏变量
    # XLOG_STATIC XLOG_EXPORTS
    target_compile_definitions(
        ${PROJECT_NAME} PUBLIC XLOG_STATIC
    )
else()
    # 配置输出路径，我们这里要求：debug release版本输出路径一致
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../bin # dll、exe、out
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../lib # .so .dylib .lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../lib # .lib
        PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../bin # pdb
    )
endif()

set(CMAKE_INSTALL_PREFIX "out")

# 设置头文件
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    PUBLIC_HEADER "${H_FILE_I}"
)

# 安装库是：${CMAKE_INSTALL_PREFIX}
# 安装库
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include # 设置玩了头文件，不要忘了设置安装路径
)

# 支持配置文件，配置文件就是find_package
install(
    EXPORT ${PROJECT_NAME} # 设置这一行的同时，不要忘记设置安装库的export
    FILE ${PROJECT_NAME}Config.cmake
    DESTINATION lib/config/
)

# 支持版本文件
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
)