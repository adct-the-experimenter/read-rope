#include "readrope.h"



#include <cstdio>

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux" // HP-UX
#elif defined(_AIX)
    #define PLATFORM_NAME "aix" // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
#else
    #define PLATFORM_NAME NULL
#endif

// Return a name of platform, if determined, otherwise - an empty string
const char *get_platform_name() 
{
    return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}

//system refers to the state machine and functions performed by the read rope library. 



uint16_t LIMIT_ZERO = 0;
uint16_t LIMIT_ONE = 0;
uint16_t LIMIT_TWO = 0;
uint16_t LIMIT_THREE = 0;
uint16_t LIMIT_FOUR = 0;
uint16_t LIMIT_FIVE = 0;
uint16_t LIMIT_SIX = 0;
uint16_t LIMIT_SEVEN = 0;


enum class State : uint8_t {
							STATE_NULL=0, 
							STATE_CALIBRATION_START, 
							STATE_CALIBRATION_S0, 
							STATE_CALIBRATION_S1, 
							STATE_CALIBRATION_S2,
							STATE_READ
							};

//state machine of the system
State state_machine;

//serial device communicator
SimpleSerial* m_serial_dev_ptr;

bool systemInitialized = false;

void ReadRope::InitReadRopeSystem()
{
	state_machine = State::STATE_NULL;	
	
	m_serial_dev_ptr = nullptr;
	
	systemInitialized = true;
}

void ReadRope::CloseReadRopeSystem()
{
	state_machine = State::STATE_NULL;
	
	if(m_serial_dev_ptr)
	{
		delete m_serial_dev_ptr;
	}
	
	m_serial_dev_ptr = nullptr;
}

std::string ReadRope::GetSerialPortOfReadRopeDevice()
{
	std::string platform_str(get_platform_name());
	
	//std::cout << "Platform:" << platform_str << std::endl;
	
	std::string port = "Null";
	std::string temp_port;
	
	std::string interface_str = "";
	
	if(platform_str == "linux")
	{
		//get available serial ports 
		//for now just do expected serial port names /dev/ttyACMX X = 0-4 and /dev/ttyUSBX
		
		bool stopTrying = false;
		
		interface_str = "/dev/ttyACM";
		
		int count = 0;
		
		while(!stopTrying)
		{
			
			
			for(int i = 0; i < 4; i++)
			{
				//bool to indicate if should continue to testing if device is read rope
				bool continueToIdentification = false;
				
				//try connecting to serial port
				try
				{
					temp_port = interface_str + std::to_string(i);
					std::cout << "testing port " << temp_port << std::endl;
					
					SimpleSerial tempSerialDevice(temp_port,9600);
					continueToIdentification = true;
				}
				catch(boost::system::system_error& e)
				{
					std::cout<< "Error: " << e.what() << std::endl;
					continueToIdentification = false;
				}
				
				//if should test if device is read rope
				if(continueToIdentification)
				{
					std::cout << "sending ID to device on this port... \n"; 
					
					SimpleSerial tempSerialDevice(temp_port,9600);
					
					//send specific serial character sequence
					tempSerialDevice.writeString("%");
					
					std::cout << "Sent ID %.\n";
					
					std::string response = tempSerialDevice.readLine();
					std::cout << "response: " << response << std::endl;
					
					//read answer
					if(response == "Y")
					{
						std::cout << "Read rope is in port " << temp_port << std::endl;
						port = temp_port;
						//stop for loop
						break;
					}
					else
					{
						std::cout << "This is not a read rope device\n";
					}
				}
				
			}
			
			if(port != "Null"){stopTrying = true;}
			
			interface_str = "/dev/ttyUSB";
			count++;
			
			if(count == 2){stopTrying = true;}
			
		}
		
		
	}
	else if(platform_str == "windows")
	{
		//To be implemented
		//list available serial ports
	}
	
	return port;
}

ReadRope::Status ReadRope::InitSerialCommunication(std::string port,unsigned int baud_rate)
{
	if(!systemInitialized)
	{
		return ReadRope::Status::ERROR_SYS_NOT_INIT;
	}
	
	try
	{
		m_serial_dev_ptr = new SimpleSerial(port,baud_rate);
		std::cout << "Successfully established communication with serial device read rope. \n";
	}
	catch(boost::system::system_error& e)
	{
		std::cout<< "Error: " << e.what() << std::endl;
		delete m_serial_dev_ptr;
		m_serial_dev_ptr = nullptr;
		
		return ReadRope::Status::ERROR;
	}
	
	return ReadRope::Status::SUCCESS;
}


void ReadRope::CalibrateSectionZeroHighLimit()
{

  bool maxFound = false;
  int count = 0;
  
  while(!maxFound)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = ReadRope::GetADCValueOfReadRope();
    
    if(ADC_value > LIMIT_ONE && ADC_value > LIMIT_ZERO)
    {
		ReadRope::SetSectionZeroHighLimit(ADC_value);
		count++;
    }
    
    if(count == 20){maxFound = true;}
   
  }
  
}

void ReadRope::SetSectionZeroHighLimit(uint16_t& limit){LIMIT_ONE = limit;}

