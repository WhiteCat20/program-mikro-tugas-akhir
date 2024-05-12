#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_ADS1X15.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
Adafruit_ADS1115 ads;

// Relay Pin Variabels
int fan_pin = 7;
int lamp_pin = 9;

//PCB Variabels
int red_led_pin = 5;
bool is_led_on = false;
int button_pin = 8;


void setup() {
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  ads.begin();
  pinMode(fan_pin, OUTPUT);
  pinMode(lamp_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_val = digitalRead(button_pin);
  static unsigned long lastPrintTime = 0; // Variabel untuk menyimpan waktu terakhir mencetak
  int16_t adc0 = ads.readADC_SingleEnded(0);
  float voltage = (adc0 * 0.1875F) / 1000;
  Serial.println(voltage, 2);
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '1') {
      digitalWrite(lamp_pin, !digitalRead(lamp_pin)); 
    } else if (receivedChar == '2') {
      digitalWrite(fan_pin, !digitalRead(fan_pin)); 
    }
    // else if (receivedChar == '3') {
    //   // Apabila button ditekan, maka mulai print nilai voltage
    //   lastPrintTime = millis(); // Set waktu terakhir mencetak menjadi waktu saat ini
    //   while (millis() - lastPrintTime < 60000) { // Loop selama 60 detik
    //     Serial.println(voltage);
    //     delay(1000); // Tunggu 1 detik sebelum mencetak lagi
    //   }
    // }
  }
  lcd.setCursor(0, 0);
  lcd.print("MQ-3 = ");
  lcd.print(voltage,2);
  lcd.print(" Volt");
  lcd.setCursor(0, 1);
  lcd.print("Oke bang ");
  delay(1000);
}
