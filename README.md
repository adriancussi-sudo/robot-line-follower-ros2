# Robot Seguidor de Línea con Visión Artificial

## Autores

- Adrián Rildo Cussi Torrez
- Mariola Andrea Cussi Torrez

## Descripción

Este proyecto presenta el desarrollo de un robot seguidor de línea basado en ESP32, ESP32-CAM y ROS2 Jazzy. El sistema utiliza visión artificial para detectar la posición de una línea y generar comandos de movimiento que permiten el seguimiento autónomo de trayectorias.

La arquitectura implementada combina procesamiento en la ESP32-CAM, comunicación mediante UDP y control a través de nodos ROS2. Además, se realizaron pruebas en simulación utilizando Gazebo Sim para validar el funcionamiento del sistema antes de su implementación física.

## Objetivo

Desarrollar un robot móvil capaz de seguir una línea de manera autónoma mediante visión artificial, integrando hardware de bajo costo con herramientas modernas de robótica como ROS2 y Gazebo.

## Hardware Utilizado

- ESP32
- ESP32-CAM
- Robot móvil diferencial
- Sensores infrarrojos
- Motores DC
- Driver de motores

## Software Utilizado

- Ubuntu 24.04
- ROS2 Jazzy
- Gazebo Sim
- Arduino IDE
- Python

## Estructura del Repositorio

```text
arduino/
├── avance.ino
└── vision_espnow_cam.ino

src/
└── line_follower_ros/
    ├── package.xml
    ├── setup.py
    ├── setup.cfg
    ├── resource/
    ├── test/
    └── line_follower_ros/
        ├── control_node.py
        ├── estado_node.py
        ├── motion_node.py
        ├── vision_node.py
        └── vision_udp_node.py

docs/
```

## Programación de las Placas

### ESP32-CAM

Cargar el archivo:

```text
arduino/vision_espnow_cam.ino
```

Funciones principales:

- Captura imágenes de la trayectoria.
- Detecta la posición relativa de la línea.
- Genera comandos de navegación.
- Envía información mediante UDP al sistema ROS2.

### ESP32 del Robot

Cargar el archivo:

```text
arduino/avance.ino
```

Funciones principales:

- Control de motores.
- Lectura de sensores infrarrojos.
- Ejecución de movimientos.
- Integración con la plataforma móvil.

## Compilación del Proyecto ROS2

```bash
cd ~/robot_final_ws

colcon build

source install/setup.bash
```

## Ejecución de Gazebo

```bash
source /opt/ros/jazzy/setup.bash

export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
```

## Ejecución de los Nodos ROS2

### Terminal 1 - Nodo de Visión

```bash
source /opt/ros/jazzy/setup.bash

cd ~/robot_final_ws

source install/setup.bash

ros2 run line_follower_ros vision_udp_node
```

### Terminal 2 - Nodo de Movimiento

```bash
source /opt/ros/jazzy/setup.bash

cd ~/robot_final_ws

source install/setup.bash

ros2 run line_follower_ros motion_node
```

## Flujo de Ejecución

1. Programar la ESP32 con el archivo `avance.ino`.
2. Programar la ESP32-CAM con el archivo `vision_espnow_cam.ino`.
3. Encender ambas placas.
4. Compilar el workspace ROS2.
5. Iniciar Gazebo Sim (opcional para pruebas de simulación).
6. Ejecutar el nodo `vision_udp_node`.
7. Ejecutar el nodo `motion_node`.
8. Verificar la recepción de mensajes y el movimiento del robot.

## Nodos Principales del Sistema

### vision_udp_node.py

Nodo encargado de recibir la información proveniente de la ESP32-CAM mediante comunicación UDP y publicarla dentro del ecosistema ROS2.

### motion_node.py

Nodo encargado de procesar la información recibida y generar comandos de velocidad para el movimiento del robot o de la simulación en Gazebo.

## Resultados

Se logró implementar un sistema funcional de seguimiento de línea mediante visión artificial utilizando una ESP32-CAM y ROS2. Las pruebas realizadas demostraron la correcta transmisión de información entre la cámara y los nodos ROS2, así como la generación de comandos de movimiento para el robot móvil.

Asimismo, se validó el comportamiento del sistema en Gazebo Sim mediante la simulación de un TurtleBot3, permitiendo verificar la integración entre percepción y control antes de la implementación física.

## Trabajo Futuro

Como trabajo futuro se plantea mejorar el algoritmo de visión artificial para aumentar la precisión del seguimiento de trayectorias y permitir la detección de obstáculos.

Además, se propone adaptar esta plataforma para aplicaciones de transporte autónomo de medicamentos e insumos médicos en hospitales, aprovechando rutas predefinidas y sistemas de navegación basados en visión artificial.

## Repositorio

https://github.com/adriancussi-sudo/robot-line-follower-ros2
