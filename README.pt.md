# arduino-iot-control

Sistema de controlo IoT com Arduino e comunicação serial para a disciplina de Arquitetura de Computadores.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-concluído-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)

[English](README.md) | Portuguese

## Sobre

Sistema IoT para controlo de LEDs e buzzer via comunicação serial entre Arduino e computador. Inclui firmware Arduino (IoTController) com leitura de botões e resposta a comandos remotos, e programa host em C para envio de comandos e registro de eventos (identidade válida/inválida) com marcação temporal.

## Requisitos

| Ferramenta  | Versão mínima |
| ----------- | ------------- |
| GCC         | 9+            |
| Make        | 4+            |
| Arduino IDE | 2+            |

## Como executar

**Arduino:** abrir `IoTController/IoTController.ino` no Arduino IDE e fazer upload para a placa.

**Host (C):**

```bash
make DEVICE=/dev/ttyUSB0
```

O valor padrão de `DEVICE` é `/dev/ttyUSB0`. Ajuste conforme a porta serial do sistema.

## Licença

Distribuído sob a licença **MIT**, © 2024 Nycolas Souza.

É uma licença permissiva: qualquer pessoa pode usar, copiar, modificar e distribuir o código, inclusive em projetos comerciais, desde que mantenha o aviso de copyright e o texto da licença.

O texto completo está em [LICENSE](LICENSE).
