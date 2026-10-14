#include <Servo.h>
#include <HCSR04.h>

#define servoPin 9
#define buzzerPin 4
#define kirmiziLed 5
#define sariLed 6
#define yesilLed 7

UltraSonicDistanceSensor distanceSensor(13, 12);
Servo radarServo;
int mesafe = 0;

void setup() {
  Serial.begin(9600);
  radarServo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(kirmiziLed, OUTPUT);
  pinMode(sariLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(kirmiziLed, LOW);
  digitalWrite(sariLed, LOW);
  digitalWrite(yesilLed, HIGH);
}

void tehlikeKontrol(int d) {
  if (d > 0 && d <= 12) {
    digitalWrite(kirmiziLed, HIGH);
    digitalWrite(sariLed, LOW);
    digitalWrite(yesilLed, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(20);
    digitalWrite(buzzerPin, LOW);
  } else if (d > 12 && d <= 28) {
    digitalWrite(kirmiziLed, LOW);
    digitalWrite(sariLed, HIGH);
    digitalWrite(yesilLed, LOW);
    static int bipSayac = 0;
    if (++bipSayac % 4 == 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(25);
      digitalWrite(buzzerPin, LOW);
    }
  } else {
    digitalWrite(kirmiziLed, LOW);
    digitalWrite(sariLed, LOW);
    digitalWrite(yesilLed, HIGH);
    digitalWrite(buzzerPin, LOW);
  }
}

void loop() {
  for (int aci = 15; aci <= 165; aci++) {
    radarServo.write(aci);
    delay(30);
    mesafe = distanceSensor.measureDistanceCm();
    tehlikeKontrol(mesafe);
    Serial.print(aci);
    Serial.print(",");
    Serial.print(mesafe);
    Serial.print(".");
  }
  for (int aci = 165; aci >= 15; aci--) {
    radarServo.write(aci);
    delay(30);
    mesafe = distanceSensor.measureDistanceCm();
    tehlikeKontrol(mesafe);
    Serial.print(aci);
    Serial.print(",");
    Serial.print(mesafe);
    Serial.print(".");
  }
}
