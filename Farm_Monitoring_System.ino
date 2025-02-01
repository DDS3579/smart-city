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
              "    <h3> For Kitchen Garden: <span id='garden'>N/A</span></h3>"
              "</div>"

              "<script>"
              "let userLocation = prompt('Enter your location (Name of the Town or City):');"
              "if(userLocation) {"
              "   document.getElementById('location').innerText = userLocation;"
              "   recommendCrops(userLocation);"
              "   recommendGarden(userLocation);"
              "} else {"
              "   document.getElementById('location').innerText = 'Location Not Provided';"
              "}"

              "function recommendGarden(location){"
              "   let garden = '';" 
              "if (location.toLowerCase().includes('kathmandu') || location.toLowerCase().includes('lalitpur') || location.toLowerCase().includes('bhaktapur')) {"
              "    garden = 'Tomato, Spinach, Carrot, Apple, Cabbage';"
              "} else if (location.toLowerCase().includes('pokhara')) {"
              "    garden = 'Cucumber, Radish, Cauliflower, Orange, Beans';"
              "} else if (location.toLowerCase().includes('biratnagar')) {"
              "    garden = 'Pumpkin, Bitter Gourd, Guava, Onion, Lettuce';"
              "} else if (location.toLowerCase().includes('birgunj')) {"
              "    garden = 'Brinjal, Garlic, Lemon, Coriander, Peas';"
              "} else if (location.toLowerCase().includes('bharatpur') || location.toLowerCase().includes('chitwan')) {"
              "    garden = 'Chili, Papaya, Carrot, Cauliflower, Beans';"
              "} else if (location.toLowerCase().includes('hetauda')) {"
              "    garden = 'Cabbage, Mango, Tomato, Coriander, Garlic';"
              "} else if (location.toLowerCase().includes('janakpur')) {"
              "    garden = 'Potato, Cucumber, Banana, Spinach, Onion';"
              "} else if (location.toLowerCase().includes('itahari')) {"
              "    garden = 'Lemon, Peas, Bitter Gourd, Tomato, Radish';"
              "} else if (location.toLowerCase().includes('dharan')) {"
              "    garden = 'Chili, Guava, Onion, Coriander, Pumpkin';"
              "} else if (location.toLowerCase().includes('dhangadhi')) {"
              "    garden = 'Tomato, Beans, Carrot, Papaya, Lettuce';"
              "} else if (location.toLowerCase().includes('nepalgunj')) {"
              "    garden = 'Spinach, Mango, Cucumber, Garlic, Radish';"
              "} else if (location.toLowerCase().includes('tulsipur')) {"
              "    garden = 'Brinjal, Peas, Lemon, Chili, Onion';"
              "} else if (location.toLowerCase().includes('ghorahi')) {"
              "    garden = 'Cabbage, Mango, Tomato, Coriander, Garlic';"
              "} else if (location.toLowerCase().includes('butwal')) {"
              "    garden = 'Carrot, Banana, Cucumber, Spinach, Onion';"
              "} else if (location.toLowerCase().includes('siddharthanagar')) {"
              "    garden = 'Tomato, Guava, Peas, Bitter Gourd, Radish';"
              "} else if (location.toLowerCase().includes('bhadrapur')) {"
              "    garden = 'Lemon, Papaya, Cauliflower, Coriander, Beans';"
              "} else if (location.toLowerCase().includes('damak')) {"
              "    garden = 'Chili, Banana, Tomato, Cabbage, Peas';"
              "} else if (location.toLowerCase().includes('rajbiraj')) {"
              "    garden = 'Cucumber, Guava, Garlic, Lettuce, Radish';"
              "} else {"
              "    garden = 'General Garden: Tomato, Spinach, Carrot, Mango, Coriander';"
              "}"
              "   document.getElementById('garden').innerText = garden;"
              "}"

              
              "function recommendCrops(location) {"
              "   let crops = '';"
              "if (location.toLowerCase().includes('kathmandu') || location.toLowerCase().includes('lalitpur') || location.toLowerCase().includes('bhaktapur')) {"
              "    crops = 'Rice, Maize, Wheat, Barley, Millet, Potato, Vegetables, Lentils, Mustard, Fruits';"
              "} else if (location.toLowerCase().includes('pokhara')) {"
              "    crops = 'Rice, Maize, Wheat, Millet, Barley, Potato, Coffee, Vegetables, Ginger, Fruits';"
              "} else if (location.toLowerCase().includes('biratnagar')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Jute, Mustard, Lentils, Potato, Vegetables, Fruits';"
              "} else if (location.toLowerCase().includes('birgunj')) {"
              "    crops = 'Sugarcane, Rice, Maize, Wheat, Pulses, Mustard, Vegetables, Jute, Lentils, Potato';"
              "} else if (location.toLowerCase().includes('bharatpur') || location.toLowerCase().includes('chitwan')) {"
              "    crops = 'Rice, Maize, Wheat, Mustard, Vegetables, Potato, Lentils, Barley, Fruits, Sugarcane';"
              "} else if (location.toLowerCase().includes('hetauda')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Mustard, Vegetables, Potato, Barley, Lentils, Fruits';"
              "} else if (location.toLowerCase().includes('janakpur')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Lentils, Mustard, Vegetables, Potato, Barley, Jute';"
              "} else if (location.toLowerCase().includes('itahari')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Jute, Mustard, Potato, Vegetables, Lentils, Barley';"
              "} else if (location.toLowerCase().includes('dharan')) {"
              "    crops = 'Rice, Maize, Wheat, Vegetables, Mustard, Potato, Lentils, Barley, Ginger, Fruits';"
              "} else if (location.toLowerCase().includes('dhangadhi')) {"
              "    crops = 'Rice, Maize, Wheat, Mustard, Sugarcane, Jute, Potato, Vegetables, Lentils, Barley';"
              "} else if (location.toLowerCase().includes('nepalgunj')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Lentils, Mustard, Potato, Vegetables, Jute, Barley';"
              "} else if (location.toLowerCase().includes('tulsipur')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Mustard, Lentils, Potato, Vegetables, Ginger, Fruits';"
              "} else if (location.toLowerCase().includes('ghorahi')) {"
              "    crops = 'Rice, Maize, Wheat, Mustard, Lentils, Potato, Vegetables, Fruits, Barley, Ginger';"
              "} else if (location.toLowerCase().includes('butwal')) {"
              "    crops = 'Rice, Maize, Wheat, Mustard, Vegetables, Potato, Lentils, Sugarcane, Barley, Fruits';"
              "} else if (location.toLowerCase().includes('siddharthanagar')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Lentils, Mustard, Vegetables, Potato, Fruits, Jute';"
              "} else if (location.toLowerCase().includes('bhadrapur')) {"
              "    crops = 'Tea, Rice, Maize, Wheat, Sugarcane, Mustard, Potato, Vegetables, Lentils, Jute';"
              "} else if (location.toLowerCase().includes('damak')) {"
              "    crops = 'Rice, Maize, Wheat, Tea, Sugarcane, Potato, Mustard, Vegetables, Lentils, Fruits';"
              "} else if (location.toLowerCase().includes('rajbiraj')) {"
              "    crops = 'Rice, Maize, Wheat, Sugarcane, Jute, Mustard, Lentils, Potato, Vegetables, Barley';"
              "} else {"
              "    crops = 'General Crops: Maize, Beans, Vegetables';"
              "}"
              "   document.getElementById('crops').innerText = crops;"
              "}"
              "</script>"

              "</body></html>";

    server.send(200, "text/html", page);
}

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
