# Read Rope 

This is an open-source hardware project for a device that outputs a certain voltage depending on where the rope/wire is bent.

The preferred configuration is the closer the bend is to source voltage at the beginning, the closer the output voltage is to source voltage.

# How It Works:

There is a loose connection of a wire segment in parallel with a resistor which shorts the resistor. 
If there is a bend in the wire, then the wire segment shorting the resistor is broken which makes the 
resistor part of the circuit and in series with another resistor connected to voltage source.
The resistor connected to ground is called Rtrack.

Multiple other resistors are connected in parallel to a wire segment whoose connection is broken with a bend.
The sum of these resistors is referred to as Req.
In the read-rope-configs-series.py simulation, Req is added in series. This is the best configuration because it gives voltage values very different and far from each other.
In the read-rope-configs-parallel.py simulation, Req is added in parallel. This is the not a good configuration because it gives voltage values very similar and close to each other.

The resistor is always connected to the wire and the wire segment shorting the resistor is what is switched.
Think of the wire segment as being connected to a SPST switch that is normally closed. 
The physical bend is like opening the connection of the switch with a press.
	   
	  
# Applications:
 - Control for disabled 
 - Virtual Reality/ Augmented Reality (e.g. track precise movement of finger bend, arm bend, leg bend)
 - Interactive control for video games
 - Interactive control for electronic musical insturments
 - Interactive control for training simulation

# Simulation

python read-rope-configs-series.py

Choose option 4 for the preferred configuration of read rope.

If there is a bend at x position, then the resistor for that position will be added to Req
and the output voltage is equal to the ratio of Req over sum of Req and Rtrack multiplied by the source voltage VCC.
For example, bend at 0th position connects 200 ohm resistor to circuit making Req=200 before Rtrack; 
Req in series with Rtrack gives an output voltage Vout = VCC*(Req / (Req + Rtrack))= VCC*(200 / (200+200)) = 0.5*VCC

Interpreting output.
Look at the console output for output voltages for each configuration and look at the graphs to see where the bend is happening
for each configuration.

Circuit:

VCC
 |
Rtrack
 |
Req
 |
GND
 
Vout = VCC * (Req / (Rtrack + Req))
