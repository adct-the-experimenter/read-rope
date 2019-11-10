# Read Rope 

This is an open-source hardware project for a device that outputs a certain voltage depending on where the rope/wire is bent.

The preferred configuration is the closer the bend is to source voltage at the beginning, the closer the output voltage is to source voltage.

# How It Works:

There is a loose connection of a wire segment in parallel with a resistor which shorts the resistor. 
If there is a bend in the wire, then the wire segment shorting the resistor is broken which makes the 
resistor part of the circuit and in series with another resistor connected to voltage source.
The resistor connected to the voltage source is called Rtrack.

Multiple other resistors are connected in parallel to a wire segment whoose connection is broken with a bend.
The sum of these resistors is referred to as Req.

Having Req be a combination of resistors in series is the best configuration because it gives voltage values very different and far from each other.

Having Req in parallel is the not a good configuration because it gives voltage values very similar and close to each other.

The resistor is always connected to the wire and the wire segment shorting the resistor is what is switched.
Think of the wire segment as being connected to a SPST switch that is normally closed. 
The physical bend is like opening the connection of the switch with a press.

See the diagrams/schematics/figures/images for read rope. 

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

Run LTSpice and open the file ltspice-sim-with-load.asc.

Run the simulation of the circuit and click on wire at point where vout label is.

The Req resistor represents the combinations of resistors from output to circuit ground.

## Interpreting Output

To interpret output:

1. Choose a combination for Req from choices of 1k, 3k, 7k, 9k. 
  - Example: 1k and 3k

2. Sum the resistors of the combination chosen.
  - Example: 1k + 3k = 4k 

3. Look at the voltage output of vout at the value of the sum of the resistors of combination.
  - Example: Look at 4k( sum of combination 1k and 3K).
  
Circuit:

VCC-Rtrack-Req-GND
 
Vout = VCC * (Req / (Rtrack + Req))
