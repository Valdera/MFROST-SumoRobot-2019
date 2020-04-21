
const int leftForward   = 8;
const int leftBackward  = 7;
const int rightForward  = 2;
const int rightBackward = 3;
const int ENA_R = 6; //Enable Pin of the Right Motor (must be PWM)
const int ENA_L = 5; //Enable Pin of the Left Motor (must be PWM)
const int Sensor1 = A0; //Left Sensor (PWM)
const int Sensor2 = A1; //Left Sensor (PWM)
const int Sensor3 = A2; //Right Sensor (PWM)
const int Sensor4 = A3; //Right Sensor (PWM)
// Speed of the Motors
int ENASpeed = 255 ;
// Horn Button to switch mode
bool isAuto = true; 
char bt='S';
// To check the condition
int counter = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(ENA_R, OUTPUT);
  pinMode(ENA_L, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  Stop();
}


void loop() {
  //Use analogWrite to run motor at adjusted speed
  analogWrite(ENA_R, ENASpeed);
  analogWrite(ENA_L, ENASpeed);
  //Android Controlled (Manual)
  while(isAuto == false){
    bt = Serial.read();
    switch (bt){
      case 'F': forward();
      break;
      case 'B': backward();
      break;
      case 'L': left();
      break;
      case 'R': right();
      break;
      case 'S': Stop();
      break;
      case 'v': isAuto = true;
      break;
      default: Stop();
      break;
    }
   }
    //Line Follower Code (Automatic)
   while (isAuto == true){
     int valSensor1 = analogRead(Sensor1);
     int valSensor2 = analogRead(Sensor2);
     int valSensor3 = analogRead(Sensor3);
     int valSensor4 = analogRead(Sensor4);
     if (valSensor1 == HIGH && valSensor2 == HIGH && valSensor2 == LOW && valSensor1 == LOW){
       left();
     }
     else if (valSensor4 == LOW && valSensor3 == LOW && valSensor2 == HIGH && valSensor1 == HIGH){
       right();
     }
     else if (valSensor4 == LOW && valSensor3 == HIGH && valSensor2 == HIGH && valSensor1 == LOW) {
       forward();  
       counter = 0;
     }
     else {
       if (counter < 20){
         right(); 
       }
       else {
         left();
       }
        counter ++;
     }
      // Check the condition
     bt = Serial.read();
     if (bt = 'V'){
       isAuto = true;
     }
  }
}


void forward()
{
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);                  
}

void backward()
{
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);  
}
void left()
{
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);  
}
void right()
{
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH); 
}
void Stop()
{
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);  
}
/*
//BackUp 
void read()
{
  bt=Serial.read()
  if(bt == 'V'){
    isAuto = false;  
  }
  if(bt == 'v'){
    isAuto = true;  
  }  
}
*/

    /*if(bt=='F'){
      forward(); 
    }
    if(bt=='B'){
      backward(); 
    }
    if(bt=='L'){
      left(); 
    }
    if(bt=='R'){
      right(); 
    }
    if(bt=='S'){
      Stop(); 
    }
    // Check the condition
    if(bt == 'v'){
      isAuto = true;  
    }*/
