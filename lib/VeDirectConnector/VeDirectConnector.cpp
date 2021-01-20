#include <math.h>
#include "sensesp.h"

#include "VeDirectConnector.h"

VeDirectConnector::VeDirectConnector(Stream* rx_stream, String config_path)
    : Sensor(config_path),
        rx_stream{rx_stream}
{
    frameHandler = new VeDirectFrameHandler();
}

void VeDirectConnector::enable()
{
    debugD("Enabling VeDirectConnector.");

    // enable reading the serial port    
    app.onAvailable(*rx_stream, [this]() {
        while (rx_stream->available())
        {
            frameHandler->rxData(rx_stream->read());
        }
    });

    app.onRepeat(5000, [this]() { this->publish_data(); });
}

void VeDirectConnector::publish_data() {
    debugD("publish_data: ");
    for ( int i = 0; i < frameHandler->veEnd; i++ ) {
        Serial.print(frameHandler->veName[i]);
        Serial.print("= ");
        Serial.println(frameHandler->veValue[i]);
        this->emit(new VeDirectValue(frameHandler->veName[i], frameHandler->veValue[i]));
    }
}