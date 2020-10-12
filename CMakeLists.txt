cmake_minimum_required(VERSION 3.5.0)
project(action_exception_test VERSION 0.0.0 LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)

add_executable(${PROJECT_NAME}_server_node
  src/server_node.cpp)
target_include_directories(${PROJECT_NAME}_server_node PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
  ${example_interfaces_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_server_node
  ${example_interfaces_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${rclcpp_action_LIBRARIES})

add_executable(${PROJECT_NAME}_client_node_multithread_reentrant
  src/client_node_multithread_reentrant.cpp)
target_include_directories(${PROJECT_NAME}_client_node_multithread_reentrant PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
  ${example_interfaces_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_client_node_multithread_reentrant
  ${example_interfaces_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${rclcpp_action_LIBRARIES})

add_executable(${PROJECT_NAME}_client_node_multithread_mutually_exclusive
  src/client_node_multithread_mutually_exclusive.cpp)
target_include_directories(${PROJECT_NAME}_client_node_multithread_mutually_exclusive PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
  ${example_interfaces_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_client_node_multithread_mutually_exclusive
  ${example_interfaces_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${rclcpp_action_LIBRARIES})

install(TARGETS
  ${PROJECT_NAME}_client_node_multithread_reentrant
  ${PROJECT_NAME}_client_node_multithread_mutually_exclusive
  ${PROJECT_NAME}_server_node
        RUNTIME DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
        DESTINATION share/${PROJECT_NAME})

ament_package()
