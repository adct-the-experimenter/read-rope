import numpy as np
import matplotlib.pyplot as plt

#ask user for integer to input into factorial computation
int_config_input = int(input("Enter the configuration to view: "));

###################################################################################
#########################Configuration 1 ##########################################
###################################################################################

# Vsource - Req - Rtrack - GND

if(int_config_input == 1):
	print("\nConfiguration 1, Volt divider Multiple Resistors in Parallel, Same R\n");

	# volt divider
	# ( R_track / (R_eq + R_track) ) * Vsource = Vout

	R_track = 200; #200 ohms

	R = 200; #200 ohms

	Vsource = 3; #source voltage being divided by voltage divider 

	num_resistor_combo = 20; #number of bends, resistors connected, 0 counts as a bend

	#array of output voltage over resistors
	output_volt_array = np.zeros(num_resistor_combo,float);

	#fill array for wealth over the years
	for n in range(len(output_volt_array)):
		if(n == 0):
			output_volt_array[n] = 0;
		else:
			output_volt_array[n] = (R_track / ( ( (n / R)**(-1)) + R_track))*Vsource;

	#array of resistances
	resistor_array = np.zeros(num_resistor_combo,float);

	#fill array of resistors
	for n in range(len(resistor_array)):
		if(n == 0):
			resistor_array[n]=0;
		else:
			resistor_array[n]=(n / R)**(-1);


	print(output_volt_array);

	#array of bends
	bends_array = np.linspace(0, num_resistor_combo-1, num_resistor_combo);
	print("bends array");
	print(bends_array);

	#Make plot from array of output voltage and array of bends
	plt.plot(bends_array,output_volt_array);
	plt.title('Configuration 1(Parallel R to vsource, Same, volt divider): Output voltage vs number of bends');
	plt.xlabel("Bends, # of Resistors connected, decreasing resistance with increasing # of bends");
	plt.ylabel("Output Voltage (V)");
	plt.xlim(0,num_resistor_combo)  # decreasing resistance, increasing # of bends
	plt.xticks(bends_array);
	plt.show();


###################################################################################
#########################Configuration 2 ##########################################
###################################################################################

# Vsource - Rtrack - Req - GND

if(int_config_input == 2):
	print("\nConfiguration 2, Volt divider Multiple Resistors in Parallel, Same R\n");

	# volt divider
	# ( Req / (R_eq + R_track) ) * Vsource = Vout

	R_track = 200; #200 ohms

	R = 200; #200 ohms

	Vsource = 3; #source voltage being divided by voltage divider 

	num_resistor_combo = 20; #number of bends, resistors connected, 0 counts as a bend

	#array of output voltage over resistors
	output_volt_array = np.zeros(num_resistor_combo,float);

	#fill array for wealth over the years
	for n in range(len(output_volt_array)):
		if(n == 0):
			output_volt_array[n] = 0;
		else:
			output_volt_array[n] = (( (n / R)**(-1) ) / ( ( (n / R)**(-1)) + R_track))*Vsource;

	#array of resistances
	resistor_array = np.zeros(num_resistor_combo,float);

	#fill array of resistors
	for n in range(len(resistor_array)):
		if(n == 0):
			resistor_array[n]=0;
		else:
			resistor_array[n]=(n / R)**(-1);


	print(output_volt_array);

	#array of bends
	bends_array = np.linspace(0, num_resistor_combo-1, num_resistor_combo);
	print("bends array");
	print(bends_array);

	#Make plot from array of output voltage and array of bends
	plt.plot(bends_array,output_volt_array);
	plt.title('Configuration 2(Parallel R to GND, Same, volt divider): Output voltage vs number of bends');
	plt.xlabel("Bends, # of Resistors connected, decreasing resistance with increasing # of bends");
	plt.ylabel("Output Voltage (V)");
	plt.xlim(0,num_resistor_combo)  # decreasing resistance, increasing # of bends
	plt.xticks(bends_array);
	plt.show();

###################################################################################
#########################Configuration 3 ##########################################
###################################################################################

# Vsource - Rtrack - Req(distance-based) - GND

