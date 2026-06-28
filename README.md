# arduino-iot-control

Sistema de controlo IoT com Arduino e comunicação serial para a disciplina de Arquitetura de Computadores.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-concluído-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)

## Sobre

Sistema IoT para controlo de LEDs e buzzer via comunicação serial entre Arduino e computador. Inclui firmware Arduino (IoTController) com leitura de botões e resposta a comandos remotos, e programa host em C para envio de comandos e registro de eventos (identidade válida/inválida) com marcação temporal.

## Como executar

**Arduino:** abrir o ficheiro `IoTController/IoTController.ino` no Arduino IDE e fazer upload.

**Host (C):** compilar com `make` e executar com o path do dispositivo serial como argumento (ex: `/dev/ttyUSB0`).

## Licença

Distribuído sob a licença **MIT**, © 2024 Nycolas Souza.

É uma licença permissiva: qualquer pessoa pode usar, copiar, modificar e distribuir o código, inclusive em projetos comerciais, desde que mantenha o aviso de copyright e o texto da licença.

O texto completo está em [LICENSE](LICENSE).
