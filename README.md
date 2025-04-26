# Regex Search Tool

A C++ utility for regex searching and replacing using the Boost regex library.

## Features

- Find all regex matches in a string or file
- Find first regex match in a string or file
- Replace all regex matches with a specified replacement
- Check if a regex pattern matches an entire string
- Support for Boost regex syntax and features

## Requirements

- C++17 compatible compiler
- Python 3.6 or higher
- CMake 3.15 or higher
- Conan package manager 1.x
- Boost 1.70 or higher (automatically installed with Conan)

## Installation of Prerequisites

### Windows

1. **Install Python**:
   - Download the installer from [python.org](https://www.python.org/downloads/windows/)
   - Run the installer and make sure to check "Add Python to PATH"
   - Verify installation by opening Command Prompt and typing:
     ```
     python --version
     ```

2. **Install CMake**:
   - Download the installer from [cmake.org](https://cmake.org/download/)
   - Run the installer and follow the instructions
   - Choose to add CMake to the system PATH during installation
   - Verify installation:
     ```
     cmake --version
     ```

3. **Install Conan**:
   - Open Command Prompt and run:
     ```
     pip install conan==1.59.0
     ```
   - Verify installation:
     ```
     conan --version
     ```

4. **Install Visual Studio (if needed)**:
   - Download Visual Studio from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/downloads/)
   - Make sure to include "Desktop development with C++" workload during installation

### macOS

1. **Install Homebrew** (if not already installed):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install Python**:
   ```bash
   brew install python
   python3 --version
   ```

3. **Install CMake**:
   ```bash
   brew install cmake
   cmake --version
   ```

4. **Install Conan**:
   ```bash
   pip3 install conan==1.59.0
   conan --version
   ```

5. **Install Xcode Command Line Tools** (if needed):
   ```bash
   xcode-select --install
   ```

### Linux (Ubuntu/Debian)

1. **Install Python**:
   ```bash
   sudo apt update
   sudo apt install python3 python3-pip
   python3 --version
   ```

2. **Install CMake**:
   ```bash
   sudo apt install cmake
   cmake --version
   ```

3. **Install Conan**:
   ```bash
   pip3 install conan==1.59.0
   conan --version
   ```

4. **Install GCC and development tools**:
   ```bash
   sudo apt install build-essential
   ```

## Building

### Using Conan

```bash
# Clone the repository and navigate to the project directory
git clone https://github.com/gnanavinayagan/regex_search.git
cd regex_search

# Install dependencies and build with a single command
conan install . --install-folder=build --build=missing
conan build . --build-folder=build
```

Alternatively, you can use the provided build script:

```bash
# On Linux/macOS
./build.sh

# On Windows
build.bat
```

## Running Tests

Tests are automatically run during the build process. You can also run them manually:

```bash
cd build
ctest -C Release
```

## Usage

### Command Line Interface

```
regex_search [command] [pattern] [text]
regex_search [command] [pattern] -f [filename]
```

### Commands

- `find` - Find all matches of pattern in text
- `first` - Find first match of pattern in text
- `replace` - Replace all occurrences of pattern with text
- `match` - Check if pattern matches entire text

### Examples

```bash
# Find all numbers in a string
./build/bin/regex_search find "\\d+" "abc123def456"

# Replace numbers with a formatted string
./build/bin/regex_search replace "(\\d+)" "num=$1" "abc123def456"

# Find all words in a file
./build/bin/regex_search find "\\w+" -f input.txt

# Check if a string is an email address
./build/bin/regex_search match "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$" "user@example.com"
```

## Library Usage

You can also use the library in your own C++ code:

```cpp
#include "regex_searcher.hpp"
#include <iostream>

int main() {
    regex_tools::RegexSearcher searcher("\\d+");
    
    auto matches = searcher.findAll("abc123def456");
    for (const auto& match : matches) {
        std::cout << "Found: " << match << std::endl;
    }
    
    std::string replaced = searcher.replaceAll("abc123def456", "NUMBER");
    std::cout << "Replaced: " << replaced << std::endl;
    
    return 0;
}
```

## Using as a Conan Package

You can also use this project as a Conan package in your own projects:

```bash
# Create a Conan package from the project
cd regex_search
conan create . bheemboy/stable
```

Then in your project's conanfile.txt:

```
[requires]
regex_search/1.0.0@bheemboy/stable
```

Or in your conanfile.py:

```python
def requirements(self):
    self.requires("regex_search/1.0.0@bheemboy/stable")
```

## Troubleshooting

### Common Issues

1. **Conan profile not configured**:
   - If you encounter errors about missing compilers, set up a default profile:
     ```bash
     conan profile new default --detect
     ```

2. **CMake not finding Boost**:
   - Ensure you've run `conan install` before `conan build`
   - Check if the `conanbuildinfo.cmake` file exists in your build directory

3. **Build errors on Windows**:
   - Make sure you're using the right generator for your version of Visual Studio:
     ```bash
     conan install . -g cmake_multi -s build_type=Release -s build_type=Debug
     ```

4. **Library not found during runtime**:
   - Make sure the runtime libraries are copied to the bin directory (this should happen automatically during the build)

## License

This project is licensed under the MIT License - see the LICENSE file for details.
