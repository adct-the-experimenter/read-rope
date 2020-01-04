//Arduino Code for reading ADC from read rope

void setup() 
{
  // put your setup code here, to run once
  
  // initialize serial communication at 9600 baud rate
  Serial.begin(9600);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  // Read the analog value from pin A0
  int ADC_value = analogRead(A0);
  
  // print the value at serial monitor
  Serial.println(ADC_value);
  
  delay(100);       // delay in between reads for stability

}
