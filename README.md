# Parallel Line Scanner Architecture for Near real-time Execution

This project implements a **multi-threaded lock free ring buffer** for real-time line scanning that

## Installation
### Prerequisites
- C++20 Compiler (GCC, Clang, or MSVC)
- CMake 3.16+
- Visual Studio (Windows) or Make (Linux/macOS)

## **Building with Make**
### **Requirements**
- GCC or Clang
- `make`

### **Build Commands**
#### **Debug Build**
```sh
make debug
```
To run the debug build:
```sh
make run
```

#### **CSV Mode Build**
```sh
make build
```
To run the CSV mode build:
```sh
make run
```

---

## **Building with CMake**
### **Requirements**
- CMake 3.16+
- A C++20 compatible compiler (GCC, Clang, MSVC)

### **Build Commands**
#### **Debug Build (Makefiles/Ninja)**
```sh
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

#### **Release Build (Makefiles/Ninja)**
```sh
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

#### **Debug Build (Visual Studio / Multi-Config Generators)**
```sh
mkdir -p build
cmake -S . -B build
cmake --build build --config Debug
```
For release mode:
```sh
cmake --build build --config Release
```

## Usage
```sh
./cnynlr
```
Make sure to have **`config.txt`** and **`data.csv`** in the same directory, as the application requires them for configuration and input data.

### Configuration File Format (`config.txt`)
The `config.txt` file should follow this pattern:

```
<threshold>
<time_to_run_the_experiment_for_outside_of_CSV_mode>
<time_period_for_each_block>
<weights_for_filter>
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
