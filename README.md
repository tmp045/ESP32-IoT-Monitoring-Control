#ESP32 IoT Monitoring & Control System

An IoT monitoring and control system built with ESP32, MQTT, Node-RED, and Pushsafer.
The system collects environmental data, detects rain conditions, provides a real-time web dashboard, controls devices remotely, and sends mobile notifications when specific conditions are detected.

##Overview

This project demonstrates an end-to-end IoT system in which sensor data is collected by an ESP32 and transmitted through MQTT to Node-RED for processing and visualization.

Node-RED acts as the central processing layer, providing:
- Real-time temperature and humidity monitoring
- Rain detection
- Web-based monitoring dashboard
- Remote device control
- Mobile notifications through Pushsafer

##System Architecture

```text
├── Images/
    └── system-architecture.png

  
  
