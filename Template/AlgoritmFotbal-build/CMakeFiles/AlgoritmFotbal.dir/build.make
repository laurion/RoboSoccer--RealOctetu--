# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build

# Include any dependencies generated for this target.
include CMakeFiles/AlgoritmFotbal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AlgoritmFotbal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AlgoritmFotbal.dir/flags.make

CMakeFiles/AlgoritmFotbal.dir/main.cpp.o: CMakeFiles/AlgoritmFotbal.dir/flags.make
CMakeFiles/AlgoritmFotbal.dir/main.cpp.o: /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AlgoritmFotbal.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AlgoritmFotbal.dir/main.cpp.o -c /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal/main.cpp

CMakeFiles/AlgoritmFotbal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoritmFotbal.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal/main.cpp > CMakeFiles/AlgoritmFotbal.dir/main.cpp.i

CMakeFiles/AlgoritmFotbal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoritmFotbal.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal/main.cpp -o CMakeFiles/AlgoritmFotbal.dir/main.cpp.s

CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.requires

CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.provides: CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoritmFotbal.dir/build.make CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.provides

CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.provides.build: CMakeFiles/AlgoritmFotbal.dir/main.cpp.o

# Object files for target AlgoritmFotbal
AlgoritmFotbal_OBJECTS = \
"CMakeFiles/AlgoritmFotbal.dir/main.cpp.o"

# External object files for target AlgoritmFotbal
AlgoritmFotbal_EXTERNAL_OBJECTS =

AlgoritmFotbal: CMakeFiles/AlgoritmFotbal.dir/main.cpp.o
AlgoritmFotbal: CMakeFiles/AlgoritmFotbal.dir/build.make
AlgoritmFotbal: /usr/lib/libmosquitto.so
AlgoritmFotbal: CMakeFiles/AlgoritmFotbal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AlgoritmFotbal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AlgoritmFotbal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AlgoritmFotbal.dir/build: AlgoritmFotbal
.PHONY : CMakeFiles/AlgoritmFotbal.dir/build

CMakeFiles/AlgoritmFotbal.dir/requires: CMakeFiles/AlgoritmFotbal.dir/main.cpp.o.requires
.PHONY : CMakeFiles/AlgoritmFotbal.dir/requires

CMakeFiles/AlgoritmFotbal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AlgoritmFotbal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AlgoritmFotbal.dir/clean

CMakeFiles/AlgoritmFotbal.dir/depend:
	cd /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build /home/razvan/Documents/FotbalRobotic/Template/AlgoritmFotbal-build/CMakeFiles/AlgoritmFotbal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AlgoritmFotbal.dir/depend

