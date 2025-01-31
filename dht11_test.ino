#include <DHT.h>

DHT dht(14, DHT11);

void setup(){
  dht.begin();
  delay(2000);
   Serial.begin(115200) ;
}

void loop(){
  Serial.print(dht.readTemperature());
  Serial.print(" & ");
  Serial.print(dht.readHumidity());
  delay(2000);
}