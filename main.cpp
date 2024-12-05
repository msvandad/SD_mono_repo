#include "billboard.h"
#include "telemetry.h"
#include "ahrs.h"
#include "high_current.h"
#include "active_controls.h"
#include <iostream>

static void InitializeISRs() 
{ 
   // Initialize the interrupt service routines 
   // for the various peripherals 
   InitializeTelemetryPolling_ISR(); 
   InitializeHighCurrent_ISR(); 
   InitializeActiveControls_ISR(); 
} 

static void InitializeHAL() 
{ 
   // Initialize the hardware abstraction layer 
   // for the various peripherals 
   InitializeHALGPIO(); 
   InitializeHALI2C(); 
   InitializeHALUART(); 
   InitializeHALPWM(); 
} 

static void InitializeModules() 
{ 
   // Initialize the various modules 
   InitializeBillboard(); 
   InitializeAHRS(); 
   InitializeTelemetry(); 
   InitializeHighCurrent(); 
   InitializeActiveControls(); 
} 

void telemetryCallback(const Billboard::Message& message) {
    std::cout << "Telemetry message received with data size: " << message.data.size() << std::endl;
}

int main() 
{ 
   // Disable the global interrupts 
   DisableInterrupts(); 

   // Initialize the interrupt service routines 
   InitializeISRs(); 

   // Initialize the hardware abstraction layer 
   InitializeHAL(); 

   // Initialize the various modules 
   InitializeModules(); 

   // Enable the global interrupts 
   EnableInterrupts(); 

   // Test case for subscribing to and publishing telemetry messages
   Billboard billboard;
   billboard.subscribe(Billboard::MessageID::TELEMETRY, telemetryCallback);
   std::vector<uint8_t> data = {0x01, 0x02, 0x03};
   billboard.publish(Billboard::MessageID::TELEMETRY, data);

   // Main loop 
   while (1) 
   { 
      // Heartbeat LED 
      heartbeat(); 

      // Services billboard  
      ServiceBillboard(); 
   } 

   return 0;
} 
