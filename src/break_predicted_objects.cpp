#include "autoware_rclue_interface/break_predicted_objects.h"

BreakPredictedObjects::BreakPredictedObjects() : Node("break_predicted_objects_node") {
    pub_obj_ = this->create_publisher<autoware_auto_perception_msgs::msg::PredictedObjectUE>("/perception/object_recognition/objects_broken", 10);
    sub_obj_ = this->create_subscription<autoware_auto_perception_msgs::msg::PredictedObjects>("/perception/object_recognition/objects", 10, std::bind(&BreakPredictedObjects::obj_cb, this, _1));
    // timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
}

void BreakPredictedObjects::obj_cb(const autoware_auto_perception_msgs::msg::PredictedObjects &in_msg) {
    for (const auto &obj : in_msg.objects) {
        autoware_auto_perception_msgs::msg::PredictedObjectUE out_msg;
        out_msg.object_id = obj.object_id;
        out_msg.existence_probability = obj.existence_probability;
        out_msg.pose = obj.kinematics.initial_pose_with_covariance.pose;
        out_msg.dimension = obj.shape.dimensions;
        for (const auto& classification : obj.classification) {
            out_msg.classifications.emplace_back(classification.label);
            out_msg.classification_confidences.emplace_back(classification.probability);
        }

        for (const auto& path : obj.kinematics.predicted_paths) {
            out_msg.pathes.insert(out_msg.pathes.end(), path.path.begin(), path.path.end());
            geometry_msgs::msg::Pose separator;
            out_msg.pathes.emplace_back(separator);
            out_msg.path_confidences.emplace_back(path.confidence);
        }

        pub_obj_->publish(out_msg);
    }
}


int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BreakPredictedObjects>());
  rclcpp::shutdown();
  return 0;
}
