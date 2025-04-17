#include <ros/ros.h>
#include <livox_ros_driver/CustomMsg.h>
#include <livox_ros_driver2/CustomMsg.h>

ros::Publisher pub;

void livoxCallback(const livox_ros_driver::CustomMsg::ConstPtr& msg_in) {
  livox_ros_driver2::CustomMsg msg_out;

  msg_out.header = msg_in->header;
  msg_out.timebase = msg_in->timebase;
  msg_out.point_num = msg_in->point_num;
  msg_out.lidar_id = msg_in->lidar_id;

  msg_out.points.reserve(msg_in->points.size());
  for (const auto& pt_in : msg_in->points) {
    livox_ros_driver2::CustomPoint pt_out;
    pt_out.offset_time = pt_in.offset_time;
    pt_out.x = pt_in.x;
    pt_out.y = pt_in.y;
    pt_out.z = pt_in.z;
    pt_out.reflectivity = pt_in.reflectivity;
    pt_out.tag = pt_in.tag;
    pt_out.line = pt_in.line;
    msg_out.points.push_back(pt_out);
  }

  pub.publish(msg_out);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "livox_msg_converter");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/livox/lidar", 10, livoxCallback);
  pub = nh.advertise<livox_ros_driver2::CustomMsg>("/livox/lidar_converted", 10);

  ros::spin();
  return 0;
}
