#!/usr/bin/env python

import shutil
import sys
import os

circuit_filename = "./read-rope-circuit.cir";

def WriteCircuitFile():
	#open empty kicad file
	circuit_file = open(circuit_filename,'w');
	
	
	circuit_file.write("Read Rope Circuit Simulation With Resistive Flexible Sensors\n");
	
	#add resistor before output
	circuit_file.write("r1 1 2 20k \n");
	
	#add parameter for flex resistor section 1
	valBend1 = int(10000);
	circuit_file.write(".param valBend1 = " + str(valBend1) + "\n");
	
	#add parallel resistor combo after output
	circuit_file.write("r2_limit 2 0 10k \n");
	circuit_file.write("r2_flex 2 0 10k \n");
	
	#add 5 volt independent voltage source
	circuit_file.write("vcc 1 0 DC 5 \n");
	
	#tell ngspice to save voltage at output
	circuit_file.write(".save v(2) \n");
	
	#specify the analysis to be done
	circuit_file.write(".op\n");
	
	
	
	#end the file
	circuit_file.write(".end");
	
	#close empty kicad file
	circuit_file.close();

def RunSimulation():
	
	command = 'ngspice -b ' + circuit_filename;
	os.system(command);

#1. Python controller file sets up parameters and ngspice circuit file.
WriteCircuitFile();

#2. Pass parameters to ngspice.

#3. Execute spice simulation to get result.
RunSimulation();

#4. Save result of spice simulation.

#5. Repeat steps 2-4 until finished getting results for every combination of parameters.

#6. Plot all results.

