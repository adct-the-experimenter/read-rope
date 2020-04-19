#include "readrope.h"


int main(int argc, char** argv)
{
	/*
	 ************************************************************ 
	  Initialize  serial communication with the read rope device.
	 ************************************************************
	*/
	 
	std::string port = ReadRope::GetSerialPortOfReadRopeDevice();
	
	if(port != "Null")
	{
		std::cout << "Read rope device port is " << port << std::endl;
		
		if(ReadRope::InitSerialCommunication(port,9600) == ReadRope::Status::ERROR)
		{
			std::cout << "Failed to connect to port " << port << "at baud rate of 9600.\n";
		}
		else
		{	
			std::cout << "Successfully able to connect to read rope device on port " << port << std::endl;
			
		}
	}
	else
	{
		std::cout << "Failed to get port of read rope device! \n.";
	}
	
	/*
	 ************************************************************ 
	  Get ADC Value from read rope device
	 ************************************************************
	*/
	
	uint16_t readRopeADCValue = 0;
	
	readRopeADCValue = ReadRope::GetADCValueOfReadRope();
	
	std::cout << "ADC value from read rope: " << readRopeADCValue << std::endl;
	
	/*
	 ************************************************************ 
	  Calibration
	 ************************************************************
	*/
	
	//To Be Implemented soon
	
	return 0;
}
