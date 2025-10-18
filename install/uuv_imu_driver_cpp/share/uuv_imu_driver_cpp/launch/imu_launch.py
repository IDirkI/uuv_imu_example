from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='uuv_imu_driver_cpp',   # package of the execuatble
            namespace='utux/sensor',        # namespace it will be put under
            executable='imu_publisher',     # exe name (as defined in your CMakeLists.txt)
            name='imu_publisher',           # runtime name of the node
            parameters=[{                   # define constants for use inside node
                
                'publish_rate': 2.0,   # --> [ Hz ]
                'frame_id': 'imu_link'  
            }]
        )
    ])