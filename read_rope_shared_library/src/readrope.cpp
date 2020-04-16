#include "readrope.h"


void StopReadingFromReadRope()
{
	state_machine = STATE_NULL;
}

void StartCalibrationProcess()
{
	state_machine = STATE_CALIBRATION_START;
}

void StartReadingFromReadRope()
{
	state_machine = STATE_READ;
}


void InitSerialCommunication(std::string port,unsigned int baud_rate)
{
	try
	{
		m_serial_dev_ptr = new SimpleSerial(port,baud_rate);
		std::cout << "Successfully established communication with serial device read rope. \n";
	}
	catch(boost::system::system_error& e)
	{
		std::cout<< "Error: " << e.what() << std::endl;
		m_serial_dev_ptr = nullptr;
	}
}

uint16_t GetADCValueOfReadRope()
{
	//send command to send ADC value to serial
	m_serial_ptr->writeString("$"); 
	
	//read number
	std::string serial_data = m_serial_dev_ptr->readLine(); 
	
	uint16_t adc_value = std::stoi(serial_data);
	
	return adc_value;
}

Bend GetBendLocationFromReadRopeDevice();
{
	//if calibrated
  if(LIMIT_ZERO != 0 || LIMIT_ONE != 0 || LIMIT_TWO != 0 || LIMIT_THREE != 0 || LIMIT_FOUR != 0 
  || LIMIT_FIVE != 0 || LIMIT_SIX != 0 || LIMIT_SEVEN != 0)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = GetADCValueOfReadRope();
    
    // print the value at serial monitor
    Serial.println(ADC_value);
  
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
  else
  {
    std::cout << "\nPlease calibrate the device.\n";
    return Bend::ERROR_BEND;
  }
  
}
