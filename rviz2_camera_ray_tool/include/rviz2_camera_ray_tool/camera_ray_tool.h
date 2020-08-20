#pragma once

#include <rviz_common/tool.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rviz2_camera_ray_tool_msgs/msg/ray.hpp>

namespace rviz2_camera_ray_tool
{

class CameraRayTool : public rviz_common::Tool, public rclcpp::Node
{
  Q_OBJECT
public:
  CameraRayTool();
  virtual ~CameraRayTool();

  virtual void onInitialize() override;

  virtual void activate() override;

  virtual void deactivate() override;

  virtual int processMouseEvent(rviz_common::ViewportMouseEvent& event) override;

private:
  rclcpp::Publisher<rviz2_camera_ray_tool_msgs::msg::Ray>::SharedPtr pub_;
};

}
