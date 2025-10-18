from setuptools import find_packages, setup

package_name = 'uuv_imu_driver_py'

setup(
    name=package_name,
    version='1.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', [
            'launch/imu_launch.py'
        ]),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Berk',
    maintainer_email='berkyilmaz2005@gmail.com',
    description='Demo: Flight Controller IMU driver example',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'imu_publisher = uuv_imu_driver_py.imu_driver:main',
        ],
    },
)
