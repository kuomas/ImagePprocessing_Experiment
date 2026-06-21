# =============================================================================
# src/CMakeLists.txt - 源代码目录 CMake 配置
# =============================================================================
# 功能说明：
#   - 定义主程序可执行文件
#   - 配置头文件搜索路径
#   - 设置 C++17 标准
#   - 传递项目版本信息
#   - 可选启用测试宏定义
# =============================================================================

# 主程序
add_executable(
    ${PROJECT_NAME}
    main.cpp
    exp1_main.cpp
    hist.cpp
)

# 配置头文件搜索路径（公共）
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

# 强制使用 C++17 标准
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# =============================================================================
# 注意：如需添加库文件，使用 target_link_libraries() 链接
# 例如：target_link_libraries(${PROJECT_NAME} PRIVATE some_lib::some_lib)
# =============================================================================

# 传递项目名称和版本号给编译器
target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE PROJECT_NAME="${PROJECT_NAME}" PROJECT_VERSION="${PROJECT_VERSION}"
)

# 当构建测试时，启用 ENABLE_TESTS 宏定义
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_TESTS)
endif()
