# Robot Seguidor de Línea con Visión Artificial

## Autores

- Adrián Rildo Cussi Torrez
- Mariola Andrea Cussi Torrez

## Descripción

Este proyecto presenta el desarrollo de un robot seguidor de línea basado en ESP32, ESP32-CAM y ROS2 Jazzy. El sistema utiliza visión artificial para detectar la posición de la trayectoria y generar comandos de movimiento que permiten el seguimiento autónomo de una línea.

Además de la implementación física, se desarrolló una simulación en Gazebo para validar el comportamiento del sistema y verificar la comunicación entre los nodos ROS2.

## Tecnologías utilizadas

- ESP32
- ESP32-CAM
- ROS2 Jazzy
- Gazebo Sim
- Python
- Arduino IDE

## Componentes principales

- ESP32 para control del robot.
- ESP32-CAM para adquisición de imágenes.
- Sensores infrarrojos para detección de línea.
- Comunicación mediante ROS2.

## Nodos ROS2 principales

### vision_udp_node.py

Recibe la información proveniente de la ESP32-CAM y publica el estado detectado de la línea.

### motion_node.py

Procesa la información recibida y genera comandos de velocidad para el robot.

## Estructura del repositorio

```text
arduino/
docs/
src/
