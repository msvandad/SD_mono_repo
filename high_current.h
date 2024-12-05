#ifndef HIGH_CURRENT_H
#define HIGH_CURRENT_H

#include "billboard.h"

class HighCurrent {
public:
    void initialize();
    void subscribeToBillboard(Billboard& billboard);

private:
    void handleAhrsData(const Billboard::Message& message);
    bool isApogeeDetected(double altitude);
    void triggerGPIO(int pin);
};

#endif // HIGH_CURRENT_H
