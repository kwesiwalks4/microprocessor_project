Air Quality Monitoring System (Wokwi Simulation)

Overview  
This Wokwi-based air quality monitoring system simulates an MQ-2 gas sensor and a DHT22 temperature/humidity sensor to measure environmental conditions, displaying them on a virtual OLED screen. The system provides visual alerts through a simulated LED and outputs data to the Serial Monitor for debugging.

Features  
- Real-time air quality monitoring using an MQ-2 sensor (simulated CO₂ and PM2.5 values)  
- Temperature and humidity measurement via a simulated DHT22 sensor  
- OLED display (128×64) showing all sensor readings  
- Visual LED alerts for high gas levels or sensor errors  
- Serial output for debugging and data logging  

Virtual Components (Wokwi)  

Component | Purpose  
-----------|---------  
Arduino Uno (Wokwi) | Main controller  
MQ-2 Gas Sensor (Simulated) | Air quality detection  
DHT22 Sensor (Simulated) | Temperature/humidity measurement  
SSD1306 OLED Display (Simulated) | Visual output  
LED (D7, Simulated) | Status indicator  

Setup (Wokwi)  

1. Open the Wokwi Simulator and create a new project  
2. Add the following components:  
   - Arduino Uno  
   - MQ-2 Gas Sensor (Simulated) → Connect to A0  
   - DHT22 Sensor (Simulated) → Connect to D2  
   - OLED Display (SSD1306, Simulated) → I2C (SDA: A4, SCL: A5)  
   - LED (Simulated) → Connect to D7  
3. Install required libraries:  
   - Adafruit_GFX  
   - Adafruit_SSD1306  
   - DHT sensor library  
4. Upload the code in Wokwi and start the simulation  

Usage  
After starting the simulation:  
1. The system initializes with a 2-second startup screen  
2. Continuous monitoring begins with 2-second intervals  
3. The OLED displays:  
   - Simulated CO₂ levels  
   - Simulated PM2.5 levels  
   - Temperature  
   - Humidity  
   - Air quality status  

Air Quality Thresholds  

Sensor Value | Status  
--------------|--------  
< 340 | Normal  
340-399 | Poor  
400-699 | Bad  
≥ 700 | Toxic  

LED Alerts  

- 3 quick blinks: High gas detected  
- 2 slow blinks: DHT22 sensor error  
- Steady on: Normal operation  

Limitations  

1. Simulated values may not reflect real-world air quality conditions  
2. OLED display constraints: Limited space for long messages  
3. DHT22 stability: In real applications, requires stable wiring  

Future Improvements  

- Integrate additional sensors (simulated MH-Z19 for CO₂, PMS5003 for PM2.5)  
- Implement data logging to a virtual SD card or cloud storage  
- Add a simulated buzzer for audible alerts  
- Explore remote monitoring via a simulated IoT dashboard  

License  
This project is open-source under the MIT License.
