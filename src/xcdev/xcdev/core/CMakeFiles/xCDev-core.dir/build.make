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
CMAKE_SOURCE_DIR = /home/lgl/master/SCARA/xCLib/src/xcdev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lgl/master/SCARA/xCLib/src/xcdev

# Include any dependencies generated for this target.
include xcdev/core/CMakeFiles/xCDev-core.dir/depend.make

# Include the progress variables for this target.
include xcdev/core/CMakeFiles/xCDev-core.dir/progress.make

# Include the compile flags for this target's objects.
include xcdev/core/CMakeFiles/xCDev-core.dir/flags.make

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o: xcdev/core/CMakeFiles/xCDev-core.dir/flags.make
xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o: xcdev/core/network_based_dev.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lgl/master/SCARA/xCLib/src/xcdev/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o"
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o -c /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core/network_based_dev.cpp

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xCDev-core.dir/network_based_dev.cpp.i"
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core/network_based_dev.cpp > CMakeFiles/xCDev-core.dir/network_based_dev.cpp.i

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xCDev-core.dir/network_based_dev.cpp.s"
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core/network_based_dev.cpp -o CMakeFiles/xCDev-core.dir/network_based_dev.cpp.s

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.requires:
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.requires

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.provides: xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.requires
	$(MAKE) -f xcdev/core/CMakeFiles/xCDev-core.dir/build.make xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.provides.build
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.provides

xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.provides.build: xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o

# Object files for target xCDev-core
xCDev__core_OBJECTS = \
"CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o"

# External object files for target xCDev-core
xCDev__core_EXTERNAL_OBJECTS =

lib/libxCDev-core.a: xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o
lib/libxCDev-core.a: xcdev/core/CMakeFiles/xCDev-core.dir/build.make
lib/libxCDev-core.a: xcdev/core/CMakeFiles/xCDev-core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libxCDev-core.a"
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && $(CMAKE_COMMAND) -P CMakeFiles/xCDev-core.dir/cmake_clean_target.cmake
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xCDev-core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
xcdev/core/CMakeFiles/xCDev-core.dir/build: lib/libxCDev-core.a
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/build

xcdev/core/CMakeFiles/xCDev-core.dir/requires: xcdev/core/CMakeFiles/xCDev-core.dir/network_based_dev.cpp.o.requires
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/requires

xcdev/core/CMakeFiles/xCDev-core.dir/clean:
	cd /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core && $(CMAKE_COMMAND) -P CMakeFiles/xCDev-core.dir/cmake_clean.cmake
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/clean

xcdev/core/CMakeFiles/xCDev-core.dir/depend:
	cd /home/lgl/master/SCARA/xCLib/src/xcdev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lgl/master/SCARA/xCLib/src/xcdev /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core /home/lgl/master/SCARA/xCLib/src/xcdev /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core /home/lgl/master/SCARA/xCLib/src/xcdev/xcdev/core/CMakeFiles/xCDev-core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xcdev/core/CMakeFiles/xCDev-core.dir/depend
