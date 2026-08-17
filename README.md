# ESP32 IoT Monitoring & Control System

An IoT monitoring and control system built with ESP32, MQTT, Node-RED, and Pushsafer.
The system collects environmental data, detects rain conditions, provides a real-time web dashboard, controls devices remotely, and sends mobile notifications when specific conditions are detected.

## Overview

This project demonstrates an end-to-end IoT system in which sensor data is collected by an ESP32 and transmitted through MQTT to Node-RED for processing and visualization.

Node-RED acts as the central processing layer, providing:
- Real-time temperature and humidity monitoring
- Rain detection
- Web-based monitoring dashboard
- Remote device control
- Mobile notifications through Pushsafer

## System Architecture

```text
├── Images/
    └── system-architecture.png
```

## Feature

### Environmental Monitoring

The ESP32 collects environmental data such as:
- Temperature
- Humidity
- Rain status
The collected data is transmitted to Node-RED through MQTT.

### Real-Time Dashboard

Node-RED provides a web dashboard for monitoring the system.
The dashboard can display:
- Temperature
- Humidity
- Rain status
- Sensor data charts
- Device status
- Control interfaces

### Remote Device Control

The system allows devices connected to the ESP32 to be controlled remotely through the Node-RED dashboard.

### Mobile Notifications
**Pushsafer** is integrated into the Node-RED flow to send notifications to a mobile device when predefined conditions occur.
Examples include:
- High/Low temperature detection
- Rain detection







  
  
