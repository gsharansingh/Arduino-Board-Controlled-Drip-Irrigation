/*
 * Assigning pins to a variables
 */
const int sensor_1=A1;
const int sensor_2=A2;
const int relay=13;
const int mode_1=10;
const int mode_2=11;

void setup() 
{
  Serial.begin(9600); //To see the output at different stages on Serial Monitor
  /*
   * Defining the function of different pins
   */
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(mode_1, OUTPUT);
  pinMode(mode_2, OUTPUT);
}

void loop()
{
  Serial.println("Started");
  int moisture_1= analogRead(sensor_1); //Reading the moisture data from Sensor #1
  int moisture_2= analogRead(sensor_2); //Reading the moisture data from Sensor #1
  int flag=0;
  
  if ( moisture_1 >= 800 || moisture_2 >= 800 ) //checking the moisture level of both Sensors
  { 
    String data_1="";
    data_1 += (char)moisture_1;
    String data_2="";
    data_2 += (char)moisture_2;
    Serial.println(" Moisture Level at Sensor 1 = "+ data_1);
    Serial.println(" Moisture Level at Sensor 2 = "+ data_2);
    if ( moisture_1 > moisture_2 ) 
    {
      Serial.println("Mode 1 is selected");
      flag=1;
      digitalWrite( mode_1 , HIGH );
      delay(500);
      digitalWrite( mode_1 , LOW );
    }
    else
    {
      Serial.println("Mode 2 is selected");
      flag=2;
      digitalWrite( mode_2 , HIGH );
      delay(500);
      digitalWrite( mode_2 , LOW );
    }
    
    Serial.println("Water Pump is gonna start in 3 seconds");
    digitalWrite( relay , HIGH );

    /*
     * Continuously checking the moisture level at both sensors
     */
    while(1)
    {
      delay(5000);
      if ( flag == 1)
      {
        if ( moisture_1 < 500 )
        {
          digitalWrite( relay , LOW );
          break;
        }
      }
      if ( flag == 2)
      {
        if ( moisture_2 < 500 )
        {
          digitalWrite( relay , LOW );
          break;
        }
      }
    }
  }
  delay(3600000); //1 hour delay
}
