cmake_minimum_required(VERSION 3.0)
project(convert_livox_msg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  livox_ros_driver
  livox_ros_driver2
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(convert_livox_msg_node convert_livox_msg_node.cpp)
target_link_libraries(convert_livox_msg_node ${catkin_LIBRARIES})
