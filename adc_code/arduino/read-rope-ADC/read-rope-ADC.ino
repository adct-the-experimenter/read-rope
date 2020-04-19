//Arduino Code for reading ADC from read rope

/*

  For the current prototype, 3 bend section.
  VCC - 56k -|- 10k - 24k - 56k - GND
            Out 
 0 = no bend, 1 = bend

 Arduino Uno has 10-bit ADC taking in values from 0V - 5V, 4.9mV per unit
 https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/

 Pins Used:
 5V, GND, A0

 Set Serial Monitor to 9600 baud rate.
 
 Combination | Bends  |  Expected Output Voltage  |  ADC value

 0              000              1.978                  403
 1              001              2.041                  416
 2              010              2.194                  447
 3              011              2.248                  458
 4              100              2.484                  506
 5              101              2.527                  515
 6              110              2.635                  537
 7              111              2.673                  545
 
 */


void setup() 
{
  // put your setup code here, to run once

  
  // initialize serial communication at 9600 baud rate
  Serial.begin(9600);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  //read serial input to determine which state to run
  ReadSerialForStateInput();

  delay(500);
}

void ReadSerialForStateInput()
{
  
  while (Serial.available() > 0) 
  {
    char incomingCharacter = Serial.read();
    
    switch (incomingCharacter) 
    {
 
      // send ADC value to serial
      case '$':
      {
        SendADCValueToSerial();
        break;
      }
      //send character Y to serial
      case '%':
      {
        Serial.println("Y");
        break;
      }
    }
  }

  
}

void SendADCValueToSerial()
{
	uint16_t ADC_value = analogRead(A0);
	Serial.println(ADC_value);
}
