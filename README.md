# Template - CMake 项目模板

一个基于现代 CMake 的 C++17 项目模板，使用 CMake + Ninja + GCC (MinGW) 工具链。

## 目录结构

```
CMakeTemplate/
├── cmake/                    # CMake 配置
│   ├── compiler.cmake        # 编译器设置（C++17、警告、优化）
│   └── toolchain.cmake       # 工具链配置（Windows MinGW）
├── external/                 # 第三方库（通过 FetchContent 管理）
│   └── CMakeLists.txt        # 外部库统一管理
├── include/                  # 公共头文件
├── src/                      # 源代码
│   ├── CMakeLists.txt        # 源码目录配置
│   └── main.cpp              # 主程序入口
├── tests/                    # 测试代码
│   ├── CMakeLists.txt        # 测试目录配置
│   └── test_main.cpp         # Google Test 测试用例
├── CMakeLists.txt            # 根 CMake 配置
├── CMakePresets.json         # CMake 预设（构建/测试）
└── README.md                 # 本文件
```

## 功能特性

- **现代 CMake**: 使用 CMake 3.21+ 的最佳实践
- **C++17 标准**: 强制启用 C++17 特性
- **构建预设**: 支持 Debug/Release/RelWithDebInfo 多种构建配置
- **测试框架**: 集成 Google Test 进行单元测试（通过 FetchContent 自动下载）

## 快速开始

### 环境要求

| 工具 | 版本 | 说明 |
|------|------|------|
| CMake | 3.21+ | 构建系统 |
| Ninja | 最新稳定版 | 构建生成器 |
| GCC (MinGW) | 11+ | Windows 编译器 |
| C++ 标准 | C++17 | 强制启用 |

### 配置项目

```powershell
# 使用预设配置（Debug）
cmake --preset debug

# 或使用 Release
cmake --preset release
```

### 构建项目

```powershell
# Debug 模式
cmake --build build/debug

# Release 模式
cmake --build build/release
```

### 运行程序

```powershell
.\build\debug\bin\<项目名>.exe
```

### 运行测试

```powershell
# 配置并构建测试
cmake --preset debug

# 运行测试
ctest --test-dir build/debug --output-on-failure
```

## 添加新代码模块

### 添加源文件

直接在 `src/` 目录下添加 `.cpp` 文件，然后在 `src/CMakeLists.txt` 中引用。

### 添加头文件

将公共头文件放在 `include/` 目录下，项目中通过 `#include "header.h"` 引用即可。

### 添加新模块（子目录）

1. 在 `src/` 下创建新目录（如 `src/network/`）
2. 在该目录下创建 `CMakeLists.txt`
3. 在 `src/CMakeLists.txt` 中通过 `add_subdirectory()` 引用

## 添加第三方库

1. 第三方库会通过 `external/CMakeLists.txt` 中的 FetchContent 自动下载
2. 在 `external/CMakeLists.txt` 中添加 FetchContent 配置

```cmake
# external/CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
    some_lib
    GIT_REPOSITORY https://github.com/xxx/some_lib.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(some_lib)
```

3. 在目标中通过 `target_link_libraries()` 链接

```cmake
# src/CMakeLists.txt
target_link_libraries(${PROJECT_NAME} PRIVATE some_lib::some_lib)
```

## 构建预设说明

| 预设 | 构建类型 | 说明 |
|------|----------|------|
| `debug` | Debug | 无优化，带调试信息 |
| `release` | Release | 最大优化，无调试信息 |
| `relwithdebinfo` | RelWithDebInfo | 适度优化，带调试信息 |