#include "system/observablevalue.h"

struct VeDirectMpptValues {
    ObservableValue<float> battery_voltage; // V, Volts
    ObservableValue<float> battery_current; // I, Amps
    ObservableValue<float> load_current; // IL, Amps
    ObservableValue<bool> load_output_state; // LOAD, on/off
    ObservableValue<float> panel_voltage; // VPV, Volts
    ObservableValue<float> panel_power; // PPW, Watts
    ObservableValue<bool> relay_state; // Relay, on/off
    ObservableValue<String> off_reason; // OR, enum
    ObservableValue<float> yield_total; // H19, wh
    ObservableValue<float> yield_today; // H20, wh
    ObservableValue<float> maximum_power_today; // H21, Watts
    ObservableValue<float> yield_yesterday; // H22, wh
    ObservableValue<float> maximum_power_yesterday; // H23, Watts
    ObservableValue<String> error_code; // ERR, String
    ObservableValue<String> state_of_operation; // CS, Enum
    ObservableValue<String> firmware_version; // FW, String
    ObservableValue<String> product_id; // PID, String
    ObservableValue<String> serial_number; // SER#, String
    ObservableValue<int> day_sequence_number; // HSDS, String
    ObservableValue<String> tracker_operation_mode; // MPPT, String
};