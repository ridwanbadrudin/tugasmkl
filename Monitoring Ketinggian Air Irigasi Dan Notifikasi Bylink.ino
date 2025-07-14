#define BLYNK_TEMPLATE_ID "TMPL6JRdC5Irw"
#define BLYNK_TEMPLATE_NAME "MONITORING KETINGGIAN AIR"
#define BLYNK_AUTH_TOKEN "YRya5SMUgemagdULuF1SoyLsgfpbKh5P"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define Echo 15
#define Trig 4
#define Merah 14
#define Kuning 12
#define Hijau 13

BlynkTimer timer;

float distance = 0;
float ketinggian = 0;

void ukur_jarak() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  int duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;
  ketinggian = 400 - distance;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" CM");

  Serial.print("Ketinggian Air: ");
  Serial.print(ketinggian);
  Serial.println(" CM");

  Blynk.virtualWrite(V0, ketinggian);

  // Logika LED Virtual dan Fisik
  if (ketinggian < 100) {
    digitalWrite(Merah, HIGH);
    digitalWrite(Kuning, LOW);
    digitalWrite(Hijau, LOW);
    Blynk.virtualWrite(V1, 255);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
  } 
  else if (ketinggian < 200) {
    digitalWrite(Merah, LOW);
    digitalWrite(Kuning, HIGH);
    digitalWrite(Hijau, LOW);
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 255);
    Blynk.virtualWrite(V3, 0);
  } 
  else {
    digitalWrite(Merah, LOW);
    digitalWrite(Kuning, LOW);
    digitalWrite(Hijau, HIGH);
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 255);
  }
}  // ← PASTIKAN KURUNG TUTUP INI ADA!!

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Merah, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);

  timer.setInterval(1000L, ukur_jarak);
}

void loop() {
  Blynk.run();
  timer.run();
}
