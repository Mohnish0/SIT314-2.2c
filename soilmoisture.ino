// Include the required libraries
#include <SPI.h>
#include <SD.h>

// Define pins for the data logger
const int chipSelect = 10;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the SD card and check for errors
  if (!SD.begin(chipSelect)) {
    Serial.println("Error initializing SD card.");
    while (1);
  }

  Serial.println("SD card initialized.");
}

void loop() {
  // Read the soil moisture sensor value
  int soilMoisture = analogRead(A0);

  // Print the moisture value to the Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // Create a file to log data on the SD card
  File dataFile = SD.open("moistureData.txt", FILE_WRITE);

  // Write the moisture value to the SD card
  if (dataFile) {
    dataFile.println(soilMoisture);
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }

}
