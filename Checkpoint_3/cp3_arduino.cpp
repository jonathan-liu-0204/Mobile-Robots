//The sample code for driving one way motor encoder
#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <PID_v1.h>

#define L298N_IN1   9
#define L298N_IN2   8
#define L298N_IN3   11
#define L298N_IN4   10

#define left_touch_pin 3
#define right_touch_pin 2
#define under_touch_pin 4
#define light_sensor_pin A0 //A0 

double val_output_L = 0; //Power supplied to the motor PWM value.
double val_output_R = 0; //Power supplied to the motor PWM value.

ros::NodeHandle nh;

std_msgs::Int32 left_pwm;
std_msgs::Int32 right_pwm;

ros::Publisher result_left("left_back", &left_pwm);
ros::Publisher result_right("right_back", &right_pwm);

int E_left = 6; //The enabling of L298PDC motor driver board connection to the digital interface port 5
int E_right = 5;

byte encoder0PinALast_R;
byte encoder0PinALast_L;

double duration_L, abs_duration_L;//the number of the pulses
double duration_R, abs_duration_R;//the number of the pulses

boolean Direction_L;//the rotation direction
boolean Direction_R;//the rotation direction

boolean result_L;
boolean result_R;

double Setpoint_L;
double Setpoint_R;

void setup(){
   Serial.begin(19200);//Initialize the serial port

   pinMode(L298N_IN1, OUTPUT);         
   pinMode(L298N_IN2, OUTPUT);     
   pinMode(L298N_IN3, OUTPUT);     
   pinMode(L298N_IN4, OUTPUT); 
   
   pinMode(left_touch_pin, INPUT);
   pinMode(right_touch_pin, INPUT);
   pinMode(under_touch_pin, INPUT);
   pinMode(light_sensor_pin, INPUT);

   Setpoint_L =80;  //Set the output value of the PID
   Setpoint_R =80;  
   
   digitalWrite(L298N_IN1, LOW);     
   digitalWrite(L298N_IN2, LOW);      
   digitalWrite(L298N_IN3, LOW);      
   digitalWrite(L298N_IN4, LOW); 
   
   nh.initNode();
   nh.advertise(result_left);
   nh.advertise(result_right);
}

void Forward(){
     digitalWrite(L298N_IN1, HIGH);       
     digitalWrite(L298N_IN2, LOW);      
     digitalWrite(L298N_IN3, HIGH);      
     digitalWrite(L298N_IN4, LOW);
     analogWrite(E_left, val_output_L);
     analogWrite(E_right, val_output_R);
}

void Backward(){
     digitalWrite(L298N_IN1, LOW);       
     digitalWrite(L298N_IN2, HIGH);      
     digitalWrite(L298N_IN3, LOW);      
     digitalWrite(L298N_IN4, HIGH);
     analogWrite(E_left, -val_output_L);
     analogWrite(E_right, -val_output_R);
}

void Right(){
     digitalWrite(L298N_IN1, LOW);       
     digitalWrite(L298N_IN2, HIGH);      
     digitalWrite(L298N_IN3, HIGH);      
     digitalWrite(L298N_IN4, LOW);
     analogWrite(E_left, val_output_L);
     analogWrite(E_right, -val_output_R);
}

void Left(){
     digitalWrite(L298N_IN1, HIGH);       
     digitalWrite(L298N_IN2, LOW);      
     digitalWrite(L298N_IN3, LOW);      
     digitalWrite(L298N_IN4, HIGH);
     analogWrite(E_left, -val_output_L);
     analogWrite(E_right, val_output_R);
}

void Stop(){ 
     digitalWrite(E_left, LOW);
     digitalWrite(E_right, LOW);
}


void Right_0_negative(){
     digitalWrite(L298N_IN1, LOW);       
     digitalWrite(L298N_IN2, HIGH);
     digitalWrite(L298N_IN3, HIGH);      
     digitalWrite(L298N_IN4, LOW);
     analogWrite(E_left, 0);
     analogWrite(E_right, -val_output_R);
}

void Right_positive_0(){
     digitalWrite(L298N_IN1, HIGH);       
     digitalWrite(L298N_IN2, LOW);
     digitalWrite(L298N_IN3, HIGH);      
     digitalWrite(L298N_IN4, LOW);
     analogWrite(E_left, val_output_L);
     analogWrite(E_right, 0);
}

void Left_0_positive(){
     digitalWrite(L298N_IN1, HIGH);       
     digitalWrite(L298N_IN2, LOW);      
     digitalWrite(L298N_IN3, HIGH);      
     digitalWrite(L298N_IN4, LOW);
     analogWrite(E_left, 0);
     analogWrite(E_right, val_output_R);
}

void Left_negative_0(){
     digitalWrite(L298N_IN1, HIGH);       
     digitalWrite(L298N_IN2, LOW);
     digitalWrite(L298N_IN3, LOW);      
     digitalWrite(L298N_IN4, HIGH);
     analogWrite(E_left, -val_output_L);
     analogWrite(E_right, 0);
}

void bumped(){
    int count = 0;
    
    while(count < 2){
      val_output_L = -100;
      val_output_R = -100;
      Backward();
      delay(1);
      count++;
    }  
}


int caught = 0;
int situation = 0;

void loop(){
    Serial.begin(19200);
    
    int touch_left = digitalRead(left_touch_pin);
    int touch_right = digitalRead(right_touch_pin);
    int touch_under = digitalRead(under_touch_pin);
    int light_sensor = analogRead(light_sensor_pin);

    if(touch_left == LOW && touch_right == LOW){
        situation = 1;
    }
    else if(light_sensor < 400){
        situation = 3;
    }
    else if(touch_under == LOW){
        situation = 4;
    }
    else if(situation != 2 && caught == 0){
        situation = 0;
    }
    else if(caught == 1){
        situation = 4;
    }

    switch(situation){

      // nothing happened
      case 0:
        val_output_L = 100;
        val_output_R = 100;
        Forward();
        break;

      //hit the wall, go back
      case 1:
        val_output_L = -100;
        val_output_R = -100;
        Backward();
        delay(2000);
        situation = 2;
        break;

      //just went backward from the wall, find the target
      case 2:
        val_output_L = -60;
        val_output_R = 60;
        Left();
        break;

      //there's the target !! RUSH!!!
      case 3:
        val_output_L = 100;
        val_output_R = 100;
        Forward();
        break;

      //Caught the target, stop
      case 4:
        val_output_L = 0;
        val_output_R = 0;
        Stop();
        caught = 1;
        break;
    }

    nh.spinOnce();
}
