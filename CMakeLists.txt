cmake_minimum_required(VERSION 3.10)
project(simple_uart_reader)

add_compile_options(-std=c++17)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
)
find_package(serial REQUIRED)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES serial_tx_rx_pkg
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include(FetchContent)
FetchContent_Declare(
  scnlib
  GIT_REPOSITORY https://github.com/eliaskosunen/scnlib.git
  GIT_TAG        e937be1a52588621b406d58ce8614f96bb5de747 #Prepare v4.0.1
)
FetchContent_MakeAvailable(scnlib)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  /tmp/usr/local/include
)

add_executable(tx_rx_node src/serial_tx_rx_pkg_node.cpp)
add_dependencies(tx_rx_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(tx_rx_node
  ${catkin_LIBRARIES}
  ${serial_LIBRARIES}
)

add_executable(example_read_data src/example_read_data.cpp)
add_dependencies(example_read_data
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(example_read_data
  ${catkin_LIBRARIES}
  ${serial_LIBRARIES}
  scn::scn
)