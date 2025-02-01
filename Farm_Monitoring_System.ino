#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// WiFi Access Point Credentials
const char *ssid = "Farm_Monitoring_AP";
const char *password = "12345678"; // Change as needed

// Sensor Pins
#define DHTPIN 14       // DHT11 connected to GPIO 4
#define DHTTYPE DHT11
#define SOIL_SENSOR_PIN 32  // Soil moisture sensor (AO) connected to GPIO36
#define LED_PIN 2          // LED connected to GPIO2 (Built-in LED)

// Objects
DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// Function to Read Soil Moisture
String getSoilMoisture() {
    int value = analogRead(SOIL_SENSOR_PIN);
    int percentage = map(value, 1023, 0, 0, 100); // 0 = Wet, 100 = Dry

    if (percentage > 60) return "Moist - No Water Needed";
    else if (percentage > 30) return "Moderate - Consider Watering";
    else return "Dry - Water Needed";
}

// Function to Read Temperature & Humidity
float getTemperature() { return dht.readTemperature(); }
float getHumidity() { return dht.readHumidity(); }

// Function to Serve Web Page
void handleRoot() {
    float temperature = getTemperature();
    float humidity = getHumidity();
    String soilCondition = getSoilMoisture();

    // HTML Page with JavaScript Prompt for Location Input
    String page = "<!DOCTYPE html>"
              "<html><head><title>Farm Monitor</title>"
              "<style>"
              "body {"
              // "    background: linear-gradient(135deg, #42a5f5, #478ed1);"
              "    margin: 0; padding: 0;"
              "    display: flex; justify-content: center; align-items: flex-start;"
              "    min-height: 100vh;"
              "}"
              ".container {"
              "    width: 50%; max-width: 600px; min-width: 300px;"
              "    background: white; padding: 30px; border-radius: 15px;"
              "    box-shadow: 0px 8px 16px rgba(0, 0, 0, 0.2);"
              "    text-align: center; transition: 0.3s ease-in-out;"
              "    margin-top: 20px;"
              "}"
              "h1 { color: #2c3e50; font-size: 26px; font-weight: 600; }"
              "h3 { color: #34495e; font-size: 20px; font-weight: 400; margin: 15px 0; }"
              "span { font-weight: bold; color: #e74c3c; }"
              "@media (max-width: 768px) {"
              "    .container { width: 80%; margin-top: 20%; padding: 40px; }"
              "    h1 { font-size: 25px; }"
              "    h3 { font-size: 15px; margin: 20px 0; }"
              "    box-shadow: 0;"
              "}"
              "</style>"
              "</head><body>"

              "<div class='container'>"
              "    <h1> Farm Monitoring System </h1>"
              "    <h3> Soil Condition: <span id='soil'>" + soilCondition + "</span></h3>"
              "    <h3> Temperature: <span id='temp'>" + String(temperature) + " °C</span></h3>"
              "    <h3> Humidity: <span id='humidity'>" + String(humidity) + "%</span></h3>"
              "    <h3> Location: <span id='location'>Not Provided</span></h3>"
              "    <h3> Recommended Crops: <span id='crops'>N/A</span></h3>"
              "</div>"

              "<script>"
              "let userLocation = prompt('Enter your location (City or Country):');"
              "if(userLocation) {"
              "   document.getElementById('location').innerText = userLocation;"
              "   recommendCrops(userLocation);"
              "} else {"
              "   document.getElementById('location').innerText = 'Location Not Provided';"
              "}"
              
              "function recommendCrops(location) {"
              "   let crops = '';"
              "   if(location.toLowerCase().includes('india')) {"
              "       crops = 'Rice, Wheat, Sugarcane';"
              "   } else if(location.toLowerCase().includes('usa')) {"
              "       crops = 'Corn, Soybean, Cotton';"
              "   } else if(location.toLowerCase().includes('uk')) {"
              "       crops = 'Barley, Oats, Potatoes';"
              "   } else {"
              "       crops = 'General Crops: Maize, Beans, Vegetables';"
              "   }"
              "   document.getElementById('crops').innerText = crops;"
              "}"
              "</script>"

              "</body></html>";

    server.send(200, "text/html", page);
}

// void checkClientConnections() {
//     int numClients = WiFi.softAPgetStationNum(); // Get connected clients count
//     Serial.print("Connected Clients: ");
//     Serial.println(numClients);

//     if (numClients > 0) {
//         Serial.println("✅ Device Connected - Turning LED ON");
//         digitalWrite(LED_PIN, HIGH); // Turn LED ON
//     } else {
//         Serial.println("❌ No Device Connected - Turning LED OFF");
//         digitalWrite(LED_PIN, LOW); // Turn LED OFF
//     }
// }


void setup() {
    Serial.begin(115200);
    delay(2000); // Allow sensor to stabilize
    dht.begin();
    pinMode(SOIL_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    // Start WiFi Access Point
    WiFi.softAP(ssid, password);
    Serial.println("WiFi Access Point Started");
    Serial.println(WiFi.softAPIP()); // Print the AP IP address

    // Start Web Server
    server.on("/", handleRoot);
    server.begin();
    Serial.println("Web Server Started");
}

void loop() {
    server.handleClient();  // Handle web requests

    // Read Sensor Data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soilMoistureValue = analogRead(SOIL_SENSOR_PIN);

    // Print Data to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureValue);

    delay(2000); // Wait 2 seconds before reading again
}