void ReadRope::CalibrateSectionOneHighLimit()
{
  bool maxFound = false;
  int count = 0;
  
  while(!maxFound)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = ReadRope::GetADCValueOfReadRope();
    
    if(ADC_value > LIMIT_TWO && ADC_value > LIMIT_ONE)
    {
		ReadRope::SetSectionOneHighLimit(ADC_value);
		count++;
    }
    
    if(count == 20){maxFound = true;}
  }

}

void ReadRope::SetSectionOneHighLimit(uint16_t& limit){LIMIT_TWO = limit;}

void ReadRope::CalibrateSectionTwoHighLimit()
{
  bool maxFound = false;
  int count = 0;
  
  while(!maxFound)
  {
	// Read the analog value from pin A0
	uint16_t ADC_value = ReadRope::GetADCValueOfReadRope();

	if(ADC_value > LIMIT_FOUR && ADC_value > LIMIT_TWO)
	{
		ReadRope::SetSectionTwoHighLimit(ADC_value);
		count++;
	}

	if(count == 20){maxFound = true;}
  }

  //Calculate remaining limits based on current limits set
  LIMIT_THREE = LIMIT_TWO + (LIMIT_ONE - LIMIT_ZERO);
  LIMIT_FIVE = LIMIT_FOUR + (LIMIT_ONE - LIMIT_ZERO);
  LIMIT_SIX = LIMIT_FOUR + (LIMIT_TWO - LIMIT_ZERO);
  LIMIT_SEVEN = LIMIT_FOUR + (LIMIT_TWO - LIMIT_ZERO) + (LIMIT_ONE - LIMIT_ZERO);
}

void ReadRope::SetSectionTwoHighLimit(uint16_t& limit){LIMIT_FOUR = limit;}


void ReadRope::SetSectionZeroOneComboMinLimit(uint16_t& limit){LIMIT_THREE = limit;}

void ReadRope::SetSectionZeroTwoComboMinLimit(uint16_t& limit){LIMIT_FIVE = limit;}

void ReadRope::SetSectionOneTwoComboMinLimit(uint16_t& limit){LIMIT_SIX = limit;}

void ReadRope::SetSectionOneTwoThreeComboMinLimit(uint16_t& limit){LIMIT_SEVEN = limit;}


uint16_t ReadRope::GetADCValueOfReadRope()
{
	//send command to send ADC value to serial
	m_serial_dev_ptr->writeString("$"); 
	
	//read number
	std::string serial_data = m_serial_dev_ptr->readLine(); 
	
	uint16_t adc_value = std::stoi(serial_data);
	
	return adc_value;
}

ReadRope::Bend ReadRope::GetBendLocationFromReadRopeDevice()
{
	//if calibrated
  if(LIMIT_ZERO != 0 || LIMIT_ONE != 0 || LIMIT_TWO != 0 || LIMIT_THREE != 0 || LIMIT_FOUR != 0 
  || LIMIT_FIVE != 0 || LIMIT_SIX != 0 || LIMIT_SEVEN != 0)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = GetADCValueOfReadRope();
    
    if(ADC_value >= LIMIT_ZERO && ADC_value < LIMIT_ONE)
    {
		//no bend
      return Bend::NO_BEND;
    }
    else if(ADC_value >= LIMIT_ONE && ADC_value < LIMIT_TWO)
    {
      //Bend in section 0
      return Bend::BEND_S0;
    }
    else if(ADC_value >= LIMIT_TWO && ADC_value < LIMIT_THREE)
    {
      //Bend in section 1
      return Bend::BEND_S1;
    }
    else if(ADC_value >= LIMIT_THREE && ADC_value < LIMIT_FOUR)
    {
      //Bend in section 0. Bend in section 1.
      return Bend::BEND_S0_S1;
    }
    else if(ADC_value >= LIMIT_FOUR && ADC_value < LIMIT_FIVE)
    {
      //Bend in section 2
      return Bend::BEND_S2;
    }
    else if(ADC_value >= LIMIT_FIVE && ADC_value < LIMIT_SIX)
    {
      //Bend in section 0. Bend in section 2.
      return Bend::BEND_S0_S2;
    }
    else if(ADC_value >= LIMIT_SIX && ADC_value < LIMIT_SEVEN)
    {
      //Bend in section 1. Bend in section 2.
      return Bend::BEND_S1_S2;
    }
    else if(ADC_value >= LIMIT_SEVEN)
    {
      //Bend in all 3 sections.
      return Bend::BEND_S0_S1_S2;
    }
  }
  
  std::cout << "\nPlease calibrate the device.\n";
  return Bend::ERROR_BEND_NO_CALIBRATION;
  
}


