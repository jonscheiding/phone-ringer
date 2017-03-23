## PWM (Pulse Width Modulation)

There are a lot of great explanations of this on the internet, so I'll keep it brief.  PWM essentially allows you to simulate a voltage between 0 and Vcc on one of your Photon/Arduino output pins by switching it on and off very quickly.  The duty cycle of this high-frequency square wave determines the resulting simulated voltage.

You can use this capability to generate a sine wave (or other waveform) on one of your output pins.  In order to do that, we'll pre-generate a list of points on the sine wave, at a defined interval.

Inside the (pwm-lookup-generator) folder is a utility to generate the lookup list.  To use it, go into that directory and edit `config.json` to set the following values appropriately:

 * `frequencyInHz` - The frequency of the wave you want to generate.
 * `amplitude` - The value at the peak of the wave.  This should be the max value that you can give to `analogWrite`; on the Photon it is 255.
 * `resolutionInMicroseconds` - Basically, the "precision" of the resulting wave.  Determines how many times you'll change the simulated voltage per wave cycle.

After editing the `config.json`, run the following:

    npm install
    npm run generate

The output will be some C code, defining the relevant constants, which you can paste into your firmware.  See the [code](phone-ringer.ino) for how this is used.