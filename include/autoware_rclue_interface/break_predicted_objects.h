#pragma once
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "autoware_auto_perception_msgs/msg/predicted_objects.hpp"
#include "autoware_auto_perception_msgs/msg/predicted_object_ue.hpp"

using std::placeholders::_1;

class BreakPredictedObjects : public rclcpp::Node
{
public:
    BreakPredictedObjects();

private:
    void obj_cb(const autoware_auto_perception_msgs::msg::PredictedObjects &in_msg);
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<autoware_auto_perception_msgs::msg::PredictedObjectUE>::SharedPtr pub_obj_;
    rclcpp::Subscription<autoware_auto_perception_msgs::msg::PredictedObjects>::SharedPtr sub_obj_;
};

