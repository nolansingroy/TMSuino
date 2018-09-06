
# Rationale - You don't need to read this. 
# This is only for people who want to know all the details.

### Coils

The six coils are *intentionally over-sized*. For four reasons:

1. To avoid soldering a decent wire thickness is needed, so a normal jumper wire clip can be used to connect the coils and the Arduino.

2. Each field should be applied perpendicular to the skull. Therefore hair has to be *flattened* - a heavy coil has just this effect.

3. A large coil diameter also supports the perpendicular constraint.

4. A large coil diameter spreads the magnetic field, which is more comfortable.

If you can achieve these constraints in any other way  (e.g. bald applicant and no problems with soldering), 
you can even use a 0.1mm enameled copper wire and wind it into a coil yourself - effectively reducing costs by another $10.
The magnetic field strength is of course much smaller than the one the coils are specified for - the Arduino cannot drive such strong currents.
How strong the field actually is has to be carefully measured with appropriate equipment. This is still an open issue.

### Arduino

The Arduino has been used since it is a simple platform already widely used by hobbyists. 
Essentially any microcontroller able to provide 500mA at 5V on at least 6 digital outputs could be used. 
The Arduinos' analog pins have originally been introduced as a solderless and breadbord-less way to connect 6 coils to ground. 
The testing routine was introduced later on, as wear and tear could loosen the jumper connections.

If you are able to solder lasting connections you can just connect all coils to ground instead of the analog pins. 
This would allow you to use an even smaller microcontroller board (e.g. ATtiny85 based like the Digispark Mini) - reducing costs by another $10. 
You would have to remove the testing routine from the source code, of course.

### Short jumper cables

Soldering is a dramatic hurdle - for normal people. So jumper wires are a must.

Typical jumper wires included in Arduino kits and available at hobbyist stores are too short to keep the Arduino off the head.
As it turns out that is not much of a hurdle. If the USB cable is too heavy, a direct 9V DC power adapter typically comes with lighter cabling.

### Cloth tape

High quality tapes provide a decent look and feel and allow a perfectly custom-sized cap for everyone.
A tape is much cleaner to apply than glue. Many people already have it, while others will find it useful to have it.
On the paper cut-out it is relatively easy to make connections of the desired length. 

### Paper pattern

It is needed to make the taping viable (we don't want to stick everything to the table). It also makes it very clear what is intended and just makes things easier.
Since the coils are put on top of the paper the intended orientation of each coil is always visible, preventing unnoticed fold downs. 
Of course, you could use a laser cutter and/or some other material than paper - which would allow you to use less tape or no tape at all. 
The SVG files created by [pattern-maker3](https://github.com/TMSuino/pattern-maker3) can be used as a starting point for laser cutter files.

### USB power / battery

The Arduinos' double power source options are great for this. 
Many people have USB power adapters from smartphones or other devices. These can be re-used. 
And if you need to go camping a 9V battery should be able to run the device for a few hours - should be enough for a few days in the wild.

### Wishlist

There are a few things I would like to change.

* Connecting the coils is currently a big opportunity for mistakes. 
  I believe it is too easy to confuse outer- and inner wire ends, and have problems with plugging the jumpers deep enough.
  Keeping the jumpers on the coil wire ends by huge amounts of tape is not optimal as well.

A solution would be to equip each coil with a LED. I envision a tiny PCB with two pins, a resistor and a LED which is soldered onto the coil holder by its manufacturer.
Due to the LED, it would be unlikely to confuse the wire order. People could see activation of the coils.


[Main Page](../README.md)
