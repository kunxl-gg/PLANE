# Parallel Line Scanner Architecture for Near real-time Execution

This project implements a **multi-threaded lock free ring buffer** for real-time line scanning that

## Installation
### Prerequisites
- C++20 Compiler (GCC, Clang, or MSVC)
- CMake 3.16+
- Visual Studio (Windows) or Make (Linux/macOS)

### Building
```sh
mkdir build
cd build
cmake ..
make -j$(nproc) # Use "cmake --build ." on Windows
```

## Usage
```sh
./pipeline_app
```

## Code Structure
```
📂 project_root
 ├📂 docs           # Documentation files
 ├📂 include        # Header files
 ├📂 src            # Source files
 ├📂 build          # Compiled binaries
 ├ CMakeLists.txt    # Build configuration
 ├ README.md         # Project documentation
```

## Contributing
1. Follow the [code formatting guidelines](https://github.com/kunxl-gg/PLANE/blob/main/docs/CONTRIBUTING.md).
2. Review the [architecture document](https://github.com/kunxl-gg/PLANE/blob/main/docs/ARCHITECTURE.md).
