# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "cp2: 1 messages, 1 services")

set(MSG_I_FLAGS "-Icp2:/home/team6/catkin_ws/src/cp2/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(cp2_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_custom_target(_cp2_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "cp2" "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" ""
)

get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_custom_target(_cp2_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "cp2" "/home/team6/catkin_ws/src/cp2/msg/Num.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(cp2
  "/home/team6/catkin_ws/src/cp2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cp2
)

### Generating Services
_generate_srv_cpp(cp2
  "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cp2
)

### Generating Module File
_generate_module_cpp(cp2
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cp2
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(cp2_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(cp2_generate_messages cp2_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(cp2_generate_messages_cpp _cp2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_dependencies(cp2_generate_messages_cpp _cp2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cp2_gencpp)
add_dependencies(cp2_gencpp cp2_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cp2_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(cp2
  "/home/team6/catkin_ws/src/cp2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cp2
)

### Generating Services
_generate_srv_eus(cp2
  "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cp2
)

### Generating Module File
_generate_module_eus(cp2
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cp2
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(cp2_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(cp2_generate_messages cp2_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(cp2_generate_messages_eus _cp2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_dependencies(cp2_generate_messages_eus _cp2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cp2_geneus)
add_dependencies(cp2_geneus cp2_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cp2_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(cp2
  "/home/team6/catkin_ws/src/cp2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cp2
)

### Generating Services
_generate_srv_lisp(cp2
  "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cp2
)

### Generating Module File
_generate_module_lisp(cp2
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cp2
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(cp2_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(cp2_generate_messages cp2_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(cp2_generate_messages_lisp _cp2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_dependencies(cp2_generate_messages_lisp _cp2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cp2_genlisp)
add_dependencies(cp2_genlisp cp2_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cp2_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(cp2
  "/home/team6/catkin_ws/src/cp2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cp2
)

### Generating Services
_generate_srv_nodejs(cp2
  "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cp2
)

### Generating Module File
_generate_module_nodejs(cp2
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cp2
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(cp2_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(cp2_generate_messages cp2_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(cp2_generate_messages_nodejs _cp2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_dependencies(cp2_generate_messages_nodejs _cp2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cp2_gennodejs)
add_dependencies(cp2_gennodejs cp2_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cp2_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(cp2
  "/home/team6/catkin_ws/src/cp2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2
)

### Generating Services
_generate_srv_py(cp2
  "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2
)

### Generating Module File
_generate_module_py(cp2
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(cp2_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(cp2_generate_messages cp2_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(cp2_generate_messages_py _cp2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/team6/catkin_ws/src/cp2/msg/Num.msg" NAME_WE)
add_dependencies(cp2_generate_messages_py _cp2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cp2_genpy)
add_dependencies(cp2_genpy cp2_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cp2_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cp2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cp2
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(cp2_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cp2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cp2
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(cp2_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cp2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cp2
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(cp2_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cp2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cp2
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(cp2_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cp2
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(cp2_generate_messages_py std_msgs_generate_messages_py)
endif()
