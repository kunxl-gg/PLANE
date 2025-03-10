# Code Formatting Guidelines

To maintain a consistent and readable codebase, follow these formatting guidelines.

## 1. General Formatting
- Use **tabs** for indentation.
- Keep line length **under 100 characters**.
- Use **brace style**:
```cpp
    if (condition) {
      doSomething();
    } else {
      doSomethingElse();
    }
```
- Place a **space** between keywords and opening parentheses:
```cpp
    while (true) { ... }
```

## 2. Naming Conventions
- **Classes & Structs**: `PascalCase`
```cpp
    class DataGenerationBlock { ... };
```
- **Variables & Functions**: `camelCase`
```cpp
    int bufferSize;
    void processBatch();
```
- **Member Variables**: Prefix with `_`
```cpp
    class Example {
      int _count;
    };
```

## 3. Header Files
- Use include guards or `#pragma once`
```cpp
    #ifndef EXAMPLE_H
    #define EXAMPLE_H
    // Code
    #endif // EXAMPLE_H
```
- Order includes as:
  1. System headers
  2. External library headers
  3. Project headers
```cpp
    #include <iostream>
    #include <vector>

    #include "ring_buffer.hpp"
```

## 4. Pre-Processor Directives
- Do not use indentation before pre-processor directives.
```cpp
#ifdef EXAMPLE_H
#define EXAMPLE_H
// Code
#endif // EXAMPLE_H
```
---

