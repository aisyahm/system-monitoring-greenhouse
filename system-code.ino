#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "PtumtV4g3NTCKd1sPEIrKX2radqMfHcY";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "OPPO A31";
char pass[] = "12345678";
// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1
// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(0, 1); // RX, TX
// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

#include <DHT.h>
ESP8266 wifi(&Serial);
DHT dht(8, DHT11);
int sensorLDR = A0;
const int pinLED = 10;
int kipas= 9;

void setup()
{
  // Debug console
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  Serial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  pinMode(pinLED, OUTPUT);
  pinMode(kipas, OUTPUT);
  dht.begin();
}
void loop()
{
  int nilaiSensor;
  nilaiSensor = analogRead(sensorLDR);
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);
  
  if(nilaiSensor >=200){
    digitalWrite(pinLED, HIGH);
    Serial.print("LED nyala");
  }else{
    digitalWrite(pinLED, LOW);
    Serial.print("LED mati");
  }
  delay(1000);

  float a = dht.readHumidity();
  float b = dht.readTemperature();
  int humid = a;
  int suhu = b;
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, humid);
  
  Serial.print("kelembaban: ");
  Serial.print(humid);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);

  if (suhu >=26){
   digitalWrite(kipas, HIGH);
  }
  else{
   digitalWrite(kipas,LOW);    
  }
 Blynk.run();
}
