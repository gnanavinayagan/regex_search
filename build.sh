#!/bin/bash
set -e

# Install dependencies
conan install . --install-folder=build --build=missing

# Build the project using conan build
conan build . --build-folder=build

echo "Build completed successfully. Executable is located at build/bin/regex_search"
