#include "ahrs.h"
#include <cmath>
#include <iostream>

AHRS::AHRS(Billboard& billboard) : quaternion{1.0, 0.0, 0.0, 0.0}, gyroBias{0.0, 0.0, 0.0}, gyroData{0.0, 0.0, 0.0}, billboard(billboard) {
    billboard.subscribe(Billboard::MessageID::TELEMETRY, [this](const Billboard::Message& message) { this->gyroCallback(message); });
}

void AHRS::update() {
    // Apply Kalman filter
    kalmanFilter();

    // Integrate using RK4
    rk4Integrate(0.01); // Assuming a fixed time step for simplicity
}

std::array<double, 4> AHRS::getQuaternion() const {
    return quaternion;
}

void AHRS::kalmanFilter() {
    // Simple Kalman filter example
    // Update quaternion and gyroBias
    // Predict step
    std::array<double, 3> gyroCorrected = {gyroData[0] - gyroBias[0], gyroData[1] - gyroBias[1], gyroData[2] - gyroBias[2]};
    rk4Integrate(0.01);

    // Update step
    // Here we would normally use the accelerometer and magnetometer data to correct the orientation
    // For simplicity, this is left as a placeholder
}

void AHRS::rk4Integrate(double dt) {
    // Simple RK4 integration example
    // Update quaternion
    std::array<double, 4> k1, k2, k3, k4;
    // Placeholder for actual RK4 computation
    // Normally, you would compute the quaternion derivative based on gyro data
}

void AHRS::gyroCallback(const Billboard::Message& message) {
    if (message.data.size() >= 3) {
        gyroData[0] = static_cast<double>(message.data[0]);
        gyroData[1] = static_cast<double>(message.data[1]);
        gyroData[2] = static_cast<double>(message.data[2]);
        std::cout << "Gyro data updated: " << gyroData[0] << ", " << gyroData[1] << ", " << gyroData[2] << std::endl;
    }
}

std::array<double, 4> AHRS::toQuaternion(const std::array<double, 3>& euler) const {
    // Convert Euler angles to quaternion
    double cy = cos(euler[2] * 0.5);
    double sy = sin(euler[2] * 0.5);
    double cp = cos(euler[1] * 0.5);
    double sp = sin(euler[1] * 0.5);
    double cr = cos(euler[0] * 0.5);
    double sr = sin(euler[0] * 0.5);

    return {
        cr * cp * cy + sr * sp * sy,
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy
    };
}

std::array<double, 3> AHRS::toEuler(const std::array<double, 4>& quat) const {
    // Convert quaternion to Euler angles
    double sinr_cosp = 2 * (quat[0] * quat[1] + quat[2] * quat[3]);
    double cosr_cosp = 1 - 2 * (quat[1] * quat[1] + quat[2] * quat[2]);
    double roll = atan2(sinr_cosp, cosr_cosp);

    double sinp = 2 * (quat[0] * quat[2] - quat[3] * quat[1]);
    double pitch = fabs(sinp) >= 1 ? copysign(M_PI / 2, sinp) : asin(sinp);

    double siny_cosp = 2 * (quat[0] * quat[3] + quat[1] * quat[2]);
    double cosy_cosp = 1 - 2 * (quat[2] * quat[2] + quat[3] * quat[3]);
    double yaw = atan2(siny_cosp, cosy_cosp);

    return {roll, pitch, yaw};
}
