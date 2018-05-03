#ifndef RVIZ_CAMERA_RAY_TOOL_H
#define RVIZ_CAMERA_RAY_TOOL_H

#include <rviz/tool.h>
#include <ros/publisher.h>
#include <ros/node_handle.h>

namespace rviz_camera_ray_tool
{

class CameraRayTool : public rviz::Tool
{
  Q_OBJECT
public:
  CameraRayTool();
  virtual ~CameraRayTool();

  virtual void onInitialize() override;

  virtual void activate() override;

  virtual void deactivate() override;

  virtual int processMouseEvent(rviz::ViewportMouseEvent& event) override;

private:
  ros::NodeHandle nh_;
  ros::Publisher pub_;
};

}

#endif
