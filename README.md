# Motorized-zen-garden

<img width="1289" height="751" alt="image" src="https://github.com/user-attachments/assets/cca61016-5026-4a85-9810-2a452b4da372" />
This zen garden is a 3d printed recreation of the motorized ones that draw patterns for you that costs only 60$. 
It was made for my 3rd hackclub project and I hope to get the certificate.
The zen garden uses 2 8mm stepper motors powered by an esp32 to control a SCARA using inverse kinematics to calculate angles required.
It is controlled from a web page hosted on the esp32 wifi and lets you draw your own patterns.


<br></br>
Wiring:

| Category | Function | ESP32-C3 Pin | Driver 1 (Motor A) | Driver 2 (Motor B) |
| :--- | :--- | :--- | :--- | :--- |
| **Power** | Logic (3.3V) | 3V3 | VCC | VCC |
| **Power** | Motor (5V USB) | 5V | VM | VM |
| **Power** | Ground | GND | GND | GND |
| **Control** | Standby (Enable) | GPIO 10 | STBY | STBY |
| **Control** | Speed (Always On) | 3V3 (Jumper) | PWMA, PWMB | PWMA, PWMB |
| **Signal** | Motor 1 Phase A | GPIO 0, 1 | AIN1, AIN2 | — |
| **Signal** | Motor 1 Phase B | GPIO 2, 3 | BIN1, BIN2 | — |
| **Signal** | Motor 2 Phase A | GPIO 4, 5 | — | AIN1, AIN2 |
| **Signal** | Motor 2 Phase B | GPIO 6, 7 | — | BIN1, BIN2 |
| **Output** | Coil 1 | — | AO1, AO2 | — |
| **Output** | Coil 2 | — | BO1, BO2 | — |
| **Output** | Coil 1 | — | — | AO1, AO2 |
| **Output** | Coil 2 | — | — | BO1, BO2 |
For the 8mm Stepper Motors, make sure you connect one coil pair to AO1/AO2 and the other pair to BO1/BO2. If the motor vibrates but doesn't spin, swap the two wires on AO1 and AO2.

<img width="589" height="762" alt="583679621-9ab5ed0f-2b91-41fe-a8dd-2e0cf367602a" src="https://github.com/user-attachments/assets/7eda8f51-c523-49a9-bd64-7c834f359b07" />



<img width="756" height="595" alt="image" src="https://github.com/user-attachments/assets/c164bef1-3218-4e2e-9f90-c37a864992c4" />

BOM:


| Category | Component | Specification |
| :--- | :--- | :--- |
| **Microcontroller** | **ESP32-C3 SuperMini** | RISC-V architecture, high-performance WiFi/BLE |
| **Motor Drivers** | **2x TB6612FNG** | High-efficiency Dual H-Bridge drivers |
| **Motors** | **2x Micro Steppers** | 8mm 2-Phase 4-Wire precision motors |
| **Kinematics** | **Magnetic Linkage** | N52 Neodymium Disc (1/8") + 8mm Steel Ball |
| **Construction** | **3D Printed PETG** | Chosen for durability and thermal resistance |
| **Interface** | **Web Dashboard** | Hosted locally on the ESP32-C3 |

> **Total Project Cost:** ~$60 USD
