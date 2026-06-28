# arduino-iot-control

IoT control system with Arduino and serial communication for the Computer Architecture course.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-completed-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)

[Portuguese](README.pt.md) | English

## About

IoT system for controlling LEDs and a buzzer via serial communication between Arduino and computer. Includes Arduino firmware (IoTController) with button reading and response to remote commands, and a C host program for sending commands and logging events (valid/invalid identity) with timestamps.

## Requirements

| Tool        | Minimum version |
| ----------- | --------------- |
| GCC         | 9+              |
| Make        | 4+              |
| Arduino IDE | 2+              |

## How to run

**Arduino:** open `IoTController/IoTController.ino` in Arduino IDE and upload to the board.

**Host (C):**

```bash
make DEVICE=/dev/ttyUSB0
```

The default `DEVICE` value is `/dev/ttyUSB0`. Adjust to your system's serial port.

## License

Distributed under the **MIT** license, © 2024 Nycolas Souza.

It is a permissive license: anyone can use, copy, modify, and distribute the code, including in commercial projects, as long as the copyright notice and license text are retained.

The full text is in [LICENSE](LICENSE).
