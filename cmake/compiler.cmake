# =============================================================================
# cmake/compiler.cmake - 编译器设置模块
# =============================================================================
# 功能说明：
#   - 设置 C++17 标准
#   - 统一输出目录
#   - 配置 GCC 警告选项
#   - 设置各构建类型的编译标志
# =============================================================================

# C++17 标准强制启用
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录统一设置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# =============================================================================
# 各构建类型的编译器标志
# =============================================================================

# 通用 C++ 标志
add_compile_options(
    -Wall -Wextra -Wpedantic -Wold-style-cast -Wnull-dereference
)

# Debug 模式
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -DDEBUG")

# Release 模式
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# RelWithDebInfo 模式
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DNDEBUG")

# MinSizeRel 模式
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os -DNDEBUG")
