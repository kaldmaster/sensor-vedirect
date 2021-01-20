#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sensesp_app.h"`
#include "signalk/signalk_output.h"
#include "VeDirectConnector.h"

// #define SERIAL_DEBUG_DISABLED = true

// SensESP builds upon the ReactESP framework. Every ReactESP application
// defines an "app" object vs defining a "main()" method.
ReactESP app([]() {

// Some initialization boilerplate when in debug mode...
#ifndef SERIAL_DEBUG_DISABLED
    SetupSerialDebug(115200);
#endif

    // Create the global SensESPApp() object.
    sensesp_app = new SensESPApp();
    
    SoftwareSerial *serial = new SoftwareSerial(D7, D8);
    serial->begin(4800);

    VeDirectConnector *veDirectConnector = new VeDirectConnector(serial);

    VeDirectValueTransform *veDirectTransform = new VeDirectValueTransform();
    veDirectTransform->connect_from(veDirectConnector);

    veDirectTransform->mpptValues.panel_power
        .connect_to(new SKOutputNumber("electrical.solar.panelPower", ""));

    // Start the SensESP application running
    sensesp_app->enable();
});