
#include "SimpleSerial.h" //for getting serial data

#include <cstdint>
#include <iostream>

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


enum class Bend : uint8_t {ERROR_BEND = 0, NO_BEND, BEND_S0, BEND_S1, BEND_S0_S1, BEND_S2, BEND_S0_S2, BEND_S1_S2, BEND_S0_S1_S2};

//system refers to the state machine and functions performed by the read rope library. 



//state machine of the system
uint8_t state_machine = STATE_NULL;

//serial device communicator
SimpleSerial* m_serial_dev_ptr;


/*
 *************
 * Functions *
 ************* 
*/


//function to make the system start reading information coming from the read rope
void StartReadingFromReadRope();

//function to make the system to stop reading information coming from read rope
void StopReadingFromReadRope();



//function to make the system start calibrating the device
//calibration involves just changing the way the system interprets the information.
void StartCalibrationProcess();


//function to initialize serial communication with serial device of read rope
void InitSerialCommunication(std::string port,unsigned int baud_rate);


//function to get the ADC value directly from read rope device through serial communication
uint16_t GetADCValueOfReadRope();

//function to make the system get the bend location from interpreting
//information from read rope device
Bend GetBendLocationFromReadRopeDevice(); 
