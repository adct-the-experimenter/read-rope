//Arduino Code for reading ADC from read rope

/*

  For the current prototype, 3 bend section.
  VCC - 56k -|- 10k - 24k - 56k - GND
            Out 
 0 = no bend, 1 = bend

 Arduino Uno has 10-bit ADC taking in values from 0V - 5V, 4.9mV per unit
 https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
 
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

uint8_t state_machine = STATE_NULL;

bool instruction_displayed = false;

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

  switch(state_machine)
  {
    case STATE_NULL:
    {
      if(!instruction_displayed)
      {
         Serial.println("Send char.\n !) Start Calibration\n @) Read bends\n #) Standby mode\n");
         instruction_displayed = true;
      }
      break;
    }
    case STATE_CALIBRATION_START:{ StartCalibration(); break;}
    case STATE_CALIBRATION_S0:{ CalibrateSectionZero(); break;}
    case STATE_CALIBRATION_S1:{ CalibrateSectionOne(); break;}
    case STATE_CALIBRATION_S2:{ CalibrateSectionTwo(); break;}
    case STATE_READ:{ ReadBendValues(); break;}
  }
  
  delay(100);       // delay in between reads for stability
}

void ReadSerialForStateInput()
{
  
  while (Serial.available() > 0) 
  {
    char incomingCharacter = Serial.read();
    
    switch (incomingCharacter) 
    {
      //switch to calibration mode
      case '!':
      {
        state_machine = STATE_CALIBRATION_START; 
        break;
      }
      //switch to 
      case '@':
      {
        state_machine = STATE_READ;
        break;
      }
      //send out rotation quaternion y value
      case '#':
      {
        state_machine = STATE_NULL;
        break;
      }
      //send out rotation quaternion z value
      case '$':
      {
        
        break;
      }
      case '%':
      {
        
        break;
      }
    }
  }
}

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
  Serial.println("\nStarting calibration. Please leave read rope in state with no bends for a few seconds.\n");

  uint16_t count = 0;
  while(count != 30)
  {
    // Read the analog value from pin A0
    uint16_t ADC_value = analogRead(A0);
    LIMIT_ZERO = ADC_value;
    delay(100);
    count++;
  }

  Serial.println("\nFinished no bend phase.\n");
  Serial.println(LIMIT_ZERO);

  //go to next phase of calibration
  state_machine = STATE_CALIBRATION_S0;
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
    else if(ADC == LIMIT_ONE)
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
    else if(ADC == LIMIT_TWO)
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
    else if(ADC == LIMIT_FOUR)
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
