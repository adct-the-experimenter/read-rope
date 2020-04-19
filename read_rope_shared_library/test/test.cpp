#include "readrope.h"


int main(int argc, char** argv)
{
	/*
	   ************************************************************
					Initialize read rope system
	   *************************************************************
	*/
	
	//initialize read rope system
	ReadRope::InitReadRopeSystem();
	
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
	double calibrationPhaseTime = 7.0;
	
	std::cout << "\nUsing default library calibration methods to calibrate the device...\n";
	
	//Calibrate section zero
	std::cout << "Calibrating section 0. Please bend only section zero as much as you can within " \
				<< calibrationPhaseTime << " seconds.\n";
				
	ReadRope::CalibrateSectionZeroMaxLimit(calibrationPhaseTime);
	
	//Calibrate section 1
	std::cout << "Calibrating section 1. Please bend only section one as much as you can within " \
				<< calibrationPhaseTime << " seconds.\n";
				
	ReadRope::CalibrateSectionOneMaxLimit(calibrationPhaseTime);
	
	//Calibrate section 2
	std::cout << "Calibrating section 2. Please bend only section two as much as you can within " \
				<< calibrationPhaseTime << " seconds.\n";
				
	ReadRope::CalibrateSectionTwoMaxLimit(calibrationPhaseTime);
	
	/*
	  ************************************************************ 
	  Get Bend location
	 ************************************************************
	*/
	bool quit = false;
	while(!quit)
	{
		switch( ReadRope::GetBendLocationFromReadRopeDevice() )
		{
			case ReadRope::Bend::ERROR_BEND_NO_CALIBRATION:
			{
				std::cout << "Error bend without calibration\n";
				break;
			}
			case ReadRope::Bend::NO_BEND:
			{
				std::cout << "No bend detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S0:
			{
				std::cout << "Bend in section 0 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S1:
			{
				std::cout << "Bend in section 1 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S0_S1:
			{
				std::cout << "Bend in section 0 and section 1 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			}
			case ReadRope::Bend::BEND_S2:
			{
				std::cout << "Bend in section 2 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S0_S2:
			{
				std::cout << "Bend in section 0 and section 2 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S1_S2:
			{
				std::cout << "Bend in section 1 and section 2 detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			} 
			case ReadRope::Bend::BEND_S0_S1_S2:
			{
				std::cout << "Bend in all 3 sections detected." << "ADC value:" << ReadRope::GetADCValueOfReadRope() << std::endl;
				break;
			}
		}
		
	}
	
	
	/*
	 ************************************************************
					Close read rope system
	 ************************************************************* 
	*/
	ReadRope::CloseReadRopeSystem();
	
	return 0;
}
