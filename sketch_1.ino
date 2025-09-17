#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial rfid(2, 3);  // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address

const int buzzerPin = 4;

struct Item {
  String tag;
  String name;
  int price;
};

Item items[] = {
  {"5300B295BBCF", "Milk", 20},
  {"5300B33638EE", "Bread", 15},
  {"5300B29ACDB6", "Juice", 30},
  {"5300B2985A23", "Soap", 10},
  {"5300B333C516", "Eggs", 25}
};

const int itemCount = sizeof(items) / sizeof(items[0]);
bool isScanned[itemCount] = {false};  // Track scan state
int total = 0;

// Find item index by tag
int findItemIndexByTag(String tag) {
  for (int i = 0; i < itemCount; i++) {
    if (items[i].tag == tag) {
      return i;
    }
  }
  return -1;
}

void setup() {
  Serial.begin(9600);
  rfid.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Scan an item...");
}

void loop() {
  // RFID sends 12 characters
  if (rfid.available() >= 12) {
    String rawTag = "";
    while (rfid.available()) {
      char ch = rfid.read();
      // Accept only hex digits
      if (isPrintable(ch)) {
        rawTag += ch;
      }
      delay(5);
    }

    rawTag.trim();  // Remove any \r \n
    Serial.println("Tag Scanned: " + rawTag);

    int index = findItemIndexByTag(rawTag);
    lcd.clear();

    if (index != -1) {
      Item item = items[index];
      if (!isScanned[index]) {
        // Add item
        total += item.price;
        isScanned[index] = true;

        lcd.setCursor(0, 0);
        lcd.print("Added: " + item.name);
        lcd.setCursor(0, 1);
        lcd.print("Rs: " + String(item.price));
        Serial.println("Added: " + item.name);
      } else {
        // Remove item
        total -= item.price;
        isScanned[index] = false;

        lcd.setCursor(0, 0);
        lcd.print("Removed: " + item.name);
        lcd.setCursor(0, 1);
        lcd.print("Rs: -" + String(item.price));
        Serial.println("Removed: " + item.name);
      }

      // Buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);

      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total: Rs " + String(total));
      Serial.println("Total: Rs " + String(total));
      delay(1000);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Unknown Item");
      lcd.setCursor(0, 1);
      lcd.print("Try again");
      Serial.println("Unknown tag.");
      delay(1000);
    }
  }
}
