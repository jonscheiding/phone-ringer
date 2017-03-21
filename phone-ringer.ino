//
// A/C wave frequency in Hz and period in milliseconds
//
const float AC_FREQUENCY_HZ = 20;
const long AC_PERIOD_MS = static_cast<long>((1 / AC_FREQUENCY_HZ) * 1000);

//
// Pins to use for the A/C control voltage
//
const int AC_PIN_1 = D0;
const int AC_PIN_2 = D1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    pinMode(AC_PIN_1, OUTPUT);
    pinMode(AC_PIN_2, OUTPUT);
}

void loop() {
    //
    // Simple A/C square wave generation
    //
    digitalWrite(AC_PIN_1, LOW);
    digitalWrite(AC_PIN_2, HIGH);
    delay(AC_PERIOD_MS / 2);
    digitalWrite(AC_PIN_2, LOW);
    digitalWrite(AC_PIN_1, HIGH);
    delay(AC_PERIOD_MS / 2);
}