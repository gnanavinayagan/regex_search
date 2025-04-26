from conans import ConanFile, CMake, tools
import os


class RegexSearchConan(ConanFile):
    name = "regex_search"
    version = "1.0.0"
    
    # Optional metadata
    license = "MIT"
    author = "Gnana Vinayagan <gnanavinayagan@iitb.ac.in>"
    url = "https://github.com/gnanavinayagan/regex_search"
    description = "A C++ utility for regex searching and replacing using the Boost regex library"
    topics = ("regex", "search", "boost", "utility")
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    
    # Sources are located in the same place as this recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "test/*", "cmake/*"
    
    generators = "cmake", "cmake_find_package"
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def requirements(self):
        self.requires("boost/1.80.0")
    
    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure(source_folder=self.source_folder)
        return cmake
    
    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        
        # Run tests if not cross-building
        if not tools.cross_building(self):
            cmake.test()
    
    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
    
    def package_info(self):
        self.cpp_info.libs = ["regex_lib"]
        
        # Add executable to PATH
        bindir = os.path.join(self.package_folder, "bin")
        self.env_info.PATH.append(bindir)
        
    def imports(self):
        # Copy shared libraries into the build folder for runtime
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
