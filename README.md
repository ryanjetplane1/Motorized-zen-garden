# Motorized-zen-garden

<img width="1289" height="751" alt="image" src="https://github.com/user-attachments/assets/cca61016-5026-4a85-9810-2a452b4da372" />
This zen garden is a 3d printed recreation of the motorized ones that draw patterns for you that costs only 60$. For parts such as the motor arm holder it is reccomended to make it out of 6061 aluminum.
This build was made for my 3rd hackclub project and I hope to get the certificate.
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
<div></div>
I genuinly cant draw so heres an image of 1 motor repeat the same diagram with 2 instead.
<img width="702" height="413" alt="image" src="https://github.com/user-attachments/assets/8003f196-917a-4b15-ba40-a6190b9db06e" />
<div></div>
Heres a diagram of how it works.
<div>
</div>
<img width="756" height="595" alt="image" src="https://github.com/user-attachments/assets/c164bef1-3218-4e2e-9f90-c37a864992c4" />

BOM:


Category,Component,Quantity,Specification,Notes, Link
Microcontroller,ESP32-C3 SuperMini,1,"RISC-V architecture, WiFi/BLE",Main MCU, https://www.amazon.com/AITRIP-ESP32-C3-Development-Board-Bluetooth/dp/B0FBGDFPBQ/ref=sr_1_6?crid=37KV6HQUNLDN3&dib=eyJ2IjoiMSJ9.ain9jVAIYRXw2BXFRrFE-5GcfGCESrmOlQgiyUymIw6dJ3arM1Sz31QGR7VxZaqeS9U49m7gjrnaLvwYvi63Toih6Ic6ni7zEVollxJZipreeIHWgZhqNQgRIJkgVcsndWxo98YfJyMuJq9-tl9_uch65lXrdfiVzxLvWPn8_L1QLeiL3vX3eY-qaAg8jH5e5zlgCUuhGxLlSLg1BoRSzVJVgg4iRT75LT1Tpj5ivkwt60E6SGFHLKnOfEGIf57m1_l9OL-6Jc5khVvcaTZuvujtGS8ETBqRoMVx3G0IeIc.a08Eix8g23r6gdsEUe_Mcn26HjWYKr0I3-fT2Mv4IPc&dib_tag=se&keywords=esp32+c3+supermini&qid=1781110162&sprefix=esp32+c3supermin%2Caps%2C217&sr=8-6
Motor Drivers,TB6612FNG,2,Dual H-Bridge,High-efficiency, https://www.amazon.com/gp/product/B0BLRSWTLM/ref=ox_sc_act_title_1?smid=A2L2YSK9NV3SSU&psc=1
Motors,Micro Stepper Motors,2,8mm 2-Phase 4-Wire,Precision movement, https://www.amazon.com/gp/product/B08346RFVZ/ref=ox_sc_act_title_2?smid=AOIFQITEAJXZV&psc=1
Kinematics,N52 Neodymium Disc,1,"1/8"" diameter",Part of magnetic linkage, https://www.amazon.com/gp/product/B0FNS4L7Y4/ref=ox_sc_act_title_4?smid=A2OHLF2K1I4V3J&th=1
Kinematics,Steel Ball,1,8mm diameter,Part of magnetic linkage, https://www.amazon.com/gp/product/B0FZKJHG5J/ref=ox_sc_act_title_1?smid=A1UCIC7VFI1GV0&th=1
Sand, Fine White Sand, 1, 425g, Patterns, https://www.amazon.com/gp/product/B0F1CR2717/ref=ox_sc_act_title_3?smid=A1EF9C2WRPTL30&psc=1
Leds, Led Light Strip, 1, 3.3ft, Looks Good, https://www.amazon.com/gp/product/B097BX7LRT/ref=ox_sc_act_title_2?smid=A1KV5GR1U2IFEZ&th=1
