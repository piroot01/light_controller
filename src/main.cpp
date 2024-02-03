#include <Arduino.h>
#include "app.h"

App myApp;

void setup () {
    Serial.begin(9600);
    Wire.begin();
    myApp.setup();
}

void loop () {
    myApp.run();
    delay(100);
}
