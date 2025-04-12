# Parallel Line Scanner Architecture for Near real-time Execution

This project implements a **multi-threaded lock free ring buffer** for real-time line scanning that

## Installation
### Prerequisites
- C++20 Compiler (GCC, Clang, or MSVC)
- CMake 3.16+
- Visual Studio (Windows) or Make (Linux/macOS)

## Build Instructions
- Use Release Mode to read from CSV 
- Use Debug Mode to generate random data. 

Make sure to have **`config.txt`** and **`data.csv`** in the same directory, as the application requires them for configuration and input data.

### Configuration File Format (`config.txt`)
The `config.txt` file should follow this pattern:

```
<path_to_csv_file>
<threshold>
<time_to_run_the_experiment_for_outside_of_CSV_mode (in milliseconds)>
<time_period_for_each_block (in ns)>
<weights_for_filter>
```
The final output after the entire program has run is stored in **output.txt**

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
