#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>


// RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);


// LCD (1602, no I2C) pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, A0, A1, A2, A3);


// Servo
Servo myServo;


// Output pins
const int greenLED = 3;
const int redLED = 4;
const int buzzer = 5;
const int servoPin = 6;


// Correct UID (change if needed)
byte correctUID[] = {0xF3, 0x65, 0x30, 0x2A}; 
const byte uidLength = 4;


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();


  lcd.begin(16, 2);
  lcd.print("Place your card");


  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);


  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);


  myServo.attach(servoPin);
  myServo.write(0); // Start locked
}


void loop() {
  // Wait for a new card
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;


  // Print UID for reference
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print("0x");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i != mfrc522.uid.size - 1) Serial.print(", ");
  }
  Serial.println();


  // Compare UID
  if (compareUID(mfrc522.uid.uidByte, correctUID, uidLength)) {
    grantAccess();
  } else {
    denyAccess();
  }


  // Cleanup
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();


  delay(2000);  // Pause before next scan
  resetOutputs();
}


bool compareUID(byte *a, byte *b, byte len) {
  for (byte i = 0; i < len; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}


void grantAccess() {
  Serial.println("Access granted");
  lcd.clear();
  lcd.print("Welcome!");
  digitalWrite(greenLED, HIGH);
  myServo.write(90); // Open door
}


void denyAccess() {
  Serial.println("Access denied");
  lcd.clear();
  lcd.print("Check the card");
  digitalWrite(redLED, HIGH);
  digitalWrite(buzzer, HIGH);
  myServo.write(0); // Keep closed
}


void resetOutputs() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  lcd.print("Place your card");
}