if(int_config_input == 3):
	print("\nConfiguration 3, Volt divider Multiple Resistors(distance-based) in Parallel, Same R\n");
	
	##bend at resistor 1, no bend at resistor 2
	
	# volt divider
	# ( Req / (R_eq + R_track) ) * Vsource = Vout

	R_track = 200; #200 ohms

	R1 = 200; #200 ohms
	R2 = 400; #10 ohms
	
	rope_length = 1; #meters length of rope
	
	Vsource = 3; #source voltage being divided by voltage divider 
	num_bends_possible = 4; # number of bends that will affect the voltage
	
	rope_array =  np.linspace(0, rope_length, num_bends_possible);
	
	output_bend_array_1 = np.zeros(len(rope_array));
	output_bend_array_1[0] = 1;
	output_bend_array_1[1] = 0;
	output_bend_array_1[2] = 0;
	output_bend_array_1[3] = 0;
	
	output_bend_array_2 = np.zeros(len(rope_array));
	output_bend_array_2[0] = 0;
	output_bend_array_2[1] = 1;
	output_bend_array_2[2] = 0;
	output_bend_array_2[3] = 0;
	
	output_bend_array_3 = np.zeros(len(rope_array));
	output_bend_array_3[0] = 0;
	output_bend_array_3[1] = 0;
	output_bend_array_3[2] = 1;
	output_bend_array_3[3] = 0;
	
	output_bend_array_4 = np.zeros(len(rope_array));
	output_bend_array_4[0] = 0;
	output_bend_array_4[1] = 0;
	output_bend_array_4[2] = 0;
	output_bend_array_4[3] = 1;
	
	output_bend_array_5 = np.zeros(len(rope_array));
	output_bend_array_5[0] = 1;
	output_bend_array_5[1] = 0;
	output_bend_array_5[2] = 0;
	output_bend_array_5[3] = 1;
	
	output_bend_array_6 = np.zeros(len(rope_array));
	output_bend_array_6[0] = 1;
	output_bend_array_6[1] = 0;
	output_bend_array_6[2] = 1;
	output_bend_array_6[3] = 0;
	
	output_bend_array_7 = np.zeros(len(rope_array));
	output_bend_array_7[0] = 1;
	output_bend_array_7[1] = 0;
	output_bend_array_7[2] = 1;
	output_bend_array_7[3] = 1;
	
	output_bend_array_8 = np.zeros(len(rope_array));
	output_bend_array_8[0] = 1;
	output_bend_array_8[1] = 1;
	output_bend_array_8[2] = 0;
	output_bend_array_8[3] = 0;
	
	output_bend_array_9 = np.zeros(len(rope_array));
	output_bend_array_9[0] = 1;
	output_bend_array_9[1] = 1;
	output_bend_array_9[2] = 0;
	output_bend_array_9[3] = 1;
	
	output_bend_array_10 = np.zeros(len(rope_array));
	output_bend_array_10[0] = 1;
	output_bend_array_10[1] = 1;
	output_bend_array_10[2] = 1;
	output_bend_array_10[3] = 0;
	
	output_bend_array_11 = np.zeros(len(rope_array));
	output_bend_array_11[0] = 1;
	output_bend_array_11[1] = 1;
	output_bend_array_11[2] = 1;
	output_bend_array_11[3] = 1;
	
	output_volt_array = np.zeros(num_bends_possible*num_bends_possible);
	
	def CalcOutputVoltage(output_bend_array,rope_array):
		Req = 0;
		#fill output voltage
		for i in range(len(output_bend_array)):
			#if there is a bend
			if(output_bend_array[i] == 1):
				print("rope_array[i]:",rope_array[i]);
				
				if(rope_array[i] == 0):
					Req = (1 / R1 )**-1;	
				elif(rope_array[i] == (1 / 3)):
					if(Req != 0):
						Req = ( (1 / Req) + (1 / R1) )**-1;
					else:
						Req = ((1 / R1))**-1
				elif(rope_array[i] == (2 / 3)):
					if (Req != 0):
						Req = ( (1 / Req) + (1 / R2) )**-1;
					else:
						Req = (1 / R2)**-1;
				elif(rope_array[i] == (3 / 3)):
					if (Req != 0):
						Req = ( (1 / Req) + (1 / R2) )**-1;
					else:
						Req = (1 / R2)**-1;
						
		vout = (R_track / (Req + R_track))*Vsource;
		return vout;
		
	for n in range(num_bends_possible*num_bends_possible):
		if(n == 0):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_1,rope_array); 
		elif(n == 1):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_2,rope_array);
		elif(n == 2):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_3,rope_array);
		elif(n == 3):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_4,rope_array);
		elif(n == 4):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_5,rope_array);
		elif(n == 5):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_6,rope_array);
		elif(n == 6):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_7,rope_array);
		elif(n == 7):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_8,rope_array);
		elif(n == 8):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_9,rope_array);
		elif(n == 9):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_10,rope_array);
		elif(n == 10):
			output_volt_array[n] = CalcOutputVoltage(output_bend_array_11,rope_array);
	
	print("output voltage array:",output_volt_array);
	
	#Make sub plot to show where there is a bend
	
	plt.subplot(451);
	plt.scatter(rope_array,output_bend_array_1);
	plt.title("Combination 1");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	
	plt.subplot(452);
	plt.scatter(rope_array,output_bend_array_2);
	plt.title("Combination 2");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(453);
	plt.scatter(rope_array,output_bend_array_3);
	plt.title("Combination 3");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(454);
	plt.scatter(rope_array,output_bend_array_4);
	plt.title("Combination 4");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(455);
	plt.scatter(rope_array,output_bend_array_5);
	plt.title("Combination 5");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(456);
	plt.scatter(rope_array,output_bend_array_6);
	plt.title("Combination 6");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(457);
	plt.scatter(rope_array,output_bend_array_7);
	plt.title("Combination 7");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(458);
	plt.scatter(rope_array,output_bend_array_8);
	plt.title("Combination 8");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(459);
	plt.scatter(rope_array,output_bend_array_9);
	plt.title("Combination 9");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.show();
	
	plt.subplot(541);
	plt.scatter(rope_array,output_bend_array_10);
	plt.title("Combination 10");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.subplot(542);
	plt.scatter(rope_array,output_bend_array_11);
	plt.title("Combination 11");
	plt.ylabel("Bend");
	plt.xlabel("Rope length (m)");
	plt.xlim(0,rope_length)  # decreasing resistance, increasing # of bends
	plt.xticks(rope_array);
	
	plt.show();
	
		
	#plot combination vs output voltage
	combo_array = np.linspace(1,num_bends_possible*num_bends_possible,num_bends_possible*num_bends_possible);


	plt.bar(combo_array,output_volt_array,width=0.1);
	plt.ylabel("Output Voltage (V)");
	plt.xlabel("Combination #");
	
	plt.show();
