#include "readrope.h"


int main(int argc, char* argv)
{
	std::string port = ReadRope::GetSerialPortOfReadRopeDevice();
	
	if(port != "Null")
	{
		std::cout << "Read rope device port is " << port << std::endl;
		ReadRope::InitSerialCommunication(port,9600);
	}
	else
	{
		std::cout << "Failed to get port of read rope device! \n.";
	}
	
	return 0;
}
