#ifndef ACTIVE_CONTROLS_H
#define ACTIVE_CONTROLS_H

#include "billboard.h"

class ActiveControls {
public:
    void initialize();
    void subscribeToBillboard(Billboard& billboard);

private:
    void handleControlCommands(const Billboard::Message& message);
    void executeCommands(const std::vector<uint8_t>& commands);
};

#endif // ACTIVE_CONTROLS_H
