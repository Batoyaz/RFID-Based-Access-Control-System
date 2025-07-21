# RFID-Based-Access-Control-System
This Arduino project is an RFID-based access control system that uses an MFRC522 reader to scan RFID cards and verify access. When a valid card is detected, a welcome message appears on a 1602 LCD, a green LED lights up, and a servo motor rotates to unlock a door. If the card is invalid, a red LED and buzzer are activated, and the door remains locked. The system resets after each scan and is suitable for basic security applications such as smart doors, lockers, or entry systems.
connections:

-RFID RC522 Connections:

SDA to pin 10

SCK to pin 13

MOSI to pin 11

MISO to pin 12

RST to pin 9

3.3V to 3.3V on Arduino

GND to GND

-1602 LCD (without I2C) Connections:

VSS to GND

VDD to 5V

V0 to the middle pin of a 10k potentiometer (for contrast)

RS to pin 7

R/W to GND

E to pin 8

D4 to A0

D5 to A1

D6 to A2

D7 to A3

A (LED+) to 5V through a 220Ω resistor

K (LED-) to GND

-Servo Motor Connections:

Signal wire to pin 6

VCC (red wire) to 5V (use external power if needed)

GND to GND

-LED and Buzzer Connections:

Green LED anode to pin 3 (with a 220Ω resistor to GND)

Red LED anode to pin 4 (with a 220Ω resistor to GND)

Buzzer positive to pin 5, negative to GND
