# ⏱ Arduino Programmable Timer Switch

An **Arduino-based programmable timer switch** that allows users to set **hours, minutes, and seconds** using push buttons and control a **relay output**.  
The system displays all information on a **16×2 I2C LCD** and is suitable for automation and timing-based control applications.

---

## 🔧 Features

- ⏰ Set timer in **hours, minutes, and seconds**
- 📟 User interface using **16×2 I2C LCD**
- 🔘 Button-based navigation (UP, DOWN, SET, MENU)
- 🔌 Relay control for external loads
- 🔁 Real-time countdown display
- ❌ Manual stop/reset option

---

## 🧠 How It Works

1. System waits for the user to enter the menu.
2. User sets:
   - Hours
   - Minutes
   - Seconds
3. Once confirmed, the relay turns **ON**.
4. Countdown begins and is displayed on the LCD.
5. After timer completion, relay turns **OFF** automatically.
6. Timer can be interrupted or reset anytime using buttons.

---

## 🧰 Hardware Required

| Component | Quantity |
|---------|----------|
| Arduino (UNO / Nano) | 1 |
| 16×2 LCD (I2C) | 1 |
| Push Buttons | 4 |
| Relay Module | 1 |
| Jumper Wires | As required |
| Power Supply | 1 |

---

## 🔌 Pin Configuration

### Buttons
| Function | Arduino Pin |
|--------|-------------|
| UP | D2 |
| DOWN | D3 |
| SET | D4 |
| MENU | D5 |

### Output
| Component | Arduino Pin |
|----------|-------------|
| Relay | D8 |

---

## 📚 Libraries Used

Install the following libraries from **Arduino Library Manager**:

- **LiquidCrystal_I2C**
- **Wire (default Arduino library)**

---

## ⚙️ Setup Instructions

1. Connect all components as per pin configuration
2. Install required libraries
3. Open the `.ino` file in Arduino IDE
4. Select correct **Board** and **Port**
5. Upload the code
6. Power the Arduino and start using the timer

---

## 🧪 Applications

- Appliance automation
- Timed power control
- Lab experiments
- Learning embedded systems
- DIY electronics projects
