#include <string>

#include "sensesp.h"
#include "system/valueconsumer.h"
#include "signalk/signalk_emitter.h"
#include "VeDirectValue.h"
#include "VeDirectMpptValues.h"

class VeDirectValueTransform : public ValueConsumer<VeDirectValue*>
{
public:
    VeDirectMpptValues mpptValues;

    VeDirectValueTransform() {
        valueHandlers["V"] = [this](VeDirectValue* new_value) { 
            mpptValues.battery_voltage.set(this->parseVoltage(new_value->value)); };
        valueHandlers["I"] = [this](VeDirectValue* new_value) { 
            mpptValues.battery_current.set(this->parseAmperes(new_value->value)); };
        valueHandlers["IL"] = [this](VeDirectValue* new_value) { 
            mpptValues.load_current.set(this->parseAmperes(new_value->value)); };
        valueHandlers["VPV"] = [this](VeDirectValue* new_value) { 
            mpptValues.panel_voltage.set(this->parseVoltage(new_value->value)); };
        valueHandlers["PPW"] = [this](VeDirectValue* new_value) { 
            mpptValues.panel_power.set(this->parseWatts(new_value->value)); };
        valueHandlers["Relay"] = [this](VeDirectValue* new_value) { 
            mpptValues.relay_state.set(this->parseOnOff(new_value->value)); };
        valueHandlers["OR"] = [this](VeDirectValue* new_value) { 
            mpptValues.off_reason.set(new_value->value); };
        valueHandlers["H19"] = [this](VeDirectValue* new_value) { 
            mpptValues.yield_total.set(this->parsewattHours(new_value->value)); };
        valueHandlers["H20"] = [this](VeDirectValue* new_value) { 
            mpptValues.yield_today.set(this->parsewattHours(new_value->value)); };
        valueHandlers["H21"] = [this](VeDirectValue* new_value) { 
            mpptValues.maximum_power_today.set(this->parseWatts(new_value->value)); };
        valueHandlers["H22"] = [this](VeDirectValue* new_value) { 
            mpptValues.yield_yesterday.set(this->parsewattHours(new_value->value)); };
        valueHandlers["H23"] = [this](VeDirectValue* new_value) { 
            mpptValues.maximum_power_yesterday.set(this->parseWatts(new_value->value)); };
        valueHandlers["ERR"] = [this](VeDirectValue* new_value) { 
            mpptValues.error_code.set(new_value->value); };
        valueHandlers["CS"] = [this](VeDirectValue* new_value) { 
            mpptValues.state_of_operation.set(new_value->value); };
        valueHandlers["FW"] = [this](VeDirectValue* new_value) { 
            mpptValues.firmware_version.set(new_value->value); };
        valueHandlers["PID"] = [this](VeDirectValue* new_value) { 
            mpptValues.product_id.set(new_value->value); };
        valueHandlers["SER#"] = [this](VeDirectValue* new_value) { 
            mpptValues.serial_number.set(new_value->value); };
        valueHandlers["HSDS"] = [this](VeDirectValue* new_value) { 
            mpptValues.day_sequence_number.set(this->parseDay(new_value->value)); };
        valueHandlers["MPPT"] = [this](VeDirectValue* new_value) { 
            mpptValues.tracker_operation_mode.set(new_value->value); };
    }

    void set_input(VeDirectValue* new_value, uint8_t input_channel = 0) override {
        this->handle_new_value(new_value);
    }

private:
    typedef void (VeDirectValueTransform::*handlerFunction)(VeDirectValue* value);
    std::map<String, std::function<void (VeDirectValue*)>> valueHandlers;

    void handle_new_value(VeDirectValue* new_value) {
        valueHandlers["V"](new_value);
    }

    /**
     * Utility functions
     */
    float parseVoltage(String mv) {
        return mv.toFloat() / 1000.F;
    }

    float parseAmperes(String ma) {
        return ma.toFloat() / 1000.F;
    }

    float parseWatts(String w) {
        return w.toFloat();
    }

    float parsewattHours(String kwh) {
        return kwh.toFloat() * 1000.F;
    }

    int parseDay(String d) {
        return d.toInt();
    }

    bool parseOnOff(String onoff) {
        if (onoff.equalsIgnoreCase("ON"))
            return true;
        else
            return false;    
    }
};