# WebWheels – Wi-Fi Controlled RC Car Using ESP8266

## Overview

WebWheels is a Wi-Fi controlled robotic car built using the ESP8266 NodeMCU microcontroller. The project allows users to control the movement of the car through a web-based interface hosted directly on the ESP8266.

Unlike traditional Bluetooth-controlled cars, WebWheels uses a local Wi-Fi network and WebSocket communication to provide fast, responsive, and low-latency control. The system can be operated from any smartphone, tablet, or computer connected to the same network without requiring any additional mobile application.

---

## Features

* Real-time wireless control using Wi-Fi
* Low-latency communication through WebSockets
* Responsive web-based control interface
* Forward, backward, left, right, and stop movement controls
* Automatic stop functionality when control buttons are released
* No mobile application required
* Cross-platform compatibility (Android, iOS, Windows, macOS)
* Simple and cost-effective hardware implementation

---

## Hardware Components

| Component          | Quantity    |
| ------------------ | ----------- |
| ESP8266 NodeMCU    | 1           |
| L298N Motor Driver | 1           |
| DC Gear Motors     | 2           |
| Robot Chassis      | 1           |
| Wheels             | 2           |
| Caster Wheel       | 1           |
| Battery Pack       | 1           |
| Jumper Wires       | As Required |

---

## Working Principle

The ESP8266 connects to a Wi-Fi network and hosts a web server that serves a control dashboard. When a user presses a control button on the webpage, a command is sent to the ESP8266 through a WebSocket connection.

The received command is processed instantly, and the corresponding motor control signals are sent to the motor driver. This enables smooth and responsive vehicle movement with minimal communication delay.

To improve responsiveness, Wi-Fi sleep mode is disabled, ensuring a stable and continuous connection between the controller and the robot.

---

## Motor Control Mapping

| Command | Action        |
| ------- | ------------- |
| F       | Move Forward  |
| B       | Move Backward |
| L       | Turn Left     |
| R       | Turn Right    |
| S       | Stop          |

---

## Pin Configuration

### Left Motor

| ESP8266 Pin | Function |
| ----------- | -------- |
| D5 (GPIO14) | IN1      |
| D6 (GPIO12) | IN2      |

### Right Motor

| ESP8266 Pin | Function |
| ----------- | -------- |
| D7 (GPIO13) | IN3      |
| D8 (GPIO15) | IN4      |

---

## Software Requirements

* Arduino IDE
* ESP8266 Board Package
* ESP8266WiFi Library
* ESP8266WebServer Library
* WebSocketsServer Library

---

## Installation

1. Clone this repository.

```bash
git clone https://github.com/yourusername/WebWheels.git
```

2. Open the project in Arduino IDE.

3. Install the required ESP8266 libraries.

4. Update the Wi-Fi credentials in the source code.

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

5. Select the correct ESP8266 board and COM port.

6. Upload the code to the NodeMCU.

7. Open the Serial Monitor and note the IP address assigned to the ESP8266.

8. Enter the IP address in a web browser connected to the same Wi-Fi network.

9. Use the control interface to drive the robot.

---

## Applications

* Educational robotics projects
* Wireless robotic vehicle control
* IoT learning and experimentation
* Remote-controlled prototypes
* Robotics workshops and demonstrations

---

## Future Improvements

* Speed control using PWM
* Live battery monitoring
* Camera integration for FPV driving
* Obstacle detection and avoidance
* Mobile-friendly joystick interface
* Autonomous navigation modes

---

## Author

Developed as part of a robotics and embedded systems project focused on real-time wireless vehicle control using ESP8266 and WebSocket communication.

---

## License

This project is released under the MIT License. Feel free to use, modify, and distribute it for educational and personal projects.
