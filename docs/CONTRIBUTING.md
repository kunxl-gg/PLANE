## CODE_FORMATTING.md

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
  1. Project headers
  2. System headers
  3. External library headers
  ```cpp
  #include "ring_buffer.hpp"
  #include <iostream>
  #include <vector>
  ```

## 4. Function Definitions
- Keep functions concise.
- Use `const` references when possible.
- Use `override` for overridden virtual functions:
  ```cpp
  class Derived : public Base {
      void execute() override;
  };
  ```

## 5. Multithreading
- Use `std::atomic<bool>` for shared flags.
- Use `std::this_thread::yield()` to reduce CPU usage in loops.

---

