# mekaHandTouchInterface

## Components N² diagram

| Component ↓ / →       | Piezo Sensors | Multiplexers     | ESP32 (FreeRTOS)          | ROS2 Hardware Interface      | ROS2 Topic           |
| --------------------- | ------------- | ---------------- | ------------------------- | ---------------------------- | -------------------- |
| **Piezo Sensors**     |               | Analog signals → |                           |                              |                      |
| **Multiplexers**      |               |                  | Selected analog signal → |                              |                      |
| **ESP32 (FreeRTOS)**  | ← Sensor data | ← MUX data       |                           | ↔ Handshake, data (via USB)  |                      |
|                       |               |                  | Filters, buffers data     | Sends filtered data →        |                      |
| **ROS2 HW Interface** |               |                  | ← Filtered data (via USB) |                              | → Publishes to topic |
| **ROS2 Topic**        |               |                  |                           | ← Data posted at sample rate |                      |

## Functional N² diagram

| Task ↓ / →                 | T1: Sensor Scan | T2: Data Filtering | T3: Handshake Protocol   | T4: Rate Config   | T5: TX Data     | T6: RX Data | T7: ROS2 Publish       |
| -------------------------- | --------------- | ------------------ | ------------------------ | ----------------- | --------------- | ----------- | ---------------------- |
| **T1: Sensor Scan**        |                 | → Raw sensor data  |                          |                   |                 |             |                        |
| **T2: Data Filtering**     | ← Sensor data   |                    |                          |                   | → Filtered data |             |                        |
| **T3: Handshake Protocol** |                 |                    |                          | → Triggers config |                 |             |                        |
| **T4: Rate Config**        |                 | → Filter params    | ← Initiated by handshake |                   |                 |             |                        |
| **T5: TX Data**            |                 | ← Filtered data    |                          | ← Rate info       |                 | → USB Data  |                        |
| **T6: RX Data**            |                 |                    |                          |                   | ← USB Data      |             | → Filtered ROS message |
| **T7: ROS2 Publish**       |                 |                    |                          |                   |                 | ← Data msg  |                        |


