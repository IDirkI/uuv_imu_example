#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

#include "uuv_imu_driver_cpp/bindings.h"

using namespace std::chrono_literals;

class IMUPublisher : public rclcpp::Node {
  private:
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;

    void timer_callback() {
      auto message = sensor_msgs::msg::Imu();
      message.linear_acceleration.x = 0.0f;
      message.linear_acceleration.y = 0.0f;
      message.linear_acceleration.z = 0.0f;

      message.angular_velocity.x = 0.0f;
      message.angular_velocity.y = 0.0f;
      message.angular_velocity.z = 0.0f;

      publisher_->publish(message);
      RCLCPP_INFO(this->get_logger(), "a = [ %3.2f, %3.2f, %3.2f ]  |  w = [ %3.2f, %3.2f, %3.2f ]\n", message.linear_acceleration.x, message.linear_acceleration.y, message.linear_acceleration.z,
        message.angular_velocity.x, message.angular_velocity.y, message.angular_velocity.z);
    }

  public:
    IMUPublisher() : Node("imu_publisher") {
      init();

      this->declare_parameter("publish_rate", 50.0);  // [ Hz ]
      this->declare_parameter("frame_id", "imu_link");

      double publish_rate = this->get_parameter("publish_rate").as_double();  // [ Hz ]
      std::chrono::milliseconds publish_period = std::chrono::milliseconds(static_cast<int>(1000.0 / publish_rate)); // [ ms ]
      
      publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("imu/data", 10);
      timer_ = this->create_wall_timer(publish_period, std::bind(&IMUPublisher::timer_callback, this));
      count_ = 0;
    }
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IMUPublisher>());
  rclcpp::shutdown();
  return 0;
}