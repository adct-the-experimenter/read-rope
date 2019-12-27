# Read Rope 

This is an open-source hardware project for a device that outputs a certain voltage depending on where the rope/wire is bent.

The preferred configuration is the closer the bend is to source voltage at the beginning, the closer the output voltage is to source voltage.

Resistive Flex Sensor used: https://www.adafruit.com/product/1070

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
 - Interactive control for electronic musical instruments
 - Interactive control for training simulation

# Simulation

Have ngspice installed.

Run python script read-rope-flex-resistor-circuit-sim.py

    python read-rope-flex-resistor-circuit-sim.py

## Interpreting Output
  
1. Look at the Equivalent Resistance at Output vs Combination graph.
2. Determine the combination of bends you want to see.
 - 0 = no bend, 1 = bend
 - combination 1 = 01 = no bend at section 1, bend at section 0
3. Look up the equivalent resistant value at output for the combination selected in the Equivalent Output Resistance vs Combination graph.
4. Look at the Output Voltage vs Equivalent Resistance at Output graph.
5. Look up the output voltage for equivalent resistance in Output Voltage vs Equivalent Resistance at Output graph.
  
## Interpreting bend combination from output voltage.

1. Look at the Output Voltage vs Equivalent Resistance at Output graph.
2. In Output Voltage vs Equivalent Resistance at Output graph, look up the equivalent resistance for output voltage read.
3. Look at the Equivalent Resistance at Output vs Combination graph.
4. In Equivalent Resistance at Output vs Combination graph, look up the combination number for the equivalent resistant value at output.
5. Determine the combination of bends from the combination number.
	- 0 = no bend, 1 = bend
	- combination 1 = 01 = no bend at section 1, bend at section 0
  
## Circuit

VCC-Rtrack-Req-GND
 
Vout = VCC * (Req / (Rtrack + Req))
