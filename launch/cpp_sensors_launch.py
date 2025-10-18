import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    imu_driver = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('uuv_imu_driver_cpp'), 'launch'),
         '/imu_launch.py'])
    )
   
    return LaunchDescription([
      imu_driver,
    ])