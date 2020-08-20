#include <rviz2_camera_ray_tool/camera_ray_tool.h>

#include <OgreCamera.h>
#include <OgreRay.h>
#include <OgreVector3.h>
#include <OgreViewport.h>

//#pragma GCC diagnostic push   // Supress warnings from library files
//#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
//#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <rviz_common/viewport_mouse_event.hpp>
#include <rviz_common/display_context.hpp>
#include <rviz_common/interaction/selection_manager.hpp>
#include <rviz_common/view_controller.hpp>
#include <rviz_common/render_panel.hpp>
#include <rviz_rendering/render_window.hpp>

#pragma GCC diagnostic pop // Un-supress warnings

#include <Eigen/Dense>

#include <rviz2_camera_ray_tool_msgs/msg/ray.hpp>

namespace rviz2_camera_ray_tool
{
CameraRayTool::CameraRayTool()
  : Node("rviz2_camera_ray_tool")
  , pub_(this->create_publisher<rviz2_camera_ray_tool_msgs::msg::Ray>("/clicked_ray", 1))
{
  shortcut_key_ = 'r';
}

CameraRayTool::~CameraRayTool()
{
}

void CameraRayTool::onInitialize()
{
}

void CameraRayTool::activate()
{
}

void CameraRayTool::deactivate()
{
}

int CameraRayTool::processMouseEvent(rviz_common::ViewportMouseEvent& event)
{
  if (event.leftUp())
  {

    auto viewport = rviz_rendering::RenderWindowOgreAdapter::getOgreViewport(event.panel->getRenderWindow());
    Ogre::Ray mouse_ray = viewport->getCamera()->getCameraToViewportRay(
      static_cast<float>(event.x) / static_cast<float>(viewport->getActualWidth()),
      static_cast<float>(event.y) / static_cast<float>(viewport->getActualHeight()));

    rviz2_camera_ray_tool_msgs::msg::Ray msg;
    msg.header.stamp = this->now();
    msg.header.frame_id = context_->getFixedFrame().toStdString();

    msg.origin.x = static_cast<double>( mouse_ray.getOrigin().x);
    msg.origin.y = static_cast<double>( mouse_ray.getOrigin().y);
    msg.origin.z = static_cast<double>( mouse_ray.getOrigin().z);
    msg.direction.x = static_cast<double>( mouse_ray.getDirection().x);
    msg.direction.y = static_cast<double>( mouse_ray.getDirection().y);
    msg.direction.z = static_cast<double>( mouse_ray.getDirection().z);

    pub_->publish(msg);

    if (event.shift()) // Hold down shift to pick many points
      return Render;
    else
      return Finished;
  }

  return Render;
}
}

#include <pluginlib/class_list_macros.hpp>  // NOLINT
PLUGINLIB_EXPORT_CLASS(rviz2_camera_ray_tool::CameraRayTool, rviz_common::Tool)