/*
 
 uint16_t LIMIT_ZERO = 0;
uint16_t LIMIT_ONE = 0;
uint16_t LIMIT_TWO = 0;
uint16_t LIMIT_THREE = 0;
uint16_t LIMIT_FOUR = 0;
uint16_t LIMIT_FIVE = 0;
uint16_t LIMIT_SIX = 0;
uint16_t LIMIT_SEVEN = 0;

#define STATE_NULL 0
#define STATE_CALIBRATION_START 1
#define STATE_CALIBRATION_S0 2
#define STATE_CALIBRATION_S1 3
#define STATE_CALIBRATION_S2 4
#define STATE_READ 5


 //function to run to determine which section is bent
void ReadBendValues()
{
  if(LIMIT_ZERO != 0 || LIMIT_ONE != 0 || LIMIT_TWO != 0 || LIMIT_THREE != 0 || LIMIT_FOUR != 0 
  || LIMIT_FIVE != 0 || LIMIT_SIX != 0 || LIMIT_SEVEN != 0)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = analogRead(A0);
    
    // print the value at serial monitor
    Serial.println(ADC_value);
  
    if(ADC_value >= LIMIT_ZERO && ADC_value < LIMIT_ONE)
    {
      Serial.println("\nNo bend.\n");
    }
    else if(ADC_value >= LIMIT_ONE && ADC_value < LIMIT_TWO)
    {
      Serial.println("\nBend in section 0.\n");
    }
    else if(ADC_value >= LIMIT_TWO && ADC_value < LIMIT_THREE)
    {
      Serial.println("\nBend in section 1.\n");
    }
    else if(ADC_value >= LIMIT_THREE && ADC_value < LIMIT_FOUR)
    {
      Serial.println("\nBend in section 0. Bend in section 1.\n");
    }
    else if(ADC_value >= LIMIT_FOUR && ADC_value < LIMIT_FIVE)
    {
      Serial.println("\nBend in section 2.\n");
    }
    else if(ADC_value >= LIMIT_FIVE && ADC_value < LIMIT_SIX)
    {
      Serial.println("\nBend in section 0. Bend in section 2.\n");
    }
    else if(ADC_value >= LIMIT_SIX && ADC_value < LIMIT_SEVEN)
    {
      Serial.println("\nBend in section 1.Bend in section 2.\n");
    }
    else if(ADC_value >= LIMIT_SEVEN)
    {
      Serial.println("\nBend in all 3 sections.\n");
    }
  }
  else
  {
    Serial.println("\nPlease calibrate the device.\n");
  }
  
}

//function to start calibration of read rope device.
void StartCalibration()
{
  
}

//function to calibrate section zero 
void CalibrateSectionZero()
{
  Serial.println("\nCalibrating section zero. Please bend section zero of the read rope as much as possible, then stop bending it.\n");

  bool maxFound = false;
  while(!maxFound)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = analogRead(A0);
    delay(100);
    
    if(ADC_value < LIMIT_ONE && ADC_value > LIMIT_ZERO)
    {
      maxFound = true;
    }
    else if(ADC_value == LIMIT_ONE)
    {
      LIMIT_ONE = 0;
    }
    else
    {
      LIMIT_ONE = ADC_value;
    }
  }
  
  Serial.println("\nFinished section 0 phase.\n");
  Serial.println(LIMIT_ONE);

  delay(2000);

  //go to next phase of calibration
  state_machine = STATE_CALIBRATION_S1;
}

void CalibrateSectionOne()
{
  Serial.println("\nCalibrating section one. Please bend section one of the read rope as much as possible, then stop bending it.\n");

  bool maxFound = false;
  while(!maxFound)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = analogRead(A0);
    delay(100);
    
    if(ADC_value < LIMIT_TWO && ADC_value > LIMIT_ONE)
    {
      maxFound = true;
    }
    else if(ADC_value == LIMIT_TWO)
    {
      LIMIT_TWO = 0;
    }
    else
    {
      LIMIT_TWO = ADC_value;
    }
  }
  
  Serial.println("\nFinished section 1 phase.\n");
  Serial.println(LIMIT_TWO);

  delay(2000);

  //go to next phase of calibration
  state_machine = STATE_CALIBRATION_S2;
}

void CalibrateSectionTwo()
{
  Serial.println("\nCalibrating section two. Please bend section two of the read rope as much as possible, then stop bending it.\n");

  bool maxFound = false;
  while(!maxFound)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = analogRead(A0);
    delay(100);
    
    if(ADC_value < LIMIT_FOUR && ADC_value > LIMIT_TWO)
    {
      maxFound = true;
    }
    else if(ADC_value == LIMIT_FOUR)
    {
      LIMIT_FOUR = 0;
    }
    else
    {
      LIMIT_FOUR = ADC_value;
    }
  }
  
  Serial.println("\nFinished section 2 phase.\n");
  Serial.println(LIMIT_FOUR);

  //Calculate remaining limits based on current limits set
  LIMIT_THREE = LIMIT_TWO + (LIMIT_ONE - LIMIT_ZERO);
  LIMIT_FIVE = LIMIT_FOUR + (LIMIT_ONE - LIMIT_ZERO);
  LIMIT_SIX = LIMIT_FOUR + (LIMIT_TWO - LIMIT_ZERO);
  LIMIT_SEVEN = LIMIT_FOUR + (LIMIT_TWO - LIMIT_ZERO) + (LIMIT_ONE - LIMIT_ZERO);

  instruction_displayed = false;
  Serial.println("\nFinished calibration!\n");
  //go to next phase of calibration
  state_machine = STATE_NULL;
}
*/
