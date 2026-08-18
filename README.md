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

```
├── Images/
    └── system-architecture.png
```
---
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
---
## Technologies

| Technology | Purpose |
|---|---|
| ESP32 | Sensor data collection and device control |
| C/C++ | ESP32 programming |
| MQTT | IoT communication protocol |
| MQTT Broker | Message exchange between devices and Node-RED |
| Node-RED | Data processing, automation, and dashboard |
| Pushsafer | Mobile push notifications |

---
## Project Structure
```text
ESP32-IoT-Monitoring-Control/
│
├── ESP32/
│   └── esp32_mqtt.ino
│
├── NodeRED/
│   └── flows.json
│
├── Images/
│   ├── dashboard1.png
│   ├── dashboard2.png
│   └── system-architecture.png
│
└── README.md
```
---
## How to Run

### ESP32
1. Open the ```.ino``` file using Arduino IDE or another compatible development environment.
2. Configure the Wi-Fi credentials.
3. Configure the MQTT broker and topics.
4. Connect the required sensors and devices.
5. Upload the program to the ESP32.

### Node-RED
1. Install and start Node-RED.
2. Import ```NodeRED/flows.json.```
3. Configure the MQTT broker.
4. Configure the required dashboard nodes.
5. Configure Pushsafer credentials locally.
6. Deploy the flow.
7. Open the Node-RED dashboard.

### Security
Do not upload the following information to a public repository:
- Wi-Fi passwords
- MQTT credentials
- Pushsafer private keys
- API keys
- Other sensitive credentials

Use placeholder values in the source code or Node-RED configuration instead.




  
  
