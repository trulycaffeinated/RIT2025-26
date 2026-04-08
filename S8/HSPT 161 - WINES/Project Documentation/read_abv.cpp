// Include Libraries
#include "Arduino.h"
#include "DS18B20.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Encoder.h"
#include "Button.h"
#include "HX711.h"


// Pin Definitions
#define DS18B20WP_PIN_DQ  4
#define OLED128X64_PIN_RST 9
#define OLED128X64_PIN_DC  8
#define OLED128X64_PIN_CS  7
#define ROTARYENCI_PIN_CLK 2
#define ROTARYENCI_PIN_D   3
#define ROTARYENCI_PIN_S1  10
#define SCALE_PIN_DAT      6
#define SCALE_PIN_CLK      5

// Global variables and defines
long rotaryEncIOldPosition = 0;

// object initialization
DS18B20 ds18b20wp(DS18B20WP_PIN_DQ);
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);
Encoder rotaryEncI(ROTARYENCI_PIN_D, ROTARYENCI_PIN_CLK);
Button rotaryEncIButton(ROTARYENCI_PIN_S1);
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);

// Calibration value from HX711 setup
#define calibration_factor 2280

// Project settings
const float assumed_bottle_volume_mL = 750.0;
const float beta = 0.00030;          // g/mL per °C
const unsigned long readIntervalMs = 750;
unsigned long lastRead = 0;

// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

enum BottleType
{
    BOTTLE_STANDARD = 0,
    BOTTLE_SPARKLING = 1,
    BOTTLE_HEAVY = 2
};

struct BottlePreset
{
    const char* name;
    float tareMass_g;
};

BottlePreset bottlePresets[] =
{
    {"Standard", 450.0},
    {"Sparkling", 850.0},
    {"Heavy",     650.0}
};

const int bottlePresetCount = sizeof(bottlePresets) / sizeof(bottlePresets[0]);
int selectedBottleIndex = 0;

void updateBottleSelection()
{
    long rotaryEncINewPosition = rotaryEncI.read() / 4; // tame sensitivity a bit

    if (rotaryEncINewPosition != rotaryEncIOldPosition)
    {
        if (rotaryEncINewPosition > rotaryEncIOldPosition)
            selectedBottleIndex++;
        else
            selectedBottleIndex--;

        if (selectedBottleIndex < 0)
            selectedBottleIndex = bottlePresetCount - 1;
        if (selectedBottleIndex >= bottlePresetCount)
            selectedBottleIndex = 0;

        rotaryEncIOldPosition = rotaryEncINewPosition;
    }

    // button press resets selection to Standard
    if (rotaryEncIButton.onPress())
    {
        selectedBottleIndex = 0;
        rotaryEncI.write(0);
        rotaryEncIOldPosition = 0;
    }
}

float compensateDensityTo20C(float densityMeasured, float tempC)
{
    // If temp > 20 C, measured density tends to be lower, so correct upward
    return densityMeasured + beta * (tempC - 20.0);
}

float convert_density_to_abv(float densityMeasured, float tempC)
{
    float rho20 = compensateDensityTo20C(densityMeasured, tempC);
    float d = 0.99820 - rho20;

    float abv = 19399.7 * d * d + 642.6 * d - 0.050;

    // if below 0, then just say 0. Most likely an error based on sugar content
    if (abv < 0.0) abv = 0.0;
    // for wines 20% is basically upper-end practical limit
    if (abv > 20.0) abv = 20.0;

    return abv;
}

void drawMainDisplay(const char* bottleName, float totalMass, float liquidMass, float tempC, float density, float abv)
{
    oLed128x64.clearDisplay();
    oLed128x64.setTextColor(WHITE);

    // Title / bottle type
    oLed128x64.setTextSize(1);
    oLed128x64.setCursor(0, 0);
    oLed128x64.print("Bottle: ");
    oLed128x64.println(bottleName);

    // ABV big
    oLed128x64.setTextSize(2);
    oLed128x64.setCursor(0, 16);
    oLed128x64.print("ABV ");
    oLed128x64.print(abv, 1);
    oLed128x64.print("%");

    // Small details
    oLed128x64.setTextSize(1);
    oLed128x64.setCursor(0, 42);
    oLed128x64.print("T:");
    oLed128x64.print(tempC, 1);
    oLed128x64.print("C D:");
    oLed128x64.print(density, 3);

    oLed128x64.setCursor(0, 54);
    oLed128x64.print("M:");
    oLed128x64.print(totalMass, 0);
    oLed128x64.print(" L:");
    oLed128x64.print(liquidMass, 0);

    oLed128x64.display();
}

void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();

    rotaryEncIButton.init();
    pinMode(ROTARYENCI_PIN_S1, INPUT_PULLUP);

    scale.set_scale(calibration_factor);
    scale.tare(); // Assuming no weight on the scale, reset the scale to 0

    // initialize encoder position
    rotaryEncI.write(0);
    rotaryEncIOldPosition = 0;

    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 0);
    oLed128x64.println("Wine ABV Estimator");
    oLed128x64.println("Preset Bottle Mode");
    oLed128x64.display();
    delay(1500);

    Serial.println("Bottle-based ABV estimator starting...");
    Serial.println("Assumes full 750 mL bottle.");
    Serial.println("Rotate encoder to choose bottle type.");
}

// Main logic of  circuit. It defines the interaction between the components selected. 
// After setup, it runs over and over again, in an eternal loop.
void loop()
{
    updateBottleSelection();

    if (millis() - lastRead >= readIntervalMs)
    {
        lastRead = millis();

        const char* bottleName = bottlePresets[selectedBottleIndex].name;
        float presetBottleMass_g = bottlePresets[selectedBottleIndex].tareMass_g;

        float ds18b20wpTempC = ds18b20wp.readTempC();
        if (ds18b20wpTempC == DEVICE_DISCONNECTED_C)
        {
            ds18b20wpTempC = 20.0; // safe fallback
        }

        float totalBottleMass_g = scale.get_units(10);

        if (totalBottleMass_g < 0)
        {
            totalBottleMass_g = 0;
        }

        float liquidMass_g = totalBottleMass_g - presetBottleMass_g;

        if (liquidMass_g < 0)
        {
            liquidMass_g = 0;
        }

        float density_g_per_mL = liquidMass_g / assumed_bottle_volume_mL;
        float abv = convert_density_to_abv(density_g_per_mL, ds18b20wpTempC);

        Serial.print("Bottle: ");
        Serial.print(bottleName);
        Serial.print(" | Temp C: ");
        Serial.print(ds18b20wpTempC, 2);
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

        drawMainDisplay(bottleName, totalBottleMass_g, liquidMass_g, ds18b20wpTempC, density_g_per_mL, abv);
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties
*    stated above and in the GNU General Public License version 3 (or any
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this
*    program subject to the following warranty disclaimers and by using
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE.
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN.
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN,
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF
*    THE ABOVE.
********************************************************/