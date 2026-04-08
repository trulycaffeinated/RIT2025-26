#include <HX711.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ======================================================
// Pin Definitions
// ======================================================
#define HX711_DT        3
#define HX711_SCK       2

#define ONE_WIRE_BUS    4      // DS18B20 data pin
#define ROTARY_PIN      A0     // analog bottle selector input

// OLED (I2C)
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

// ======================================================
// Objects
// ======================================================
HX711 scale;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ======================================================
// Calibration / Project Settings
// ======================================================
float calibration_factor = -7050.0;   // CHANGE after calibration
const float assumed_bottle_volume_mL = 750.0;
const float beta = 0.00030;           // g/mL per °C
unsigned long lastRead = 0;
const unsigned long readIntervalMs = 750;

// ======================================================
// Bottle Presets
// ======================================================
enum BottleType {
  BOTTLE_STANDARD = 0,
  BOTTLE_SPARKLING,
  BOTTLE_HEAVY,
  BOTTLE_UNKNOWN
};

struct BottlePreset {
  const char* name;
  float tareMass_g;
};

BottlePreset bottlePresets[] = {
  {"Standard", 450.0},
  {"Sparkling", 850.0},
  {"Heavy", 650.0},
  {"Unknown", 500.0}
};

// ======================================================
// Helper: read bottle type from analog rotary selector
// Assumes selector outputs different analog bands.
// Adjust thresholds for your actual hardware.
// ======================================================
BottleType readBottleType() {
  int val = analogRead(ROTARY_PIN);

  // Example ranges for 3-position selector / resistor ladder / pot zones
  if (val < 341) {
    return BOTTLE_STANDARD;
  } else if (val < 682) {
    return BOTTLE_SPARKLING;
  } else {
    return BOTTLE_HEAVY;
  }
}

// ======================================================
// Helper: compensate density to 20 °C
// ======================================================
float compensateDensityTo20C(float densityMeasured, float tempC) {
  return densityMeasured + beta * (tempC - 20.0);
}

// ======================================================
// Helper: convert density to estimated ABV
// Empirical approximation
// ======================================================
float convert_density_to_abv(float densityMeasured, float tempC) {
  float rho20 = compensateDensityTo20C(densityMeasured, tempC);
  float d = 0.99820 - rho20;

  float abv = 19399.7 * d * d + 642.6 * d - 0.050;

  if (abv < 0.0) abv = 0.0;
  if (abv > 20.0) abv = 20.0;

  return abv;
}

// ======================================================
// Helper: draw OLED screen
// ======================================================
void drawDisplay(const char* bottleName, float totalMass, float liquidMass,
                 float tempC, float density, float abv) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Bottle: ");
  display.print(bottleName);

  // ABV big
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print("ABV ");
  display.print(abv, 1);
  display.print("%");

  // Small details
  display.setTextSize(1);
  display.setCursor(0, 42);
  display.print("T:");
  display.print(tempC, 1);
  display.print("C  D:");
  display.print(density, 3);

  display.setCursor(0, 54);
  display.print("M:");
  display.print(totalMass, 0);
  display.print("g L:");
  display.print(liquidMass, 0);
  display.print("g");

  display.display();
}

// ======================================================
// Setup
// ======================================================
void setup() {
  Serial.begin(9600);

  scale.begin(HX711_DT, HX711_SCK);
  scale.set_scale(calibration_factor);
  scale.tare();   // Tare with empty platform only (NO bottle)

  tempSensor.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Wine ABV Estimator");
  display.println("Preset Bottle Mode");
  display.display();
  delay(1500);

  Serial.println("Bottle-based ABV estimator starting...");
  Serial.println("Assumes full 750 mL bottle.");
  Serial.println("Place full bottle on platform.");
}

// ======================================================
// Main Loop
// ======================================================
void loop() {
  if (millis() - lastRead >= readIntervalMs) {
    lastRead = millis();

    // --------------------------
    // Read bottle preset
    // --------------------------
    BottleType selectedType = readBottleType();
    const char* bottleName = bottlePresets[selectedType].name;
    float presetBottleMass_g = bottlePresets[selectedType].tareMass_g;

    // --------------------------
    // Read temperature
    // --------------------------
    tempSensor.requestTemperatures();
    float tempC = tempSensor.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C) {
      tempC = 20.0; // safe fallback
    }

    // --------------------------
    // Read total bottle mass
    // --------------------------
    float totalBottleMass_g = scale.get_units(10);

    if (totalBottleMass_g < 0) {
      totalBottleMass_g = 0;
    }

    // --------------------------
    // Estimate liquid mass
    // --------------------------
    float liquidMass_g = totalBottleMass_g - presetBottleMass_g;

    if (liquidMass_g < 0) {
      liquidMass_g = 0;
    }

    // --------------------------
    // Compute density
    // --------------------------
    float density_g_per_mL = liquidMass_g / assumed_bottle_volume_mL;

    // --------------------------
    // Compute ABV
    // --------------------------
    float abv = convert_density_to_abv(density_g_per_mL, tempC);

    // --------------------------
    // Serial debug output
    // --------------------------
    Serial.print("Bottle: ");
    Serial.print(bottleName);
    Serial.print(" | Temp C: ");
    Serial.print(tempC, 2);
    Serial.print(" | Total Mass g: ");
    Serial.print(totalBottleMass_g, 2);
    Serial.print(" | Preset Bottle g: ");
    Serial.print(presetBottleMass_g, 2);
    Serial.print(" | Liquid Mass g: ");
    Serial.print(liquidMass_g, 2);
    Serial.print(" | Density g/mL: ");
    Serial.print(density_g_per_mL, 4);
    Serial.print(" | ABV %: ");
    Serial.println(abv, 2);

    // --------------------------
    // OLED output
    // --------------------------
    drawDisplay(bottleName, totalBottleMass_g, liquidMass_g, tempC, density_g_per_mL, abv);
  }
}