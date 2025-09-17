#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial rfid(2, 3);  // RX, TX (Only RX used)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address of LCD

const int buzzerPin = 4;  // Buzzer connected to D4

struct Item {
  String name;
  int price;
};

int total = 0;

Item getItemByRFID(String tag) {
  if (tag == "5300B295BBCF") return {"Milk", 20};
  if (tag == "5300B33638EE") return {"Bread", 15};
  if (tag == "5300B29ACDB6") return {"Juice", 30};
  if (tag == "5300B2985A23") return {"Soap", 10};
  if (tag == "5300B333C516") return {"Eggs", 25};
  return {"Unknown", 0};
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
  if (rfid.available() >= 12) {
    String tag = "";
    for (int i = 0; i < 12; i++) {
      char ch = rfid.read();
      tag += ch;
    }

    Item item = getItemByRFID(tag);
    lcd.clear();

    if (item.name != "Unknown") {
      total += item.price;
      Serial.print("Scanned: ");
      Serial.print(item.name);
      Serial.print(" | Price: Rs");
      Serial.print(item.price);
      Serial.print(" | Total: Rs");
      Serial.println(total);

      // Short beep for valid scan
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);

      // Show item and price
      lcd.setCursor(0, 0);
      lcd.print("Item: " + item.name);
      lcd.setCursor(0, 1);
      lcd.print("Rs: " + String(item.price));
      delay(2000);

      // Show total
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total: Rs " + String(total));
      delay(2000);
    } else {
      Serial.println("Unknown Item");
      lcd.setCursor(0, 0);
      lcd.print("Unknown Item");
      lcd.setCursor(0, 1);
      lcd.print("Try again");
      delay(2000);
    }

    while (rfid.available()) rfid.read();  // Clear buffer
    delay(1000);
  }
}