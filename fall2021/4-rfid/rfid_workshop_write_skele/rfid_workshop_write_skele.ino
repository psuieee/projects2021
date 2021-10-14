#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Ready to scan");
}

void loop() {
    
  // prep key
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  // reset loop if no card present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // select a card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("New card detected");

  MFRC522::StatusCode status;
  byte buffer[34];
  byte block;
  byte len;

  // get data
  
  block = 1;
  // authenticate

  // write

}
