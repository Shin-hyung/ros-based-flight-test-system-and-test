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

# Utility rule file for server_io_pkg_generate_messages_py.

# Include any custom commands dependencies for this target.
include server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/compiler_depend.make

# Include the progress variables for this target.
include server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/progress.make

server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py
server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py
server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/__init__.py
server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/__init__.py

/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/__init__.py: /opt/ros/melodic/lib/genpy/genmsg_py.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/__init__.py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/__init__.py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Python msg __init__.py for server_io_pkg"
	cd /home/xavier/catkin_ws/build/server_io_pkg && ../catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py -o /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg --initpy

/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py: /opt/ros/melodic/lib/genpy/genmsg_py.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py: /home/xavier/catkin_ws/src/server_io_pkg/msg/data.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating Python from MSG server_io_pkg/data"
	cd /home/xavier/catkin_ws/build/server_io_pkg && ../catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/xavier/catkin_ws/src/server_io_pkg/msg/data.msg -Iserver_io_pkg:/home/xavier/catkin_ws/src/server_io_pkg/msg -Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg -p server_io_pkg -o /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg

/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/__init__.py: /opt/ros/melodic/lib/genpy/genmsg_py.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/__init__.py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/__init__.py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating Python srv __init__.py for server_io_pkg"
	cd /home/xavier/catkin_ws/build/server_io_pkg && ../catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py -o /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv --initpy

/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py: /opt/ros/melodic/lib/genpy/gensrv_py.py
/home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py: /home/xavier/catkin_ws/src/server_io_pkg/srv/diftorder.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/xavier/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating Python code from SRV server_io_pkg/diftorder"
	cd /home/xavier/catkin_ws/build/server_io_pkg && ../catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/genpy/cmake/../../../lib/genpy/gensrv_py.py /home/xavier/catkin_ws/src/server_io_pkg/srv/diftorder.srv -Iserver_io_pkg:/home/xavier/catkin_ws/src/server_io_pkg/msg -Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg -p server_io_pkg -o /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv

server_io_pkg_generate_messages_py: server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py
server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/__init__.py
server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/msg/_data.py
server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/__init__.py
server_io_pkg_generate_messages_py: /home/xavier/catkin_ws/devel/lib/python2.7/dist-packages/server_io_pkg/srv/_diftorder.py
server_io_pkg_generate_messages_py: server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/build.make
.PHONY : server_io_pkg_generate_messages_py

# Rule to build all files generated by this target.
server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/build: server_io_pkg_generate_messages_py
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/build

server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/clean:
	cd /home/xavier/catkin_ws/build/server_io_pkg && $(CMAKE_COMMAND) -P CMakeFiles/server_io_pkg_generate_messages_py.dir/cmake_clean.cmake
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/clean

server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/depend:
	cd /home/xavier/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xavier/catkin_ws/src /home/xavier/catkin_ws/src/server_io_pkg /home/xavier/catkin_ws/build /home/xavier/catkin_ws/build/server_io_pkg /home/xavier/catkin_ws/build/server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server_io_pkg/CMakeFiles/server_io_pkg_generate_messages_py.dir/depend
