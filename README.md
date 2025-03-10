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
Make sure to have **`config.txt`** and **`data.csv`** in the same directory, as the application requires them for configuration and input data.

### Configuration File Format (`config.txt`)
The `config.txt` file should follow this pattern:

```
<number_of_samples>
<number_of_iterations>
<weight_vector_values (space-separated)>
```

## Code Structure
```
project_root
├── docs           # Documentation files
├── include        # Header files
├── src            # Source files
├── build          # Compiled binaries
├── CMakeLists.txt # Build configuration
└── README.md      # Project documentation
```

## Contributing
1. Follow the [code formatting guidelines](https://github.com/kunxl-gg/PLANE/blob/main/docs/CONTRIBUTING.md).
2. Review the [architecture document](https://github.com/kunxl-gg/PLANE/blob/main/docs/ARCHITECTURE.md).
