# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wwt/WebServer_sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wwt/WebServer_sylar/build

# Include any dependencies generated for this target.
include CMakeFiles/bin_sylar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bin_sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bin_sylar.dir/flags.make

CMakeFiles/bin_sylar.dir/src/main.cpp.o: CMakeFiles/bin_sylar.dir/flags.make
CMakeFiles/bin_sylar.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wwt/WebServer_sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bin_sylar.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"src/main.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bin_sylar.dir/src/main.cpp.o -c /home/wwt/WebServer_sylar/src/main.cpp

CMakeFiles/bin_sylar.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bin_sylar.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"src/main.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wwt/WebServer_sylar/src/main.cpp > CMakeFiles/bin_sylar.dir/src/main.cpp.i

CMakeFiles/bin_sylar.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bin_sylar.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"src/main.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wwt/WebServer_sylar/src/main.cpp -o CMakeFiles/bin_sylar.dir/src/main.cpp.s

# Object files for target bin_sylar
bin_sylar_OBJECTS = \
"CMakeFiles/bin_sylar.dir/src/main.cpp.o"

# External object files for target bin_sylar
bin_sylar_EXTERNAL_OBJECTS =

../bin/sylar: CMakeFiles/bin_sylar.dir/src/main.cpp.o
../bin/sylar: CMakeFiles/bin_sylar.dir/build.make
../bin/sylar: ../lib/libsylar.so
../bin/sylar: /usr/lib64/libssl.so
../bin/sylar: /usr/lib64/libcrypto.so
../bin/sylar: CMakeFiles/bin_sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wwt/WebServer_sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/sylar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bin_sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bin_sylar.dir/build: ../bin/sylar

.PHONY : CMakeFiles/bin_sylar.dir/build

CMakeFiles/bin_sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bin_sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bin_sylar.dir/clean

CMakeFiles/bin_sylar.dir/depend:
	cd /home/wwt/WebServer_sylar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wwt/WebServer_sylar /home/wwt/WebServer_sylar /home/wwt/WebServer_sylar/build /home/wwt/WebServer_sylar/build /home/wwt/WebServer_sylar/build/CMakeFiles/bin_sylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bin_sylar.dir/depend

