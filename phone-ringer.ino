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

//
// Sine wave lookup table and step interval in microseconds
//
const short PWM_STEPS[] = {
    0,   3,   6,   10,  13,  16,  19,  22,  26,  29,  32,  35,  38,  42,  45,  48,  51,  54,  57,  61,  64,  67,  70,  73,  76,  
    79,  82,  85,  88,  91,  94,  97,  100, 103, 106, 109, 112, 115, 118, 121, 123, 126, 129, 132, 134, 137, 140, 143, 145, 148, 
    150, 153, 156, 158, 161, 163, 166, 168, 170, 173, 175, 178, 180, 182, 184, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 
    207, 209, 211, 213, 214, 216, 218, 220, 221, 223, 224, 226, 227, 229, 230, 232, 233, 234, 236, 237, 238, 239, 240, 241, 242, 
    243, 244, 245, 246, 247, 248, 249, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 256, 256, 256, 256, 
    256, 256, 256, 256, 256, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 249, 248, 247, 246, 245, 244, 
    243, 242, 241, 240, 239, 238, 237, 236, 234, 233, 232, 230, 229, 227, 226, 224, 223, 221, 220, 218, 216, 214, 213, 211, 209, 
    207, 205, 203, 201, 199, 197, 195, 193, 191, 189, 187, 184, 182, 180, 178, 175, 173, 170, 168, 166, 163, 161, 158, 156, 153, 
    150, 148, 145, 143, 140, 137, 134, 132, 129, 126, 123, 121, 118, 115, 112, 109, 106, 103, 100, 97,  94,  91,  88,  85,  82,  
    79,  76,  73,  70,  67,  64,  61,  57,  54,  51,  48,  45,  42,  38,  35,  32,  29,  26,  22,  19,  16,  13,  10,  6,   3,   
};
const int PWM_STEP_COUNT = sizeof(PWM_STEPS) / sizeof(PWM_STEPS[0]);
const int PWM_STEP_INTERVAL_US = ((AC_PERIOD_MS / 2) * 1000) / PWM_STEP_COUNT;

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
    doHalfWave(AC_PIN_2);
    digitalWrite(AC_PIN_2, LOW);
    doHalfWave(AC_PIN_1);
}

void doHalfWave(int pin) {
    for(int i = 0; i < PWM_STEP_COUNT; i++) {
        analogWrite(pin, PWM_STEPS[i]);
        delayMicroseconds(PWM_STEP_INTERVAL_US);
    }
}