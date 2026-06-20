# =============================================================================
# external/CMakeLists.txt - 第三方库配置
# =============================================================================
# 功能说明：
#   - 通过 FetchContent 自动下载第三方库（网络优先）
#   - 如果本地目录已存在，则直接使用本地库
#   - googletest 测试框架
# =============================================================================
# 添加第三方库的方式：
#   1. 在 FetchContent_Declare 中配置 GIT_REPOSITORY 和 GIT_TAG
#   2. 使用 FetchContent_MakeAvailable() 引入
#   3. 在目标中通过 target_link_libraries() 链接
# =============================================================================
# Google Test 测试框架
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/googletest")
    # 本地不存在，通过 FetchContent 自动下载
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/googletest"
    )
    FetchContent_MakeAvailable(googletest)
else()
    # 本地已存在，直接引入
    add_subdirectory(googletest)
endif()

# 抑制 gtest 的某个编译警告
target_compile_options(gtest PRIVATE -Wno-null-dereference)
