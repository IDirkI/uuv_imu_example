import rclpy
from rclpy.node import Node
import bluerobotics_navigator as navigator

from sensor_msgs.msg import Imu
from math import atan, sqrt, pi

class IMUPublisher(Node):
    def __init__(self):
        super().__init__('imu_publisher')

        self.t = [0.0, 0.0, 0.0]

        self.declare_parameter("publish_rate", 0.2)
        self.declare_parameter("trust", 0.99)

        self.publisher_ = self.create_publisher(Imu, 'imu/data', 10)
        self.trust = self.get_parameter("trust").get_parameter_value().double_value
        self.timer_period = 1/self.get_parameter("publish_rate").get_parameter_value().double_value
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        navigator.init()
        acc = navigator.read_accel()
        self.t[0], self.t[1] = self.get_angles(acc.x, acc.y, acc.z)

    def timer_callback(self):
        message = Imu()
        acc = navigator.read_accel()
        gyro = navigator.read_gyro()

        message.linear_acceleration.x = acc.x
        message.linear_acceleration.y = acc.y
        message.linear_acceleration.z = acc.z

        message.angular_velocity.x = gyro.x
        message.angular_velocity.y = gyro.y
        message.angular_velocity.z = gyro.z

        dG = [gyro.x*self.timer_period, gyro.y*self.timer_period, gyro.z*self.timer_period]
        roll, pitch = self.get_angles(acc.x, acc.y, acc.z)
        self.t[0] = (1-self.trust)*roll + (self.trust)*(dG[0] + self.t[0])
        self.t[1] = (1-self.trust)*pitch + (self.trust)*(dG[1] + self.t[1])
        self.t[2] = (self.trust)*(dG[2] + self.t[2])
        
    
        self.publisher_.publish(message)
        #self.get_logger().info(f"a = [ {message.linear_acceleration.x}, {message.linear_acceleration.y}, {message.linear_acceleration.z} ]")
        #self.get_logger().info(f"w = [ {message.angular_velocity.x}, {message.angular_velocity.y}, {message.angular_velocity.z} ]")

        self.get_logger().info(f"t = [ {self.t[0] : .3f}, {self.t[1]: .3f}, 0.0]")

    def get_angles(self, a_x, a_y, a_z):
        if a_z != 0.0:
            roll = atan(a_y / a_z)
        else:
            roll = (pi/2)*(a_y/abs(a_y))
        pitch = atan(-a_x/sqrt(a_y**2 +  a_z**2))
        return roll, pitch

def main(args=None):
    rclpy.init(args=args)

    imu_publisher = IMUPublisher()

    rclpy.spin(imu_publisher)

    imu_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()