#ifndef AHRS_H
#define AHRS_H

#include <vector>
#include <array>
#include "billboard.h"

class AHRS {
public:
    AHRS(Billboard& billboard);
    void update();
    std::array<double, 4> getQuaternion() const;

private:
    std::array<double, 4> quaternion;
    std::array<double, 3> gyroBias;
    std::array<double, 3> gyroData;
    Billboard& billboard;

    void kalmanFilter();
    void rk4Integrate(double dt);
    std::array<double, 4> toQuaternion(const std::array<double, 3>& euler) const;
    std::array<double, 3> toEuler(const std::array<double, 4>& quat) const;
    void gyroCallback(const Billboard::Message& message);
};

#endif // AHRS_H
