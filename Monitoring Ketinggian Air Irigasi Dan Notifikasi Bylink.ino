#define BLYNK_TEMPLATE_ID "TMPL6r5GB95yQ"
#define BLYNK_TEMPLATE_NAME "MONITORING KETINGGIAN AIR IRIGASI"
#define BLYNK_AUTH_TOKEN "oOG01KSJdS1tqiJEVGgzkDxnkS3WT9Px"

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
  // Kirim pulsa ke sensor
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // Baca durasi echo
  int duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;  // Hitung jarak
  ketinggian = 350 - distance;     // Asumsikan tinggi wadah = 350 cm

  // Tampilkan di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" CM");

  Serial.print("Ketinggian Air: ");
  Serial.print(ketinggian);
  Serial.println(" CM");

  // Kirim ke Blynk Virtual Pin V0
  Blynk.virtualWrite(V0, ketinggian);

  // Logika LED berdasarkan ketinggian
  if (ketinggian < 100) {
    digitalWrite(Merah, HIGH);
    digitalWrite(Kuning, LOW);
    digitalWrite(Hijau, LOW);
  } 
  else if (ketinggian >= 100 && ketinggian < 200) {
    digitalWrite(Merah, LOW);
    digitalWrite(Kuning, HIGH);
    digitalWrite(Hijau, LOW);
  } 
  else {
    digitalWrite(Merah, LOW);
    digitalWrite(Kuning, LOW);
    digitalWrite(Hijau, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(Merah, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);

  timer.setInterval(1000L, ukur_jarak); // Ukur tiap 1 detik
}

void loop() {
  Blynk.run();
  timer.run();
}
