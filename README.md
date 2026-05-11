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

### 1. Voltage Divider Equation

This equation converts the LDR resistance into a measurable voltage for the Arduino.

Vout = VCC × (Rf / (RLDR + Rf))

Where:

- Vout → Output voltage read by Arduino
- VCC → Supply voltage (5V)
- Rf → Fixed resistor (10kΩ)
- RLDR → Resistance of the LDR

---

### 2. Lambert’s Cosine Law

The power received by the solar panel depends on the angle of sunlight.

P = P0 × cos(θ)

Where:

- P → Effective power received
- P0 → Maximum power when sunlight is perpendicular
- θ → Angle between sunlight and panel normal

---

### 3. Azimuth Error Signal

Used to determine whether the panel should move left or right.

eaz = (V1 + V3) − (V2 + V4)

Where:

- V1 → Top-left LDR voltage
- V2 → Top-right LDR voltage
- V3 → Bottom-left LDR voltage
- V4 → Bottom-right LDR voltage

---

### 4. Elevation Error Signal

Used to determine whether the panel should move up or down.

eel = (V1 + V2) − (V3 + V4)

---

### 5. Servo Angle Update Equation

The servo angle changes proportionally to the detected error.

Δϕ = Kp × e

Where:

- Δϕ → Change in servo angle
- Kp → Proportional gain constant
- e → Error signal

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

##  Authors

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
