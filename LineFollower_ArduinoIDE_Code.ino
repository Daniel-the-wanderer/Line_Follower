//Code originally posted on Github by Daniel-the-wanderer

  //Pins used for IR sensors imput
  const int LeftPin = 2;
  const int RightPin = 3;

  //Pins for controling the motor
  const int MotorA0 = 7;
  const int MotorA1 = 8;
  const int MotorB0 = 11;
  const int MotorB1 = 12;
  
  //Pins used controlling the speed
  const int SpeedA = 9;
  const int SpeedB = 10;

  //set initial speed
  int NormalSpeed = 0;
  int SteeringSpeed = 0;

  //set initia1 sensor values as low
  bool LeftSens = LOW;
  bool RightSens = LOW;

  
void setup() {


  // Start serial communication
  Serial.begin(9600);
  
  //Setting the imput pins for controlling the speed (
  int NormalSpeedRead = analogRead(A0);
  int SteeringSpeedRead = analogRead(A1);
 
  //Set sensor pins as imput
  pinMode(LeftPin, INPUT);
  pinMode(RightPin, INPUT);
    
  //Set pins as output
  pinMode(MotorA0, OUTPUT);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorB0, OUTPUT);
  pinMode(MotorB1, OUTPUT);
    
  //Set speed ctrl pins as output
  pinMode(SpeedA, OUTPUT);
  pinMode(SpeedB, OUTPUT);

  //Map the values of the speed in order to be used for controlling the speed
  int NormalSpeed = map(NormalSpeedRead, 0, 1023, 0 ,255);
  int SteeringSpeed = map(SteeringSpeedRead, 0, 1023, 0, 255);

  //Send the speed values over serial
  Serial.print("Normal Speed : ");
  Serial.print(NormalSpeed);
  Serial.print("  Steering Speed : ");
  Serial.println(SteeringSpeed);
}


void loop() {

 //Read the sensor va1ues
 bool LeftSens = digitalRead(LeftPin);
 bool RightSens = digitalRead(RightPin);
  
  //When the end of the line is reached
 if (LeftSens == LOW && RightSens == LOW){
    
  //Stop the motors
  digitalWrite(MotorA0, LOW);
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorB0, LOW);
  digitalWrite(MotorB1, LOW);
  
  //Set the speed to 0
  analogWrite(SpeedA, 0);
  analogWrite(SpeedB, 0);
 }

 //Move forward if the line is in the middle
 if (LeftSens == HIGH && RightSens == HIGH){

  //Start both motors
  digitalWrite(MotorA0, HIGH);
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorB0, HIGH);
  digitalWrite(MotorB1, LOW);

  //Set the speed to the normal speed
  analogWrite(SpeedA, NormalSpeed);
  analogWrite(SpeedB, NormalSpeed);
 }

 //If the line is on the LEFT, move left
 if (LeftSens == LOW && RightSens == HIGH){

  //Stop the left motor
  digitalWrite(MotorA0, LOW);
  digitalWrite(MotorA1, LOW);
  //Right motor moves forward
  digitalWrite(MotorB0, HIGH);
  digitalWrite(MotorB1, LOW);

  //Set the left motor`s speed to 0
  analogWrite(SpeedA, 0);
  //Set the right motor`s speed to the steering speed
  analogWrite(SpeedB, SteeringSpeed);
  }

 //If the line is on the RIGHT, move right
 if (LeftSens == LOW && RightSens == HIGH){

  //Left motor moves forward
  digitalWrite(MotorA0, HIGH);
  digitalWrite(MotorA1, LOW);
  //Stop the right motor
  digitalWrite(MotorB0, LOW);
  digitalWrite(MotorB1, LOW);

  //Set the left motor`s speed to the steering speed
  analogWrite(SpeedA, SteeringSpeed);
  //Set the right motor`s speed to 0
  analogWrite(SpeedB, 0);
  }

}
