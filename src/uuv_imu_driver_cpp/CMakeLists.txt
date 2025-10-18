cmake_minimum_required(VERSION 3.8)
project(uuv_imu_driver_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ===== ROS2 PACKAGES =====
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# ===== FC NAVIGATOR LIBRARY =====
set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/navigator_lib/aarch64-unknown-linux-gnu/libbluerobotics_navigator.so")

# ===== BUILD =====
add_executable(imu_publisher src/imu_publisher.cpp)

ament_target_dependencies(imu_publisher rclcpp sensor_msgs)
target_link_libraries(imu_publisher ${LIBRARY_PATH})
target_include_directories(imu_publisher PRIVATE 
  include
)


set_target_properties(imu_publisher PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

# ===== INSTALL EXECUTABLES =====
install(TARGETS
  imu_publisher
  DESTINATION lib/${PROJECT_NAME})

# ===== INSTALL LAUNCH FILES =====
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
