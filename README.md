# Read Rope 

This is an open-source hardware project for a device that outputs a certain voltage depending on where the rope/wire is bent.

The preferred configuration is the closer the bend is to source voltage at the beginning, the closer the output voltage is to source voltage.

# How It Works:

A resistive flex sensor is in parallel with a limiter resistor.

The resistive flex sensor increases in resistance when bent.

The limiter resistor in parallel to the resistive flex sensor scales the increase in resistance.

There is a series chain of sections of a parallel combination of a resistive flex sensor and limiter resistor.
Different values for a limiter resistor in each section makes for several equivalent resistors in series with each other
that contribute different increases in output voltage when bent depending on the limiter resistor.

If individual limiter resistors resistance value in each section of the chain were set to make 
the limiter resistor dependent on the distance from the output node,

then, the increase in output voltage would depend on the distance of flex resistor from the output node
thus making output voltage depend on location of the bend of a flex resistor.

See the diagrams/schematics/figures/images for read rope in old_base directory.
The resistive flex sensor by Spectra Symbol replaces the switch.

read-rope-diagram-1-bend.png

read-rope-diagram-4-bends.png

proof-of-concept-wire-short-resistor.jpg

proof-of-concept-broken-connection-resistance-added.jpg

# Applications:
 - Control for disabled 
 - Virtual Reality/ Augmented Reality (e.g. track precise movement of finger bend, arm bend, leg bend)
 - Interactive control for video games
 - Interactive control for electronic musical insturments
 - Interactive control for training simulation

# Simulation

Have ngspice installed.

Run python script read-rope-flex-resistor-circuit-sim.py

    python read-rope-flex-resistor-circuit-sim.py

## Interpreting Output
  
  
## Circuit

VCC-Rtrack-Req-GND
 
Vout = VCC * (Req / (Rtrack + Req))
