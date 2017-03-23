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

In our case, we're not directly using the PWM output to drive the phone - instead, we are using it to switch the outputs of the h-bridge.  As long as the h-bridge can respond quickly enough, this results in a PWM output from it, at the higher voltage.

### The RC filter

Although the transformer may help round it off somewhat, the "naked" PWM signal will probably not do a very good job of driving the phone due to the high-frequency square wave component. We can use an RC filter to turn this into a more "pure" sine wave.

An RC filter looks like this:

![RC filter diagram](https://static.tiendy.com/shops/opendaq/uploads/rc_schema.png)

The RC filter eliminates the higher-frequency portions of the signal, leaving (ideally) only the lower-frequency sine wave.  The values of R and C are determined by the formula

 ![](http://www.ekswai.com/wp-content/uploads/highlow.gif)
 
 where `f` is the cutoff frequency.  There are a lot of tradeoffs to be made here, which an electrical engineer would probably understand very well and explain in terms of complex impedance.  I will provide the following gross oversimplification:
 
  * A higher `f` means a "messier" signal, to which some phones will be more sensitive than others.
  * A higher `C` means your circuit will draw more current.
  * A higher `R` means a lower `Vout` and thus a bigger transformer needed.

You'll want to experiment in a simulator and in real life with different R and C values.  I got decent results using 100Ω and 470μF.
