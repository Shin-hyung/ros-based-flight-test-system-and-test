# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(FATAL_ERROR "Could not find messages which '/home/xavier/catkin_ws/src/test_ws/msg/Num.msg' depends on. Did you forget to specify generate_messages(DEPENDENCIES ...)?
Cannot locate message [strimg] in package [test_ws] with paths [['/home/xavier/catkin_ws/src/test_ws/msg']]")
message(STATUS "test_ws: 1 messages, 0 services")

set(MSG_I_FLAGS "-Itest_ws:/home/xavier/catkin_ws/src/test_ws/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(test_ws_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_cpp(test_ws
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_ws
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(test_ws_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(test_ws_generate_messages test_ws_generate_messages_cpp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(test_ws_gencpp)
add_dependencies(test_ws_gencpp test_ws_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_ws_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_eus(test_ws
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_ws
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(test_ws_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(test_ws_generate_messages test_ws_generate_messages_eus)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(test_ws_geneus)
add_dependencies(test_ws_geneus test_ws_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_ws_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_lisp(test_ws
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_ws
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(test_ws_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(test_ws_generate_messages test_ws_generate_messages_lisp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(test_ws_genlisp)
add_dependencies(test_ws_genlisp test_ws_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_ws_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_nodejs(test_ws
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_ws
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(test_ws_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(test_ws_generate_messages test_ws_generate_messages_nodejs)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(test_ws_gennodejs)
add_dependencies(test_ws_gennodejs test_ws_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_ws_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_py(test_ws
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_ws
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(test_ws_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(test_ws_generate_messages test_ws_generate_messages_py)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(test_ws_genpy)
add_dependencies(test_ws_genpy test_ws_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_ws_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_ws)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_ws
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(test_ws_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_ws)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_ws
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(test_ws_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_ws)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_ws
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(test_ws_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_ws)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_ws
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(test_ws_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_ws)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_ws\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_ws
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(test_ws_generate_messages_py std_msgs_generate_messages_py)
endif()
