#define BLYNK_PRINT Serial
 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "SC5nTryZByqNXNQLwy2qfIvCRk1lxZ0_";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "WiFi";
//char pass[] = "12345678";
char ssid[] = "H!T";
char pass[] = "H!RO-015";

#define DHTPIN 0          // D3
#define soil_moisture_pin A0
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11



DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float moisture_percentage;
  moisture_percentage = ( 100.00 - ( (analogRead(soil_moisture_pin)/1023.00) * 100.00 ) );
  Blynk.virtualWrite(V7, moisture_percentage);

  //TESTING THE SENSOR OUTPUT IN SERIAL MONITOR
  Serial.print("Soil Moisture: ");
  Serial.print(moisture_percentage);
  Serial.print(" Temprature: ");
  Serial.print(t);
  Serial.print(" Humidity: ");
  Serial.print(h);
  Serial.print("\n");

  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  
}

 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
