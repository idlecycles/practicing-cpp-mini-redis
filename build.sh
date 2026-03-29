#!/bin/bash
set -e
 
BUILD_DIR="build"
CORES=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
 
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ..
make -j"$CORES"
 
echo ""
echo "=== Starting mini-redis ==="
echo ""
./mini-redis "$@"
 