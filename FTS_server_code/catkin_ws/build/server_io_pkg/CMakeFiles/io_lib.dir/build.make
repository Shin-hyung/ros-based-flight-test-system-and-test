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
include server_io_pkg/CMakeFiles/io_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server_io_pkg/CMakeFiles/io_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include server_io_pkg/CMakeFiles/io_lib.dir/progress.make

# Include the compile flags for this target's objects.
include server_io_pkg/CMakeFiles/io_lib.dir/flags.make

server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/flags.make
server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o: /home/xavier/catkin_ws/src/server_io_pkg/src/vl53l1_linux_platform.cpp
server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o -MF CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o.d -o CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o -c /home/xavier/catkin_ws/src/server_io_pkg/src/vl53l1_linux_platform.cpp

server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.i"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xavier/catkin_ws/src/server_io_pkg/src/vl53l1_linux_platform.cpp > CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.i

server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.s"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xavier/catkin_ws/src/server_io_pkg/src/vl53l1_linux_platform.cpp -o CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.s

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/flags.make
server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o: /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_api.cpp
server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o -MF CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o.d -o CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o -c /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_api.cpp

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.i"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_api.cpp > CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.i

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.s"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_api.cpp -o CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.s

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/flags.make
server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o: /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_calibration.cpp
server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o: server_io_pkg/CMakeFiles/io_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o -MF CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o.d -o CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o -c /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_calibration.cpp

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.i"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_calibration.cpp > CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.i

server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.s"
	cd /home/xavier/catkin_ws/build/server_io_pkg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xavier/catkin_ws/src/server_io_pkg/src/VL53L1X_calibration.cpp -o CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.s

# Object files for target io_lib
io_lib_OBJECTS = \
"CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o" \
"CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o" \
"CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o"

# External object files for target io_lib
io_lib_EXTERNAL_OBJECTS =

/home/xavier/catkin_ws/devel/lib/libio_lib.so: server_io_pkg/CMakeFiles/io_lib.dir/src/vl53l1_linux_platform.cpp.o
/home/xavier/catkin_ws/devel/lib/libio_lib.so: server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_api.cpp.o
/home/xavier/catkin_ws/devel/lib/libio_lib.so: server_io_pkg/CMakeFiles/io_lib.dir/src/VL53L1X_calibration.cpp.o
/home/xavier/catkin_ws/devel/lib/libio_lib.so: server_io_pkg/CMakeFiles/io_lib.dir/build.make
/home/xavier/catkin_ws/devel/lib/libio_lib.so: server_io_pkg/CMakeFiles/io_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /home/xavier/catkin_ws/devel/lib/libio_lib.so"
	cd /home/xavier/catkin_ws/build/server_io_pkg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/io_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server_io_pkg/CMakeFiles/io_lib.dir/build: /home/xavier/catkin_ws/devel/lib/libio_lib.so
.PHONY : server_io_pkg/CMakeFiles/io_lib.dir/build

server_io_pkg/CMakeFiles/io_lib.dir/clean:
	cd /home/xavier/catkin_ws/build/server_io_pkg && $(CMAKE_COMMAND) -P CMakeFiles/io_lib.dir/cmake_clean.cmake
.PHONY : server_io_pkg/CMakeFiles/io_lib.dir/clean

server_io_pkg/CMakeFiles/io_lib.dir/depend:
	cd /home/xavier/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xavier/catkin_ws/src /home/xavier/catkin_ws/src/server_io_pkg /home/xavier/catkin_ws/build /home/xavier/catkin_ws/build/server_io_pkg /home/xavier/catkin_ws/build/server_io_pkg/CMakeFiles/io_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server_io_pkg/CMakeFiles/io_lib.dir/depend
