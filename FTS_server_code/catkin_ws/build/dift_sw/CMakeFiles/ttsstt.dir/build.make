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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xavier/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xavier/catkin_ws/build

# Include any dependencies generated for this target.
include dift_sw/CMakeFiles/ttsstt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dift_sw/CMakeFiles/ttsstt.dir/compiler_depend.make

# Include the progress variables for this target.
include dift_sw/CMakeFiles/ttsstt.dir/progress.make

# Include the compile flags for this target's objects.
include dift_sw/CMakeFiles/ttsstt.dir/flags.make

dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o: dift_sw/CMakeFiles/ttsstt.dir/flags.make
dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o: /home/xavier/catkin_ws/src/dift_sw/src/ttsstt.cpp
dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o: dift_sw/CMakeFiles/ttsstt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o"
	cd /home/xavier/catkin_ws/build/dift_sw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o -MF CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o.d -o CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o -c /home/xavier/catkin_ws/src/dift_sw/src/ttsstt.cpp

dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ttsstt.dir/src/ttsstt.cpp.i"
	cd /home/xavier/catkin_ws/build/dift_sw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xavier/catkin_ws/src/dift_sw/src/ttsstt.cpp > CMakeFiles/ttsstt.dir/src/ttsstt.cpp.i

dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ttsstt.dir/src/ttsstt.cpp.s"
	cd /home/xavier/catkin_ws/build/dift_sw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xavier/catkin_ws/src/dift_sw/src/ttsstt.cpp -o CMakeFiles/ttsstt.dir/src/ttsstt.cpp.s

# Object files for target ttsstt
ttsstt_OBJECTS = \
"CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o"

# External object files for target ttsstt
ttsstt_EXTERNAL_OBJECTS =

/home/xavier/catkin_ws/devel/lib/dift_sw/ttsstt: dift_sw/CMakeFiles/ttsstt.dir/src/ttsstt.cpp.o
/home/xavier/catkin_ws/devel/lib/dift_sw/ttsstt: dift_sw/CMakeFiles/ttsstt.dir/build.make
/home/xavier/catkin_ws/devel/lib/dift_sw/ttsstt: dift_sw/CMakeFiles/ttsstt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/xavier/catkin_ws/devel/lib/dift_sw/ttsstt"
	cd /home/xavier/catkin_ws/build/dift_sw && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ttsstt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dift_sw/CMakeFiles/ttsstt.dir/build: /home/xavier/catkin_ws/devel/lib/dift_sw/ttsstt
.PHONY : dift_sw/CMakeFiles/ttsstt.dir/build

dift_sw/CMakeFiles/ttsstt.dir/clean:
	cd /home/xavier/catkin_ws/build/dift_sw && $(CMAKE_COMMAND) -P CMakeFiles/ttsstt.dir/cmake_clean.cmake
.PHONY : dift_sw/CMakeFiles/ttsstt.dir/clean

dift_sw/CMakeFiles/ttsstt.dir/depend:
	cd /home/xavier/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xavier/catkin_ws/src /home/xavier/catkin_ws/src/dift_sw /home/xavier/catkin_ws/build /home/xavier/catkin_ws/build/dift_sw /home/xavier/catkin_ws/build/dift_sw/CMakeFiles/ttsstt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dift_sw/CMakeFiles/ttsstt.dir/depend
