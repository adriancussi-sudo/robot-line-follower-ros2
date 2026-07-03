from setuptools import find_packages, setup

package_name = 'line_follower_ros'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='mariola',
    maintainer_email='adrian.cussi@ucb.edu.bo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'vision_node = line_follower_ros.vision_node:main',
            'control_node = line_follower_ros.control_node:main',
            'motion_node = line_follower_ros.motion_node:main',
            'estado_node = line_follower_ros.estado_node:main',
            'vision_udp_node = line_follower_ros.vision_udp_node:main',
        ],
    },
)
