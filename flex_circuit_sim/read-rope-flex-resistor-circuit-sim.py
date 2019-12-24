#!/usr/bin/env python

import shutil


def WriteCircuitFile():
	#open empty kicad file
	circuit_file = open("./read-rope-circuit.cir",'w');
	
	
	circuit_file.write("Read Rope Circuit Simulation With Resistive Flexible Sensors\n");
	
	#close empty kicad file
	circuit_file.close();



#1. Python controller file sets up parameters and ngspice circuit file.
WriteCircuitFile();

#2. Pass parameters to ngspice.

#3. Execute spice simulation to get result.

#4. Save result of spice simulation.

#5. Repeat steps 2-4 until finished getting results for every combination of parameters.

#6. Plot all results.

