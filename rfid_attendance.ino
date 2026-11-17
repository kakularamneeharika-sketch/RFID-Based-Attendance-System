
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 8

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER, OUTPUT);

  Serial.println("RFID Attendance System");
  Serial.println("Scan your RFID card");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card ID: ");

  String cardID = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    cardID += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.println();

  cardID.toUpperCase();

  if (cardID == "A1B2C3D4") {
    Serial.println("Name: Student 1");
    Serial.println("Attendance Marked");
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
  }
  else if (cardID == "12345678") {
    Serial.println("Name: Student 2");
    Serial.println("Attendance Marked");
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
  }
  else {
    Serial.println("Invalid Card");
  }

  Serial.println("-------------------");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000);
}
