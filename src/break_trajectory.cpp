#include "autoware_rclue_interface/break_trajectory.h"

BreakTrajectory::BreakTrajectory() : Node("break_trajectory_node") {
    pub_traj_ = this->create_publisher<nav_msgs::msg::Path>("/planning/scenario_planning/trajectory_path_broken", 10);
    sub_traj_ = this->create_subscription<autoware_auto_planning_msgs::msg::Trajectory>("/planning/scenario_planning/trajectory", 10, std::bind(&BreakTrajectory::traj_cb, this, _1));
    // timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
}

void BreakTrajectory::traj_cb(const autoware_auto_planning_msgs::msg::Trajectory &in_msg) {
    nav_msgs::msg::Path path;
    path.header = in_msg.header;
    for (const auto &point : in_msg.points) {
        geometry_msgs::msg::PoseStamped buf_pose;
        buf_pose.pose = point.pose;
        path.poses.emplace_back(buf_pose);
    }
    pub_traj_->publish(path);
}


int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BreakTrajectory>());
  rclcpp::shutdown();
  return 0;
}
