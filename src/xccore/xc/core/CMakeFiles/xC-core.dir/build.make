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
CMAKE_SOURCE_DIR = /home/lgl/master/SCARA/xCLib/src/xccore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lgl/master/SCARA/xCLib/src/xccore

# Include any dependencies generated for this target.
include xc/core/CMakeFiles/xC-core.dir/depend.make

# Include the progress variables for this target.
include xc/core/CMakeFiles/xC-core.dir/progress.make

# Include the compile flags for this target's objects.
include xc/core/CMakeFiles/xC-core.dir/flags.make

xc/core/CMakeFiles/xC-core.dir/core.cpp.o: xc/core/CMakeFiles/xC-core.dir/flags.make
xc/core/CMakeFiles/xC-core.dir/core.cpp.o: xc/core/core.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lgl/master/SCARA/xCLib/src/xccore/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object xc/core/CMakeFiles/xC-core.dir/core.cpp.o"
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/xC-core.dir/core.cpp.o -c /home/lgl/master/SCARA/xCLib/src/xccore/xc/core/core.cpp

xc/core/CMakeFiles/xC-core.dir/core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xC-core.dir/core.cpp.i"
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lgl/master/SCARA/xCLib/src/xccore/xc/core/core.cpp > CMakeFiles/xC-core.dir/core.cpp.i

xc/core/CMakeFiles/xC-core.dir/core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xC-core.dir/core.cpp.s"
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lgl/master/SCARA/xCLib/src/xccore/xc/core/core.cpp -o CMakeFiles/xC-core.dir/core.cpp.s

xc/core/CMakeFiles/xC-core.dir/core.cpp.o.requires:
.PHONY : xc/core/CMakeFiles/xC-core.dir/core.cpp.o.requires

xc/core/CMakeFiles/xC-core.dir/core.cpp.o.provides: xc/core/CMakeFiles/xC-core.dir/core.cpp.o.requires
	$(MAKE) -f xc/core/CMakeFiles/xC-core.dir/build.make xc/core/CMakeFiles/xC-core.dir/core.cpp.o.provides.build
.PHONY : xc/core/CMakeFiles/xC-core.dir/core.cpp.o.provides

xc/core/CMakeFiles/xC-core.dir/core.cpp.o.provides.build: xc/core/CMakeFiles/xC-core.dir/core.cpp.o

# Object files for target xC-core
xC__core_OBJECTS = \
"CMakeFiles/xC-core.dir/core.cpp.o"

# External object files for target xC-core
xC__core_EXTERNAL_OBJECTS =

lib/libxC-core.a: xc/core/CMakeFiles/xC-core.dir/core.cpp.o
lib/libxC-core.a: xc/core/CMakeFiles/xC-core.dir/build.make
lib/libxC-core.a: xc/core/CMakeFiles/xC-core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libxC-core.a"
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && $(CMAKE_COMMAND) -P CMakeFiles/xC-core.dir/cmake_clean_target.cmake
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xC-core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
xc/core/CMakeFiles/xC-core.dir/build: lib/libxC-core.a
.PHONY : xc/core/CMakeFiles/xC-core.dir/build

xc/core/CMakeFiles/xC-core.dir/requires: xc/core/CMakeFiles/xC-core.dir/core.cpp.o.requires
.PHONY : xc/core/CMakeFiles/xC-core.dir/requires

xc/core/CMakeFiles/xC-core.dir/clean:
	cd /home/lgl/master/SCARA/xCLib/src/xccore/xc/core && $(CMAKE_COMMAND) -P CMakeFiles/xC-core.dir/cmake_clean.cmake
.PHONY : xc/core/CMakeFiles/xC-core.dir/clean

xc/core/CMakeFiles/xC-core.dir/depend:
	cd /home/lgl/master/SCARA/xCLib/src/xccore && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lgl/master/SCARA/xCLib/src/xccore /home/lgl/master/SCARA/xCLib/src/xccore/xc/core /home/lgl/master/SCARA/xCLib/src/xccore /home/lgl/master/SCARA/xCLib/src/xccore/xc/core /home/lgl/master/SCARA/xCLib/src/xccore/xc/core/CMakeFiles/xC-core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xc/core/CMakeFiles/xC-core.dir/depend

