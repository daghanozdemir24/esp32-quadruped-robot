# ESP32 Bluetooth Quadruped Robot Controller

An embedded locomotion controller for a 4-legged (quadruped) walking robot. The system is powered by an **ESP32 DevKit**, communicating wirelessly via **Bluetooth SPP (Serial Port Profile)**, and actuates servos through an I2C-driven **PCA9685 16-Channel 12-bit PWM Driver**.

## 🚀 Key Features
* **Actuator Control via I2C:** Generates precise 50 Hz PWM signals utilizing the PCA9685 PWM driver to command 4 micro servo motors.
* **Bluetooth Telemetry & Control:** Implements non-blocking Bluetooth serial command ingestion for manual leg trimming and automated gaits.
* **Gait & Locomotion Routines:**
  * **Individual Leg Trimming:** Manual step adjustments per leg for calibration.
  * **Automated Gait Cycles:** Coordinated diagonal pairs for forward and reverse crawl sequences.
  * **Differential Turning:** Coordinated phase delays for clockwise and counter-clockwise steering.
  * **Neutral Center Reset:** Automatic default stance calibration (90° trim point).

## 📁 Repository Structure
* `esp32_quadruped_controller.ino`: Main firmware handling Bluetooth UART events, PWM duty-cycle mapping, and kinematic sequence routines.

## 🕹️ Control Command Mapping (Bluetooth Serial)

| Command (Char) | Target / Subsystem   |               Action                  |
|    ------      |        ------        |               ------                  |
| `a` / `b`      | Front-Right Leg (B0) | Increment / Decrement Position        |
| `c` / `d`      | Front-Left Leg (B1)  | Increment / Decrement Position        |
| `e` / `f`      | Rear-Right Leg (B2)  | Increment / Decrement Position        |
| `g` / `h`      | Rear-Left Leg (B3)   | Increment / Decrement Position        |
| `F`            | Locomotion Engine    | Automated 3-Step Forward Walk         |
| `B`            | Locomotion Engine    | Automated 3-Step Reverse Walk         |
| `1`            | Steering Engine      | Turn Right Routine                    |
| `2`            | Steering Engine      | Turn Left Routine                     |
| `S`            | Safety / System      | Stop & Reset All Legs to Center (90°) |

## 🛠️ Hardware Setup & Wiring

| ESP32 Pin     | PCA9685 Driver Pin |               Description                |
|    ------     |      ------        |                  ---                     |
| `3V3`         | `VCC`              |               Logic Power                |
| `GND`         | `GND`              | Logic & Bus Ground (Shared with Battery) |
| `GPIO 22`     | `SCL`              |              I2C Clock Line              |
| `GPIO 21`     | `SDA`              |              I2C Data Line               |
| External Rail | `V+`               |     External 5V - 6V Power for Servos    |

## 💻 Flashing & Deployment

### 1. Dependencies
Install the following libraries in Arduino IDE:
* `Adafruit PWM Servo Driver Library`

### 2. Flashing
1. Select **ESP32 Dev Module** under Arduino IDE boards.
2. Connect your ESP32 via USB and upload `esp32_quadruped_controller.ino`.

### 3. Pairing
1. Power on the robot.
2. Pair your mobile phone or PC to Bluetooth device: `Daghan_Robot_Master`.
3. Open any Bluetooth Serial Terminal app (115200 baud) and send mapped command characters.

## 👤 Author
* **Dağhan Özdemir** - [GitHub Profile](https://github.com/daghanozdemir24)
