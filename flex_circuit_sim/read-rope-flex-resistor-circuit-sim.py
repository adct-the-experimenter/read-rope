#!/usr/bin/env python

import shutil #file reading and writing
import sys
import os #running ngspice from command line
import re #regular expressions

import matplotlib.pyplot as plt


###########
# Circuit #
###########

#	VCC
#	RTrack
#			Output Node
#	Req at output, load
#	GND




#filename of file that contains ngspice circuit
circuit_filename = "./read-rope-circuit.cir";

#list containing resistance values to be used for limiter resistors in each section
#index indicates section, 0th index = first section
#set manually by person
resistor_limiter_val_list = []

#list of equivalent resistances at output for different combinations of bends
#set by program automatically
equivalent_resistances_list = [];

#list of output voltages for different combinations of bends
#set by program automatically
output_volt_list = [];

#Values for resistive flex sensor, no bend and full bend
flex_resistor_no_bend = 25e3; #25k ohms

flex_resistor_full_bend = 100e3; #100k ohms


#value for track resistor that comes is between the power source and output 
track_resistor = 20e3;

#value for voltage source for powering the circuit
vcc = 5;

def WriteCircuitFile(output_EQR):
	#open empty kicad file
	circuit_file = open(circuit_filename,'w');
	
	
	circuit_file.write("Read Rope Circuit Simulation With Resistive Flexible Sensors\n");
	
	#add resistor before output
	circuit_file.write("r1 1 2 " + str(track_resistor) + "\n");
	
	#add parallel resistor flex section combo after output node, node 2
	circuit_file.write("rOutEQ 2 0 " + str(output_EQR) + "\n");
	
	#add 5 volt independent voltage source
	circuit_file.write("vcc 1 0 DC " +  str(vcc) + "\n");
	
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
	
	command = 'ngspice ' + circuit_filename;
	os.system(command);


def ReadOutput():
	output_file = open('outresult', 'r');
	
	output_string = "";
	
	for line in output_file: 
		output_string = line;
				
	output_file.close();
	
	#print("output string" + output_string);
	
	#split the string with regular expression
	#split string into numbers like 1.00e+2 or 1.00e-2
	result = re.split(r'(((\d|\d\.))+(e|E)(\+|\-)(\d+))',output_string);
	
	#print("result: ");
	print(result[8]);
	
	output = float(result[8]);
	#print(output);
	out_val = output;
	return out_val;
	
def SimulateReadRopeWithFlexSections(num_sections):
	
	#set up combinations of bends
	#since 0 is no bend and 1 means bend, using binary number to represent combinations
	#example, for 2 flex sections, combinations are 00,01,10,11 = 4 combinations = 2^2
	
	num_combinations = 2**num_sections;
	
	#assuming flex resistor has 25k ohms when flat, 100k ohms when bent at 90 degrees
	
	#set up equivalent resistances list based on combinations of bends
	#and limiter resistors in each section
	for i in range(num_combinations):
		
		resistance = 0;
		
		#print("combination " + str(i));
		
		for j in range(num_sections):
			
			flex_resistor = 0;
			
			#if there is not a bend
			if( ((i & (1<<j)) >> j) == 0):
				#print("no bend. 0");
				flex_resistor = flex_resistor_no_bend;
			#else if there is a bend
			else:
				#print("bend. 1");
				flex_resistor = flex_resistor_full_bend;
			
			#print("limiter resistor in section " + str(j) +  ": " + str(resistor_limiter_val_list[j]));	
			resistance = resistance + ( ( (resistor_limiter_val_list[j]**-1) + (flex_resistor)**(-1) )**(-1) );
		
		equivalent_resistances_list.append(int(round(resistance)));
	
	#for each equivalent resistance at output in list generated
	for R in equivalent_resistances_list:
		
		#write the ngspice circuit file that includes the resistance,
		WriteCircuitFile(R);
		
		#run the simulation
		RunSimulation();
		
		
		#read the output
		out = ReadOutput();
		
		#store the output in the list of output voltages
		output_volt_list.append(out);
		
		
	
# Main Program

#set vcc, votage source powering circuit to 5 V
vcc = 5;

#set track resistor to be 56k
track_resistor = 56e3;

#Set up the equivalent resistor at output, also known as load

num_sections = 3;
#set the values for limiter resistors
#limiter resistors are the resistors that are in parallel with a flex resistor
#These are used as scale factors to determine how big the change in resistance is from a bend in a section
#Ideally the limiter resistors increase in value along the rope to make distinct identifiable changes for different bends.

#Required: number of limiter resistors = number of sections
resistor_limiter_val_list = [10e3,24e3,56e3];

#Good combos:
# 4 sections, [10e3,24e3,56e3,120e3], rtrack = 56e3
# 3 sections, [10e3,24e3,56e3], rtrack = 56e3

#simulate the read rope combos
#input of number of sections
SimulateReadRopeWithFlexSections(num_sections);

print("\nEquivalent Resistances list.\n");

print(equivalent_resistances_list);

print("\nOutput Voltages list. \n");

print(output_volt_list);

# Plot all results.

#plot combination to equivalent resistance
combo_bend_list = list(range(0,2**num_sections,1));

print(combo_bend_list);

plot1 = plt.figure(1);

plt.scatter( combo_bend_list , equivalent_resistances_list);
plt.xlabel('Combination Bend. Read as binary. 1 = 01 = no bend at section 1, bend at section 0');
plt.ylabel('Equivalent Resistance at Output (ohms)');
plot1.show();


plot2 = plt.figure(2);

#plot output voltage to equivalent resistance
plt.scatter(equivalent_resistances_list , output_volt_list);
plt.xlabel('Equivalent Resistance at Output (ohms)');
plt.ylabel('Output Voltage (V)');
plot2.show();

plot3 = plt.figure(3);

#plot output voltage to combination
plt.scatter( combo_bend_list , output_volt_list);
plt.xlabel('Combination Bend. Read as binary. 1 = 01 = no bend at section 1, bend at section 0');
plt.ylabel('Output Voltage (V)');
plot3.show();


plt.show();
