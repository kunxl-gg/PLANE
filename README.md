## README.md

# Pipeline Processing System

This project implements a **multi-threaded pipeline** that:
1. Reads and processes data from a CSV file.
3. Applies a filtering algorithm to the data.

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
 ├📂 include        # Header files
 ├📂 src            # Source files
 ├📂 build          # Compiled binaries
 ├ CMakeLists.txt    # Build configuration
 ├ README.md         # Project documentation
 ├ CODE_FORMATTING.md# Coding style guide
```

## Contributing
1. Follow the [code formatting guidelines](CODE_FORMATTING.md).
2. Review the [architecture document](ARCHITECURE.md) for more insight into the implementation.
