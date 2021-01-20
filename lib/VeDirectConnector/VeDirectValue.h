#include <Arduino.h>

class VeDirectValue 
{
public:
    VeDirectValue(String key, String value) {
        this->key = key;
        this->value = value;
    };
    String key;
    String value;
};