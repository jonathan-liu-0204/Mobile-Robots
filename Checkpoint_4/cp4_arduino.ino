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
#define IR_pin 13

double val_output_L = 0; //Power supplied to the motor PWM value.
double val_output_R = 0; //Power supplied to the motor PWM value.

ros::NodeHandle nh;
std_msgs::Int32 light_value;
std_msgs::Int32 IR_value;

// ros::Subscriber<std_msgs::Int32> command_subscriber("command_num", number_callback_command);
ros::Publisher light_publisher("light_value", &light_value);
ros::Publisher IR_publisher("IR_value", &IR_value);

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
   //Serial.begin(9600);//Initialize the serial port

   pinMode(L298N_IN1, OUTPUT);         
   pinMode(L298N_IN2, OUTPUT);     
   pinMode(L298N_IN3, OUTPUT);     
   pinMode(L298N_IN4, OUTPUT); 
   
   pinMode(left_touch_pin, INPUT);
   pinMode(right_touch_pin, INPUT);
   pinMode(under_touch_pin, INPUT);
   pinMode(light_sensor_pin, INPUT);
   pinMode(IR_pin, INPUT);

   Setpoint_L = 80;  //Set the output value of the PID
   Setpoint_R = 80;  
   
   digitalWrite(L298N_IN1, LOW);     
   digitalWrite(L298N_IN2, LOW);      
   digitalWrite(L298N_IN3, LOW);      
   digitalWrite(L298N_IN4, LOW); 
   
   nh.initNode();
   nh.advertise(light_publisher);
   nh.advertise(IR_publisher);
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

int which_IR = 0;

int find_goal(){
     float rate = 0.0;
     float count_low = 0.0;
     float count_high = 0.0;

     for(int i = 0; i < 120; i++){
          if(digitalRead(IR_pin) == 1){
               count_high++;
               delay(1);
          }

          if(digitalRead(IR_pin) == 0){
               count_low++;
               delay(1);
          }
     }

     rate = count_low / (count_high + count_low);

     if(rate > 0.25 && rate < 0.37){
          which_IR = 600;
          return 600;
     }
     else if(rate > 0.17 && rate < 0.22){
          which_IR = 1500;
          return 1500;
     }
     else{
          return 0;
     }
}


int caught = 0;
int situation = 0;
int count = 1;
int done = 0;


void loop(){
    // Serial.begin(19200);

     int touch_left = digitalRead(left_touch_pin);
     int touch_right = digitalRead(right_touch_pin);
     int touch_under = digitalRead(under_touch_pin);
     int light_sensor = analogRead(light_sensor_pin);

     // Serial.print("touch_left: ");
     // Serial.println(touch_left);
     // Serial.print("touch_right: ");
     // Serial.println(touch_right);
//    Serial.print("touch_under: ");
//    Serial.println(touch_under);
//    Serial.print("light_sensor: ");
//    Serial.println(light_sensor);
//
    //delay(5);

    if((touch_left == LOW && touch_right == LOW) && (situation == 0 || situation == 3)){
        situation = 1;
    }
    else if(light_sensor < 600 && situation == 2){
        situation = 3;
    }
    else if(touch_under == LOW && situation == 3){
        situation = 4;
    }
    else if(situation == 4 && find_goal() == 600){
        situation = 5;
    }
    else if(situation == 4 && find_goal() == 1500){
        situation = 6;
    }
    else if((touch_left == LOW || touch_right == LOW) && situation == 6){
        situation = 7;
    }
    else if(done == 1){
        situation = 8;
    }

    switch(situation){

      // nothing happened
      case 0:
        val_output_L = 250;
        val_output_R = 250;
        Forward();
        break;

      //hit the wall, go back
      case 1:
        val_output_L = -100;
        val_output_R = -100;
        Backward();
        delay(600);
        situation = 2;
        break;

      //just went backward from the wall, find the target
      case 2:
        val_output_L = -100;
        val_output_R = 100;
        Left();
        break;

      //there's the target !! RUSH!!!
      case 3:
        val_output_L = 100;
        val_output_R = 100;
        Forward();
        break;

      //Caught the target, find the goal
      case 4:
        val_output_L = 100;
        val_output_R = -100;
        Right();
        break;

      //when it's IR 600, turn back a bit
      case 5:
        val_output_L = -120;
        val_output_R = 120;
        Left();
        delay(200);
        situation = 6;
      
      //Found the goal, gooo!!!!
      case 6:
        val_output_L = 180;
        val_output_R = 180;
        Forward();
        break;
      
      //Reached the goal, leave the ball
      case 7:
        delay(800);
        val_output_L = -120;
        val_output_R = -120;
        Backward();
        delay(800);
        situation = 8;

      //Goallll! Stop
      case 8:
        val_output_L = 0;
        val_output_R = 0;
        Stop();
        done = 1;
        break;

      default:
        val_output_L = 0;
        val_output_R = 0;
        Stop();
        done = 1;
        break;
    }

    if(count == 100){
        light_value.data = light_sensor;
        light_publisher.publish(&light_value);
        
        IR_value.data = find_goal();
        IR_publisher.publish(&IR_value);

        count = 1;
    }
    else{
        nh.spinOnce();
    }
    count++;
}