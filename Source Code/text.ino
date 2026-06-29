 #include <LiquidCrystal.h>

// LCD Pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int smokeSensor = A0;   // MQ-2 Sensor
const int tempSensor = A1;    // LM35 Sensor
const int buzzer = 8;

int smokeThreshold = 300;
float tempThreshold = 50.0;

void setup() {
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Fire Alert Sys");

  Serial.begin(9600);   // GSM Module Communication

  delay(2000);
  lcd.clear();
}

void loop() {
  int smokeValue = analogRead(smokeSensor);

  int tempValue = analogRead(tempSensor);
  float temperature = (tempValue * 5.0 * 100.0) / 1024.0;

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Smoke:");
  lcd.print(smokeValue);

  if (smokeValue > smokeThreshold || temperature > tempThreshold) {

    digitalWrite(buzzer, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE DETECTED!");
    lcd.setCursor(0, 1);
    lcd.print("Sending SMS...");

    sendSMS();

    delay(5000);
  }
  else {
    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}

void sendSMS() {
  Serial.println("AT");
  delay(1000);

  Serial.println("AT+CMGF=1");
  delay(1000);

  Serial.println("AT+CMGS=\"+91XXXXXXXXXX\""); // Replace with mobile number
  delay(1000);

  Serial.print("Alert! Fire detected. Check immediately.");
  delay(1000);

  Serial.write(26); // Ctrl+Z to send SMS
  delay(3000);
}


