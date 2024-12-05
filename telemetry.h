#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "billboard.h"
#include <vector>

class Telemetry {
public:
    Telemetry(Billboard& billboard);
    void initializeSensors();
    void pollData();

private:
    Billboard& billboard;
    std::vector<uint8_t> lowPassFilter(const std::vector<uint8_t>& data);
    void postToBillboard(const std::vector<uint8_t>& data);
};

#endif // TELEMETRY_H
