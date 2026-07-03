# Robot Seguidor de Línea con Visión Artificial

## Autores

- Adrián Rildo Cussi Torrez
- Mariola Andrea Cussi Torrez

## Descripción

Sistema de seguimiento de línea basado en ESP32, ESP32-CAM, ROS2 Jazzy y Gazebo Sim.

El sistema utiliza una ESP32-CAM para detectar la posición de la línea y transmitir comandos mediante UDP. ROS2 procesa la información y genera comandos de movimiento para el robot.

## Requisitos

### Hardware

- ESP32
- ESP32-CAM
- Robot móvil
- Sensores infrarrojos

### Software

- Ubuntu 24.04
- ROS2 Jazzy
- Gazebo Sim
- Arduino IDE

## Estructura del repositorio

```text
arduino/
├── avance.ino
└── vision_espnow_cam.ino

src/
└── line_follower_ros/

docs/
```

## Compilación del paquete ROS2

```bash
cd ~/robot_final_ws

colcon build

source install/setup.bash
```

## Ejecución de Gazebo

```bash
source /opt/ros/jazzy/setup.bash

export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_gazebo empty_world.launch.py
```

## Ejecución de los nodos

### Nodo de visión

```bash
source /opt/ros/jazzy/setup.bash

cd ~/robot_final_ws

source install/setup.bash

ros2 run line_follower_ros vision_udp_node
```

### Nodo de movimiento

```bash
source /opt/ros/jazzy/setup.bash

cd ~/robot_final_ws

source install/setup.bash

ros2 run line_follower_ros motion_node
```

## Nodos principales

### vision_udp_node.py

Recibe información proveniente de la ESP32-CAM y publica el estado detectado de la línea.

### motion_node.py

Procesa la información recibida y genera comandos de velocidad para el robot.

## Resultados

El sistema fue validado tanto en una plataforma física como en un entorno de simulación Gazebo, logrando el seguimiento autónomo de trayectorias mediante visión artificial.

## Repositorio

https://github.com/adriancussi-sudo/robot-line-follower-ros2
