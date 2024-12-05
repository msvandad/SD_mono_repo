#include "telemetry.h"
#include <iostream>
#include <numeric> // For std::accumulate

Telemetry::Telemetry(Billboard& billboard) : billboard(billboard) {}

void Telemetry::initializeSensors() {
    // Initialize IMUs, magnetometer, barometer, and GPS
    std::cout << "Sensors initialized." << std::endl;
}

void Telemetry::pollData() {
    // Simulate polling data from sensors
    std::vector<uint8_t> imuData = {0x10, 0x20, 0x30}; // Mock IMU data
    std::vector<uint8_t> magData = {0x40, 0x50, 0x60}; // Mock magnetometer data
    std::vector<uint8_t> baroData = {0x70, 0x80, 0x90}; // Mock barometer data
    std::vector<uint8_t> gpsData = {0xA0, 0xB0, 0xC0}; // Mock GPS data

    // Combine all sensor data
    std::vector<uint8_t> rawData;
    rawData.insert(rawData.end(), imuData.begin(), imuData.end());
    rawData.insert(rawData.end(), magData.begin(), magData.end());
    rawData.insert(rawData.end(), baroData.begin(), baroData.end());
    rawData.insert(rawData.end(), gpsData.begin(), gpsData.end());

    // Apply low-pass filter
    std::vector<uint8_t> filteredData = lowPassFilter(rawData);

    // Post to billboard
    postToBillboard(filteredData);
}

std::vector<uint8_t> Telemetry::lowPassFilter(const std::vector<uint8_t>& data) {
    // Apply a simple low-pass filter
    std::vector<uint8_t> filteredData;
    for (size_t i = 0; i < data.size(); ++i) {
        uint8_t filteredValue = (i > 0) ? (data[i] + data[i - 1]) / 2 : data[i];
        filteredData.push_back(filteredValue);
    }
    return filteredData;
}

void Telemetry::postToBillboard(const std::vector<uint8_t>& data) {
    // Post filtered data to the billboard
    billboard.publish(Billboard::MessageID::TELEMETRY, data);
}
