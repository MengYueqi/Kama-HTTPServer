#!/bin/bash
# ==========================================
# 🚀 One-click build script for MultiApps
# ==========================================

# 设置变量
BUILD_DIR="build"
BUILD_TYPE="Release"   # 或者 Debug
CMAKE_VERSION_REQUIRED="3.10"

# 清理并创建 build 目录
echo "🔧 Cleaning previous build..."
rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 检查 cmake 版本
CMAKE_VERSION=$(cmake --version | head -n1 | awk '{print $3}')
echo "🧱 CMake version: ${CMAKE_VERSION}"

# 运行 cmake 配置
echo "⚙️  Configuring project..."
cmake .. -DBUILD_AI_APPS=OFF -DBUILD_WEB_APPS=ON

# 编译
echo "🔨 Building..."
cmake --build . -- -j$(nproc)

# 返回上级目录
cd ..
# echo "✅ Build finished successfully!"
