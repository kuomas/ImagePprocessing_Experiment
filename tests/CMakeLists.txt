# =============================================================================
# tests/CMakeLists.txt - 测试目录 CMake 配置
# =============================================================================
# 功能说明：
#   - 定义测试可执行文件
#   - 链接 Google Test 框架
#   - 自动注册测试用例
#   - 注册到 CTest 测试管理器
# =============================================================================

# 测试可执行文件
add_executable(
    ${PROJECT_NAME}_tests
    test_main.cpp
)

# 配置头文件搜索路径
target_include_directories(
    ${PROJECT_NAME}_tests
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# 链接 Google Test 框架
target_link_libraries(
    ${PROJECT_NAME}_tests
    PRIVATE gtest_main
)

# 强制使用 C++17 标准
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_17)

# 使用 gtest_discover_tests 自动注册 Google Test 测试用例
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

# 注册测试到 CTest 测试管理器
add_test(NAME ${PROJECT_NAME}_Tests
         COMMAND ${PROJECT_NAME}_tests
)
