#include <SD.h>
#include <Wire.h>

const int soilMoisturePin = A0;  // Analog pin for soil moisture sensor

// Set the name of the file where the data will be logged
const char* logFileName = "soil_moisture_log.csv";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize the data logger shield
  if (!SD.begin(10)) {
    Serial.println("SD Card initialization failed!");
    while (1);  // Stop here if SD card initialization fails
  }

  // Open the log file in append mode
  File dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    // If the file opened successfully, write the header
    dataFile.println("Timestamp,Soil Moisture");
    dataFile.close();
    Serial.println("Data logger initialized!");
  } else {
    // If the file failed to open, print an error message
    Serial.println("Error opening log file!");
  }
}

void loop() {
  // Read the soil moisture value from the sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Get the current timestamp
  unsigned long currentTime = millis();

  // Print the soil moisture value and timestamp to the serial monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  
  // Log the data to the SD card
  logData(currentTime, soilMoistureValue);

  // Delay for a while before taking the next reading
  delay(5000); // Change this value to set the reading interval (in milliseconds)
}

// Function to log data to the SD card
void logData(unsigned long timestamp, int soilMoistureValue) {
  File dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    // Print the data to the file in CSV format (comma-separated values)
    dataFile.print(timestamp);
    dataFile.print(",");
    dataFile.println(soilMoistureValue);
    dataFile.close();
  } else {
    // If the file failed to open, print an error message
    Serial.println("Error opening log file!");
  }
}
