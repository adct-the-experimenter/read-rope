#!/usr/bin/env python

import shutil #file reading and writing
import sys
import os #running 
import re #regular expressions

import matplotlib

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
	
	#write control section for doing analysis
	
	circuit_file.write(".control\n");
	circuit_file.write("unset askquit\n");
	circuit_file.write("op\n");
	circuit_file.write("print V(2)\n");

	circuit_file.write("echo output test > outresult.data  $ start new file\n");
	circuit_file.write("wrdata outresult V(2)\n");
	
	circuit_file.write("quit\n")
	circuit_file.write(".endc\n");
	
	#end the file
	circuit_file.write(".end");
	
	#close empty kicad file
	circuit_file.close();

def RunSimulation():
	
	command = 'ngspice -b ' + circuit_filename;
	os.system(command);


def ReadOutput(out_val):
	output_file = open('outresult', 'r');
	
	output_string = "";
	
	for line in output_file: 
		output_string = line;
				
	output_file.close();
	
	print("output string" + output_string);
	
	#split the string with regular expression
	#split string into numbers like 1.00e+2 or 1.00e-2
	result = re.split(r'(((\d|\d\.))+(e|E)(\+|\-)(\d+))',output_string);
	
	print("result: ");
	print(result[8]);
	
	out_val = float(result[8]);
	print(out_val);
	
	
	
# Main Program

output = 0;

#1. Python controller file sets up parameters and ngspice circuit file.
WriteCircuitFile();

#2. Execute spice simulation to get result.
RunSimulation();

#3. Read output from file and save it in python.
ReadOutput(output);


#4. Repeat steps 1-3 for every combination of parameters.


#5. Plot all results.

