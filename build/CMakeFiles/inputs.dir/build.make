# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/espian/random/advent_of_code_2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/espian/random/advent_of_code_2024/build

# Utility rule file for inputs.

# Include any custom commands dependencies for this target.
include CMakeFiles/inputs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/inputs.dir/progress.make

CMakeFiles/inputs:
	/usr/bin/cmake -E copy_directory /home/espian/random/advent_of_code_2024/src/inputs /home/espian/random/advent_of_code_2024/build/inputs

inputs: CMakeFiles/inputs
inputs: CMakeFiles/inputs.dir/build.make
.PHONY : inputs

# Rule to build all files generated by this target.
CMakeFiles/inputs.dir/build: inputs
.PHONY : CMakeFiles/inputs.dir/build

CMakeFiles/inputs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inputs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inputs.dir/clean

CMakeFiles/inputs.dir/depend:
	cd /home/espian/random/advent_of_code_2024/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/espian/random/advent_of_code_2024 /home/espian/random/advent_of_code_2024 /home/espian/random/advent_of_code_2024/build /home/espian/random/advent_of_code_2024/build /home/espian/random/advent_of_code_2024/build/CMakeFiles/inputs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inputs.dir/depend

