cmake_minimum_required(VERSION 3.5.0)
project(rviz2_camera_ray_tool)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)

find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)


find_package(rviz2_camera_ray_tool_msgs REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)


qt5_wrap_cpp(MOC_FILES include/${PROJECT_NAME}/camera_ray_tool.h)

add_library(${PROJECT_NAME} SHARED
 src/${PROJECT_NAME}/camera_ray_tool.cpp
 ${MOC_FILES}
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rviz_common
  rviz_rendering
  rviz2_camera_ray_tool_msgs
)

target_link_libraries(${PROJECT_NAME}
  rviz_common::rviz_common
)

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
target_include_directories(${PROJECT_NAME} PUBLIC
    ${rviz2_camera_ray_tool_msgs_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
)
target_compile_definitions(${PROJECT_NAME} PRIVATE "RVIZ_DEFAULT_PLUGINS_BUILDING_LIBRARY")
target_compile_definitions(${PROJECT_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

## Mark cpp header files for installation
install(DIRECTORY include/
  DESTINATION include/
  )

ament_export_include_directories(include)
ament_export_interfaces(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  Qt5
  rviz_common
  geometry_msgs
  map_msgs
  rclcpp
)

ament_package()
