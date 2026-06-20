# =============================================================================
# CMakeTemplate - 根 CMake 配置文件
# =============================================================================
# 功能说明：
#   - 设置 CMake 最低版本要求（3.31+）
#   - 自动获取项目文件夹名作为 PROJECT_NAME
#   - 配置默认构建类型为 Release
#   - 引入编译器设置模块
#   - 添加 src、external 子目录
#   - 可选添加 tests 子目录（需开启 BUILD_TESTS 选项）
# =============================================================================

cmake_minimum_required(VERSION 3.31)

# 自动获取项目根目录文件夹名作为 PROJECT_NAME
get_filename_component(PROJECT_DIR_NAME "${CMAKE_SOURCE_DIR}" NAME)

project(${PROJECT_DIR_NAME}
        VERSION 1.0.0
        DESCRIPTION "A modern CMake project template"
        LANGUAGES CXX
)

# 强制指定默认构建类型（默认为 Release）
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel"
                                                     "RelWithDebInfo"
    )
endif()

# 添加自定义 CMake 模块搜索路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# 引入编译器设置模块（包含 C++ 标准、警告、构建标志等）
include(compiler)

# =============================================================================
# 添加子目录
# =============================================================================

# 源代码目录
add_subdirectory(src)

# 第三方库目录（通过 FetchContent 管理依赖）
add_subdirectory(external)

# =============================================================================
# 测试配置（可选）
# =============================================================================
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
