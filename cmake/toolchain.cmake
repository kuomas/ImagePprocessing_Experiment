# =============================================================================
# cmake/toolchain.cmake - GCC 工具链配置（Windows MinGW）
# =============================================================================
# 功能说明：
#   - 指定目标系统为 Windows
#   - 配置 GCC/G++ 编译器
#   - 设置变量查找模式
# =============================================================================

# Windows 平台
set(CMAKE_SYSTEM_NAME "Windows" CACHE STRING "Target system name")
set(CMAKE_SYSTEM_PROCESSOR "x86_64" CACHE STRING "Target processor")

# GCC 编译器绝对路径
set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

# 环境变量：将 MinGW bin 目录加入 PATH，确保运行时能找到动态库
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM "BOTH" CACHE STRING "Program search mode")
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY "BOTH" CACHE STRING "Library search mode")
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE "BOTH" CACHE STRING "Include search mode")
