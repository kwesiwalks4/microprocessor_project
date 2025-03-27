

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin Definitions ---
#define MQ2_PIN     A0      // MQ-2 sensor analog pin
#define LED_PIN     7       // LED indicator pin
#define DHT_PIN     2       // DHT22 data pin
#define DHT_TYPE    DHT22   // DHT22 sensor

// --- OLED Display Configuration ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
// I2C address for many SSD1306 displays is 0x3C
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// --- DHT Sensor Object ---
DHT dht(DHT_PIN, DHT_TYPE);

// --- Gas Threshold for MQ-2 (simulated CO2/PM2.5) ---
int gasThreshold = 300;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  while (!Serial);

  // MQ-2 sensor pin
  pinMode(MQ2_PIN, INPUT);

  // LED indicator
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Turn LED ON to indicate power

  // Initialize DHT22
  dht.begin();

  // Initialize SSD1306 display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found. Check wiring!");
    while (1);
  }
  display.clearDisplay();
  display.display();

  // Show initial message on the display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");
  display.println("Initializing...");
  display.display();
  delay(2000);

  Serial.println("Setup complete. Monitoring started.");
}

void loop() {
  // --- 1) Read the MQ-2 sensor (placeholder for gas levels) ---
  int mq2Value = analogRead(MQ2_PIN);

  // --- 2) Read DHT22 sensor (humidity + temperature) ---
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if DHT22 reading failed
  bool dhtError = isnan(humidity) || isnan(temperature);

  // --- LED Behavior ---
  // If gas reading exceeds threshold, blink LED 3 times
  if (mq2Value > gasThreshold) {
    blinkLED(3, 200);
    Serial.println("High Gas Detected!");
  }
  // If DHT22 fails to read, blink LED 2 times
  else if (dhtError) {
    blinkLED(2, 300);
    Serial.println("DHT sensor error!");
  }
  else {
    // Normal operation: LED stays ON
    digitalWrite(LED_PIN, HIGH);
  }

  // --- 3) Update OLED display ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  // Title
  display.println("IoT Air Quality");

  // "CO2" reading (simulated via MQ-2)
  display.print("CO2: ");
  display.print(mq2Value);
  display.println(" ppm?"); // placeholder

  // "PM2.5" reading (simulated via MQ-2)
  display.print("PM2.5: ");
  display.print(mq2Value / 23.0, 1); // arbitrary scaling
  display.println(" ug/m3?");       // placeholder

  // Humidity
  display.print("Humidity: ");
  if (!dhtError) {
    display.print(humidity, 1);
    display.println(" %");
  } else {
    display.println("Err");
  }

  // Temperature
  display.print("Temp: ");
  if (!dhtError) {
    display.print(temperature, 1);
    display.println(" C");
  } else {
    display.println("Err");
  }

// Determine air quality message
String airQualityMsg;
if (mq2Value < 340) airQualityMsg = "Air: Normal";
else if (mq2Value < 400) airQualityMsg = "Air: Poor";
else if (mq2Value < 700) airQualityMsg = "Air: Bad";  // Shortened to fit better
else airQualityMsg = "Air: Toxic!";

display.setCursor(0, 50);  // <-- Adjusted Y-position
display.setTextSize(1);
display.println(airQualityMsg);
  

  display.display();

  // --- 4) Print to Serial Monitor for debugging ---
  Serial.print("MQ-2 Value: ");
  Serial.print(mq2Value);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  // Delay before next reading
  delay(2000);
}

// Helper function to blink the LED
void blinkLED(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(delayTime);
    digitalWrite(LED_PIN, HIGH);
    delay(delayTime);
  }
}
