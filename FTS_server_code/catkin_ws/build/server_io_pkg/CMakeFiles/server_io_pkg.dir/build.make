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
include server_io_pkg/CMakeFiles/server_io_pkg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server_io_pkg/CMakeFiles/server_io_pkg.dir/compiler_depend.make

# Include the progress variables for this target.
include server_io_pkg/CMakeFiles/server_io_pkg.dir/progress.make

# Include the compile flags for this target's objects.
include server_io_pkg/CMakeFiles/server_io_pkg.dir/flags.make

server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o: server_io_pkg/CMakeFiles/server_io_pkg.dir/flags.make
server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o: /home/xavier/catkin_ws/src/server_io_pkg/src/api/vl53l1_linux_platform.c
server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o: server_io_pkg/CMakeFiles/server_io_pkg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o -MF CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o.d -o CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o -c /home/xavier/catkin_ws/src/server_io_pkg/src/api/vl53l1_linux_platform.c

server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.i"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xavier/catkin_ws/src/server_io_pkg/src/api/vl53l1_linux_platform.c > CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.i

server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.s"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xavier/catkin_ws/src/server_io_pkg/src/api/vl53l1_linux_platform.c -o CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.s

# Object files for target server_io_pkg
server_io_pkg_OBJECTS = \
"CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o"

# External object files for target server_io_pkg
server_io_pkg_EXTERNAL_OBJECTS =

/home/xavier/catkin_ws/devel/lib/libserver_io_pkg.so: server_io_pkg/CMakeFiles/server_io_pkg.dir/src/api/vl53l1_linux_platform.c.o
/home/xavier/catkin_ws/devel/lib/libserver_io_pkg.so: server_io_pkg/CMakeFiles/server_io_pkg.dir/build.make
/home/xavier/catkin_ws/devel/lib/libserver_io_pkg.so: server_io_pkg/CMakeFiles/server_io_pkg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library /home/xavier/catkin_ws/devel/lib/libserver_io_pkg.so"
	cd /home/xavier/catkin_ws/build/server_io_pkg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_io_pkg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server_io_pkg/CMakeFiles/server_io_pkg.dir/build: /home/xavier/catkin_ws/devel/lib/libserver_io_pkg.so
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg.dir/build

server_io_pkg/CMakeFiles/server_io_pkg.dir/clean:
	cd /home/xavier/catkin_ws/build/server_io_pkg && $(CMAKE_COMMAND) -P CMakeFiles/server_io_pkg.dir/cmake_clean.cmake
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg.dir/clean

server_io_pkg/CMakeFiles/server_io_pkg.dir/depend:
	cd /home/xavier/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xavier/catkin_ws/src /home/xavier/catkin_ws/src/server_io_pkg /home/xavier/catkin_ws/build /home/xavier/catkin_ws/build/server_io_pkg /home/xavier/catkin_ws/build/server_io_pkg/CMakeFiles/server_io_pkg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg.dir/depend
