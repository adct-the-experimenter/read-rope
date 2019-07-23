import numpy as np
import matplotlib.pyplot as plt

# Vsource - Rtrack - Req(distance-based) - GND


print("\nConfiguration 4, Volt divider Multiple Resistors(distance-based) in Series\n");

##bend at resistor 1, no bend at resistor 2

# volt divider
# ( Req / (R_eq + R_track) ) * Vsource = Vout

R_track = 3e6; #resistor connected to Vsource

#resistances to use
R1 = 3e6; #resistor at position 0
R2 = 2e6; #resistor at position 1
R3 = 1e6; #resistor at position 2
R4 = 760e3; #resistor at position 3

rope_length = 1; #meters length of rope

Vsource = 3; #source voltage being divided by voltage divider 
num_bends_possible = 4; # number of bends that will affect the voltage

rope_array =  np.linspace(0, rope_length, num_bends_possible);
#1 means that there is a bend.
#output_bend_array[x] = 1 means that there is a bend at x position in rope.

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
output_bend_array_7[1] = 1;
output_bend_array_7[2] = 0;
output_bend_array_7[3] = 0;

output_bend_array_8 = np.zeros(len(rope_array));
output_bend_array_8[0] = 1;
output_bend_array_8[1] = 1;
output_bend_array_8[2] = 0;
output_bend_array_8[3] = 1;

output_bend_array_9 = np.zeros(len(rope_array));
output_bend_array_9[0] = 1;
output_bend_array_9[1] = 1;
output_bend_array_9[2] = 1;
output_bend_array_9[3] = 0;

output_bend_array_10 = np.zeros(len(rope_array));
output_bend_array_10[0] = 1;
output_bend_array_10[1] = 1;
output_bend_array_10[2] = 1;
output_bend_array_10[3] = 1;

output_bend_array_11 = np.zeros(len(rope_array));
output_bend_array_11[0] = 0;
output_bend_array_11[1] = 0;
output_bend_array_11[2] = 0;
output_bend_array_11[3] = 0;

output_volt_array = np.zeros(num_bends_possible*num_bends_possible);

def CalcOutputVoltage(output_bend_array,rope_array):
	Req = 0;
	#fill output voltage
	for i in range(len(output_bend_array)):
		#if there is a bend
		if(output_bend_array[i] == 1):
			print("rope_array[i]:",rope_array[i]);
			
			if(rope_array[i] == 0):
				if(Req != 0):
					Req = Req + R1;
				else:
					Req = R1;	
			elif(rope_array[i] == (1 / 3)):
				if(Req != 0):
					Req = Req + R2;
				else:
					Req = R2;
			elif(rope_array[i] == (2 / 3)):
				if (Req != 0):
					Req = Req + R3;
				else:
					Req = R3;
			elif(rope_array[i] == (3 / 3)):
				if (Req != 0):
					Req = Req + R4;
				else:
					Req = R4;
					
	vout = (Req / (Req + R_track))*Vsource;
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

print("output voltage Config 1:",output_volt_array[0]);
print("output voltage Config 2:",output_volt_array[1]);
print("output voltage Config 3:",output_volt_array[2]);
print("output voltage Config 4:",output_volt_array[3]);
print("output voltage Config 5:",output_volt_array[4]);
print("output voltage Config 6:",output_volt_array[5]);
print("output voltage Config 7:",output_volt_array[6]);
print("output voltage Config 8:",output_volt_array[7]);
print("output voltage Config 9:",output_volt_array[8]);
print("output voltage Config 10:",output_volt_array[9]);
print("output voltage Config 11:",output_volt_array[10]);

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
