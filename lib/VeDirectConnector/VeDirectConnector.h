#include "sensors/sensor.h"

#include "VeDirectValueTransform.h"
#include "VeDirectFrameHandler.h"

class VeDirectConnector : public Sensor, public ValueProducer<VeDirectValue*>
{
public:
    VeDirectConnector(Stream* rx_stream, String config_path = "");
    virtual void enable() override final;

private:
    Stream *rx_stream;
    VeDirectFrameHandler *frameHandler;

    void publish_data();
    void emit_data(String data);
};