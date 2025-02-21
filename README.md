<h1>Smart City</h1>
<br>
<p>This is the code for a Smart City which consists of a Farm Monitoring System designed especially for the conditions of Nepal, Smart Recycling System and many more.</p>
<br>
<h2>Dependencies</h2>
<p><b>Driver for Arduino Nano (CP340): </b><a href="https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all">Click Here</a></p>
<p><b>Driver for ESP32 (CP210x): </b><a href="https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers">Click Here</a></p>
<p><b>Arduino IDE: </b><a href="https://www.arduino.cc/en/software">Click Here</a></p>
<p><b>Inside the IDE:</b></p>
<ul>
  <li>"ESP32" in Board Manager</li>
  <li>"Arduino AVR Boards" in Board Manager</li>
  <li>"DHT Sensor Library" in Library Manager</li>
</ul>
<br>
<h2>Structure</h2>
<br>
<img src="forest.png"/>
<br>
<h2>Setup Steps:</h2>
<br>
<h3>Farm Monitoring System</h3>
<br>
<p>Materials Required:</p>
<ul>
  <li>ESP32 Microcontroller (For a LAN (Wifi) and Data Processing)</li>
  <li>DHT11 Temperature and Humidity Sensor</li>
  <li>PH Sensor (if available)</li>
  <li>FS-90 Soil Moisture Sensor</li>
  <li>Jumper Wires (All 3 Types atleast 15 each)</li>
  <li>Breadboard or Project Board (optional)</li>
  <li>DC 5V Power Supply or USB (According to the type of ESP32) connection to laptop</li>
</ul>
<br>
<p><b>Connections:</b></p>
<br>
<p><strong>Disclaimer:</strong> Make sure to checkout the ESP32 Pinout below before making the connections.</p>
<br>
<img src="https://lastminuteengineers.com/wp-content/uploads/iot/ESP32-Pinout.png" alt="ESP32 PINOUT"/>
<p><b>Note: </b>The image may differ from your ESP32 so check the text above the pin present in the ESP32.</p>
<br>
<ul>
  <li>DHT11 Temperature Sensor Data Pin &rarr; GPIO 14</li>
  <li>Soil Moisture Sensor Data Pin &rarr; GPIO 32</li>
  <li>Connect the following in Series:</li>
  <ul>
    <li>VCC of DHT 11</li>
    <li>VCC of Soil Moisture Sensor</li>
    <li></li>
  </ul>
</ul>

