
/* 
 * File:   SimpleSerial.h
 * Author: Terraneo Federico
 * Distributed under the Boost Software License, Version 1.0.
 *
 * Created on September 10, 2009, 12:12 PM
 */

#ifndef _SIMPLESERIAL_H
#define	_SIMPLESERIAL_H

#include <boost/asio.hpp>

class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    SimpleSerial(std::string port, unsigned int baud_rate)
    : io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    std::string readLine()
    {
        //Reading data char by char, code is optimized for simplicity, not speed
        char c;
        std::string result;
        for(;;)
        {
            boost::asio::read(serial,boost::asio::buffer(&c,1));
            switch(c)
            {
                case '\r':
                    break;
                case '\n':
                    return result;
                default:
                    result+=c;
            }
        }
    }

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};

#endif	/* _SIMPLESERIAL_H */


#include <cstdint>
#include <iostream>


namespace ReadRope{
	
	enum class Bend : uint8_t {ERROR_BEND_NO_CALIBRATION = 0, NO_BEND, BEND_S0, BEND_S1, BEND_S0_S1, BEND_S2, BEND_S0_S2, BEND_S1_S2, BEND_S0_S1_S2};

	enum class Status : uint8_t {ERROR = 0, ERROR_SYS_NOT_INIT, SUCCESS};


/*
 *************
 * Functions *
 ************* 
*/

//function to initialize the system for reading from read rope
//Just initializes some objects that makes it easy to 
void InitReadRopeSystem();

//function to close the system
//cleans up resources
void CloseReadRopeSystem();

//function to get the serial port that read rope device is connected to
std::string GetSerialPortOfReadRopeDevice();

//function to initialize serial communication with serial device of read rope
Status InitSerialCommunication(std::string port,unsigned int baud_rate);


/* 
 *********************
       Calibration
 ********************* 
*/

//Can do calibration manually using SetSectionXMaxLimit functions
//or use default methods for calibrating the section

//function to determine the highest limit for section zero
//must bend section zero as much as you can
void CalibrateSectionZeroMaxLimit(double& duration);

//function to set high limit for section zero
void SetSectionZeroMaxLimit(uint16_t& limit);

//function to determine the highest limit for section one
//must bend section one as much as you can
void CalibrateSectionOneMaxLimit(double& duration);

//function to set high limit for section one
void SetSectionOneMaxLimit(uint16_t& limit);

//function to determine the highest limit for section two
//must bend section two as much as you can
void CalibrateSectionTwoMaxLimit(double& duration);

//function to set high limit for section two
void SetSectionTwoMaxLimit(uint16_t& limit);

//function to set minimum limit for a bend in both section zero and section one
void SetSectionZeroOneComboMinLimit(uint16_t& limit);

//function to set minimum limit for a bend in both section zero and section two
void SetSectionZeroTwoComboMinLimit(uint16_t& limit);

//function to set minimum limit for a bend in both section one and section two
void SetSectionOneTwoComboMinLimit(uint16_t& limit);

//function to set minimum limit for a bend in all 3 sections
void SetSectionOneTwoThreeComboMinLimit(uint16_t& limit);

/*
 LIMIT_ZERO No bend
 LIMIT_ONE  minimum limit for bend in only section 0
 LIMIT_TWO  maximum limit for bend in only section 1
 LIMIT_FOUR maximum limit for bend in only section 2
 
 LIMIT_THREE minimum limit for bends in section 0 and section 1 
 LIMIT_FIVE minimum limit for bends in section 0 and section 2
 LIMIT_SIX minimum limit for bends in section 1 and section 2
 LIMIT_SEVEN minimum limit for bends in all 3 sections.

*/


//function to get the ADC value directly from read rope device through serial communication
uint16_t GetADCValueOfReadRope();

//function to make the system get the bend location from interpreting
//information from read rope device
Bend GetBendLocationFromReadRopeDevice();
	
}

 
