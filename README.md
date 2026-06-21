
# 数字图像处理实验项目

本项目是一个基于 C++ 和 OpenCV 的数字图像处理实验，包含多个图像处理算法的实现与可视化实验。项目使用 CMake 作为构建系统，支持多实验并行开发与管理。

## 📋 实验环境

| 项目 | 配置 |
|------|------|
| 操作系统 | Windows 11 |
| 编译器 | MinGW64 g++ (GCC 11.2.0) |
| OpenCV | 4.6.0 |
| 构建系统 | CMake 3.21+ / Ninja |
| 开发工具 | VSCode |

## 🔧 构建与运行

### 构建方式

项目使用 CMake 预设配置，支持多种构建模式：

```bash
# 配置 Debug 版本
cmake --preset=debug
cmake --build --preset=debug

# 配置 Release 版本
cmake --preset=release
cmake --build --preset=release

# 配置 RelWithDebInfo 版本
cmake --preset=relwithdebinfo
cmake --build --preset=relwithdebinfo
```

### 运行实验

```bash
# 运行默认实验
./build/debug/ImagePprocessing_Experiment

```

## 📚 实验内容

### EXP_1：灰度直方图与图像增强

实现并可视化图像灰度直方图计算、均衡化及图像增强功能。

**功能列表：**
- 读取摄像头视频流
- 计算灰度直方图
- 实时绘制并显示直方图
- 直方图均衡化处理
- 均衡化后的图像增强
- 多线程图像处理与显示

### EXP_2：双边滤波

实现双边滤波算法，用于图像去噪同时保留边缘信息。

**功能列表：**
- 自定义双边滤波算法实现
- 使用双边滤波算法对图像降噪处理
- 原图与处理结果对比显示

### EXP_3：图像纹理特征提取

基于灰度共生矩阵（GLCM）实现图像纹理特征分析与可视化。

**功能列表：**
- 灰度共生矩阵计算（参考 MATLAB 实现）[Matlab](https://ww2.mathworks.cn/help/images/ref/graycomatrix.html)
- 随机图像块采样与纹理特征重复计算
- 特征向量统计分析
- 特征散点图可视化：
  - 能量 vs 熵
  - 相关性 vs 对比度

### EXP_4：色彩鲜艳度调整

实现图像色彩鲜艳度调节功能。

**功能列表：**
- 读取图像
- 调整色彩鲜艳度
- 结果实时预览显示

##### EXP_5 模板匹配

- 实现模板匹配算法
- 使用实现的模板匹配算法在一张图像中找到指定目标
- 显示结果

### EXP_6：K-Means 图像分割

实现 K-Means 聚类算法用于图像分割。

**功能列表：**
- K-Means 聚类算法实现
- 图像像素聚类分割
- 分割结果可视化显示
