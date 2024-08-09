#pragma once
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "autoware_auto_planning_msgs/msg/trajectory.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/path.hpp"

using std::placeholders::_1;

class BreakTrajectory : public rclcpp::Node
{
public:
    BreakTrajectory();

private:
    void traj_cb(const autoware_auto_planning_msgs::msg::Trajectory &in_msg);
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_traj_;
    rclcpp::Subscription<autoware_auto_planning_msgs::msg::Trajectory>::SharedPtr sub_traj_;
};

