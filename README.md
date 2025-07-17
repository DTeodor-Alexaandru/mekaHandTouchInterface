# mekaHandTouchInterface

## N² diagram

| Component ↓ / →             | Sensor Array       | Data Acquisition | Filter Component       | Config Component     | Communication Component     | ROS2 HW Interface  |
| --------------------------- | ------------------ | ---------------- | ---------------------- | -------------------- | --------------------------- | ------------------ |
| **Sensor Array**            |                    | ← Sensor address |                        |                      |                             |                    |
| **Data Acquisition**        | → Raw sensor value |                  | → Raw data             |                      |                             |                    |
| **Filter Component**        |                    | ← Raw data       |                        | ← Filter parameters  | → Filtered sensor data      |                    |
| **Config Component**        |                    |                  | → Filter parameters    |                      | ← Configuration data        |                    |
| **Communication Component** |                    |                  | ← Filtered sensor data | → Configuration data |                             | ↔ Handshake & data |
| **ROS2 HW Interface**       |                    |                  |                        |                      | ↔ Handshake & config + data |                    |




