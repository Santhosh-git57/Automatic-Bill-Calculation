# Automatic Bill Calculation System

This project automates the bill calculation process in retail environments using **Arduino Nano** and an **RFID system**.  
When a customer scans items using RFID tags, the system automatically adds the item’s cost and displays the running total on an LCD screen.

---

## 🚀 Features
- Automatic item recognition using RFID.
- Real-time bill calculation.
- LCD display showing items and total cost.
- Buzzer alert for invalid scans.
- Low-cost, portable, and efficient system.

---

## 🛠️ Components Used
- Arduino Nano
- EM-18 RFID Reader
- RFID Tags
- 16x2 LCD Display
- Breadboard & Jumper Wires
- Buzzer
- Power Supply

---

## ⚡ How It Works
1. Each item has a unique RFID tag.
2. When scanned, the Arduino checks the tag ID.
3. The corresponding item price is added to the total.
4. The LCD shows the current bill amount.
5. If an unrecognized tag is scanned, the buzzer alerts.

---

## 📂 Project Files
- `sketch_1→ Final Arduino code.
- `sketch_2` → Backup/earlier version of the code.

---

## 🖼️ Circuit Diagram
<img width="494" height="513" alt="block diagram" src="https://github.com/user-attachments/assets/60944094-4d61-4aba-9954-ccf6d7863fb8" />

---

## 🔧 Setup Instructions
1. Clone this repo:
   ```bash
   git clone https://github.com/Santhosh-git57/Automatic-Bill-Calculation.git
