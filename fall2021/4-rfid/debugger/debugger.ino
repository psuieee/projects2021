#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

/*
* PENN STATE IEEE FA21
* RFID Workshop Debugger
* 
* The Penn State IEEE RFID Debugger is a debugging tool for MFRC522 boards and
* the RFID cards those boards can read. The debugger consists of an Arduino
* Nano, an MFRC522, an SSD1306 128x64 OLED screen, and 4 pushbuttons. 
*
*/

// input button pins
#define BUTTON_1 5
#define BUTTON_2 4
#define BUTTON_3 3
#define BUTTON_4 2

// MFRC522 rst and ss pins
#define RST_PIN 9
#define SS_PIN 10

// SSD1306 params
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// global vars
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

boolean pressed1 = false;
boolean pressed2 = false;
boolean pressed3 = false;
boolean pressed4 = false;

String buttonFnNames[4] = {"", "", "", "CLS"};

void setup() {
  // init ssd1306
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // splish splash
  display.display();
  delay(250);  
  //display.clearDisplay();

  // kitschy init text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Display Initialized");
  display.display();
  
  // set auth key. unsure if this does anything
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  
  // button setup
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  
  // init serial
  Serial.begin(115200);
  while(!Serial);
  display.println("Serial Initialized");
  display.display();

  // init mfrc522
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  display.println("Reader Initialized");
  display.display();
  mfrc522.PCD_DumpVersionToSerial();
  display.println("READY");
  display.display();
  delay(500);  

  // set default display text
  displayInit();

}

void loop() {

  // check buttons
  buttonCheck();
  
  // reset loop if no new card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // select a card, reset loop on failure
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // clear oled
  display.clearDisplay();

  // housekeeping
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  buttonFns(); // draw button labels
  display.setCursor(0, 0);
  
  // gib uid
  char uidStr[32] = "";
  array_to_string(mfrc522.uid.uidByte, 4, uidStr); 
  display.setCursor(0,0);
  display.print("UID:");
  display.println(uidStr);
  
  // gib picc type name
  display.print("TYPE:");
  display.print(mfrc522.PICC_GetTypeName(piccType));
  display.display();

  // dumpy
  writeScan(); // write scan w/ black bg to indicate card is being read
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); // dump hex to serial
  scanReady(); // write scan with white bg to indicate that card can be read
}

void buttonCheck() { // check for button presses and do fns
  if((digitalRead(BUTTON_1) == LOW) && !pressed1) { // no function
    pressed1 = true;
  } else if (pressed1 && (digitalRead(BUTTON_1) == HIGH)) {
    pressed1 = false;
  }
  
  if((digitalRead(BUTTON_2) == LOW) && !pressed2) { // no function
    pressed2 = true;
  } else if (pressed2 && (digitalRead(BUTTON_2) == HIGH)) {
    pressed2 = false;
  }
  
  if((digitalRead(BUTTON_3) == LOW) && !pressed3) { // no function
    pressed3 = true;
  } else if (pressed3 && (digitalRead(BUTTON_3) == HIGH)) {
    pressed3 = false;
  }
  
  if((digitalRead(BUTTON_4) == LOW) && !pressed4) { // reset display
    displayInit();
    
    pressed4 = true;
  } else if (pressed4 && (digitalRead(BUTTON_4) == HIGH)) {
    pressed4 = false;
  }
}

void scanReady() { // draw inverted SCAN text to indicate that a card can be read
  display.fillRect(103, 0, 128, 11, WHITE);
  display.setTextColor(BLACK);
  writeScan();
  display.setTextColor(WHITE);
}

void writeScan() { // draw SCAN text
  display.setCursor(104,2);
  display.println("SCAN");
  display.display();
}

void buttonFns() { // draw button labels at bottom of the screen
  // frame
  display.drawLine(0, 50, 128, 50, WHITE);
  for (int i = 1; i < 4; i++) {
    display.drawLine(32*i, 50, 32*i, 64, WHITE);
  }

  // labels
  for (int i = 0; i < 4; i++) {
    display.setCursor((32*i)+4, 54);
    display.print(buttonFnNames[i]);
  }

  display.display();
}

void displayInit() { // draw inital display items
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("UID:\nTYPE:");
  scanReady();
  buttonFns();
  display.display();
}

void array_to_string(byte array[], unsigned int len, char buffer[]) {
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';
}
