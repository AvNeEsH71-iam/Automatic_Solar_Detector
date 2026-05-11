# Automatic Solar Tracker using LDR and Arduino

A dual-axis automatic solar tracker built using **LDR sensors, Arduino Uno, and SG90 servo motors** to continuously orient a solar panel toward the brightest light source for maximum energy harvesting.

---

## Overview

This project was developed as part of the **PHY312 : Advanced Electronics & Instrumentation Lab** at the Indian Institute of Science Education and Research Mohali.

The tracker uses:

* **4 LDRs** arranged in a quadrant sensor array
* **Arduino Uno** for real-time control
* **2 servo motors** for dual-axis movement
* A simple **feedback control algorithm**

The system automatically adjusts the panel orientation in both:

* **Azimuth** (left-right)
* **Elevation** (up-down)

to minimize cosine losses and improve solar energy collection.

---

##  Features

*  Dual-axis solar tracking
*  Real-time light sensing using LDRs
*  Closed-loop feedback control
*  Simple and low-cost design
*  Estimated **35–40% higher energy collection**
*  Fully programmed in Arduino C++
*  Breadboard-friendly implementation
*  Simulated and tested in Wokwi

---

## Components Used

| Component            | Quantity |
| -------------------- | -------- |
| Arduino Uno          | 1        |
| LDR Sensors (GL5539) | 4        |
| 10kΩ Resistors       | 4        |
| SG90 Servo Motors    | 2        |
| Mini Solar Panel     | 1        |
| Breadboard           | 1        |
| Jumper Wires         | Several  |
| 100µF Capacitors     | 2        |
| Pan-Tilt Mount       | 1        |

---

## ⚙️ Working Principle

The four LDRs are arranged in a cross-shaped configuration.

When sunlight falls unevenly:

* One side receives more light
* Resistance changes in the corresponding LDRs
* Arduino detects voltage differences
* Servo motors rotate the panel toward the brighter direction

The system continuously repeats this process every 100 ms.

---

## Core Equations

### Voltage Divider Output

V_{out}=V_{CC}\cdot\frac{R_f}{R_{LDR}+R_f}

### Lambert’s Cosine Law

P=P_0\cos\theta

### Azimuth Error Signal

e_{az}=(V_1+V_3)-(V_2+V_4)

### Elevation Error Signal

e_{el}=(V_1+V_2)-(V_3+V_4)

---

## Control Algorithm

```cpp
error_az = (V1 + V3) - (V2 + V4)
error_el = (V1 + V2) - (V3 + V4)

if(abs(error_az) > dead_band)
    move azimuth servo

if(abs(error_el) > dead_band)
    move elevation servo
```

The dead-band prevents unnecessary servo jitter and stabilizes the system.

---

## Expected Performance

| Parameter             | Value       |
| --------------------- | ----------- |
| Tracking Accuracy     | ~ ±3°       |
| Control Loop Delay    | 100 ms      |
| Estimated Energy Gain | 35–40%      |
| Servo Response Time   | 2–4 seconds |
| Approximate Cost      | < ₹1000     |

---

## Simulation

The system was simulated using:

* [Wokwi Arduino Simulator](https://wokwi.com?utm_source=chatgpt.com)

Simulation results showed stable tracking with low steady-state error and smooth servo response.

---

## Future Improvements

* Add RTC + GPS based astronomical tracking
* Replace servos with stepper motors
* Add IoT monitoring using ESP32
* Implement real-time power measurement
* Improve cloud-day tracking reliability

---

## Concepts Demonstrated

* Voltage Divider Networks
* LDR Characteristics
* ADC (Analog-to-Digital Conversion)
* Feedback Control Systems
* PWM Servo Control
* Embedded Systems Programming
* Solar Energy Optimization

---

## Repository Structure

```bash
├── README.md
├── Arduino_Code/
│   └── solar_tracker.ino
├── Report/
│   └── PHY312-Report-Group3.pdf
├── Circuit_Diagrams/
├── Images/
└── Simulation/
```

---

## 👨‍💻 Authors

* Avneesh Singh
* Tisha Dewangan
* Brahamjot Singh

Group 3 — PHY312 Lab Project

---

## References

1. Abdallah & Nijmeh — Two-axis sun tracking systems
2. Eke & Taneli — Performance comparison of solar trackers
3. Arduino Documentation
4. GL5539 LDR Datasheet

---

## License

This project is intended for educational and academic purposes.

MIT License recommended.

---

## Acknowledgement

Special thanks to the PHY312 course instructor and the Indian Institute of Science Education and Research Mohali for supporting this project.
