#include "rviz_camera_ray_tool/camera_ray_tool.h"
#include <pluginlib/class_list_macros.h>

#pragma GCC diagnostic push   // Supress warnings from library files
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <rviz/viewport_mouse_event.h>
#include <rviz/display_context.h>
#include <rviz/selection/selection_manager.h>
#include <rviz/view_controller.h>

#include <OGRE/OgreViewport.h>
#include <OGRE/OgreCamera.h>
#pragma GCC diagnostic pop // Un-supress warnings

#include <Eigen/Dense>

#include <rviz_camera_ray_tool/Ray.h>


rviz_camera_ray_tool::CameraRayTool::CameraRayTool()
{
  pub_ = nh_.advertise<Ray>("/clicked_ray", 1);
}

rviz_camera_ray_tool::CameraRayTool::~CameraRayTool()
{
}

void rviz_camera_ray_tool::CameraRayTool::onInitialize()
{
}

void rviz_camera_ray_tool::CameraRayTool::activate()
{
}

void rviz_camera_ray_tool::CameraRayTool::deactivate()
{
}

int rviz_camera_ray_tool::CameraRayTool::processMouseEvent(rviz::ViewportMouseEvent& event)
{
  if (event.leftUp())
  {
    const auto width = event.viewport->getActualWidth();
    const auto height = event.viewport->getActualHeight();
    const auto cam_pos = event.viewport->getCamera()->getPosition();
    const auto ray = event.viewport->getCamera()->getCameraToViewportRay(event.x / float(width),
                                                                         event.y / float(height));

    rviz_camera_ray_tool::Ray msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = context_->getFixedFrame().toStdString();

    msg.origin.x = cam_pos.x;
    msg.origin.y = cam_pos.y;
    msg.origin.z = cam_pos.z;
    msg.direction.x = ray.getDirection().x;
    msg.direction.y = ray.getDirection().y;
    msg.direction.z = ray.getDirection().z;

    pub_.publish(msg);

    return Finished;
  }

  return Render;
}

PLUGINLIB_EXPORT_CLASS(rviz_camera_ray_tool::CameraRayTool, rviz::Tool)
