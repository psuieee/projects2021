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

  byte buffer[18];
  byte block = 1;
  byte len = 18;

  // authenticate
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
     Serial.println("Failed to authenticate");
     return;
  }
  Serial.println("Successfully Authenticated");

  // get data
  status = mfrc522.MIFARE_Read(block, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.println("Failed to read card");
    return;
  }

  // print data
  Serial.print("Data: ");
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 32) {
      Serial.write(buffer[i]);
    }
  }
  Serial.println();
}
