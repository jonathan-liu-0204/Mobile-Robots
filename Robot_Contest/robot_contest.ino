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
#define light_sensor_pin A0
#define IR_pin 13

double val_output_L = 0; //Power supplied to the motor PWM value.
double val_output_R = 0; //Power supplied to the motor PWM value.

ros::NodeHandle nh;
std_msgs::Int32 command_back_value;

int command_value = 99;
int received_command = 0;

void number_callback_command(const std_msgs::Int32 & msg2){
    command_value = msg2.data;
    received_command = 1;
}

ros::Subscriber<std_msgs::Int32> command_subscriber("command_num", number_callback_command);
ros::Publisher command_back("command_back", &command_back_value);

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

   nh.subscribe(command_subscriber);
   nh.advertise(command_back);
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

     int touch_left = digitalRead(left_touch_pin);
     int touch_right = digitalRead(right_touch_pin);
     int touch_under = digitalRead(under_touch_pin);
     int light_sensor = analogRead(light_sensor_pin);

     delay(5);

    

    if(received_command == 1){
      command_back_value.data = command_value;
      command_back.publish(&command_back_value);
      received_command = 0;
    }
    else{
      // Left. Goal 600
      if(command_value == 1){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 600){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 8){
              situation = 9;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(200);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(500);
              situation = 3;
              break;
      
            case 3:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(100);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(300);
              situation = 6;
              break;
      
            case 6:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              break;
      
            case 7:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              delay(100);
              situation = 8;
      
            case 8:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 9:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }
      
      // Middle. Goal 600
      else if(command_value == 2){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 600){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 8){
              situation = 9;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(200);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 3;
              break;
      
            case 3:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(300);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(800);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(300);
              val_output_L = -120;
              val_output_R = 120;
              Left();
              delay(200);
              situation = 6;
              break;
      
            case 6:
              val_output_L = -100;
              val_output_R = 100;
              Left();
              break;
      
            case 7:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              delay(200);
              situation = 8;
      
            case 8:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 9:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }

      
      // Right. Goal 600
      else if(command_value == 3){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 600){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 8){
              situation = 9;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(150);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 3;
              break;
      
            case 3:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(150);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(250);
              val_output_L = -120;
              val_output_R = 120;
              Left();
              delay(250);
              situation = 6;
              break;
      
            case 6:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              break;
      
            case 7:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              delay(100);
              situation = 8;
      
            case 8:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 9:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }

      // Left. Goaling 1500
      else if(command_value == 4){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 1500){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 7){
              situation = 8;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(200);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(500);
              situation = 3;
              break;
      
            case 3:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(100);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(250);
//              val_output_L = -120;
//              val_output_R = 120;
//              Left();
//              delay(200);
              situation = 6;
              break;
      
            case 6:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              break;
      
            case 7:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 8:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }

      // Middle. Goal 1500
      else if(command_value == 5){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 1500){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 7){
              situation = 8;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(200);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(500);
              situation = 3;
              break;
      
            case 3:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(300);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(800);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(300);
//              val_output_L = -120;
//              val_output_R = 120;
//              Left();
//              delay(200);
              situation = 6;
              break;
      
            case 6:
              val_output_L = -100;
              val_output_R = 100;
              Left();
              break;
      
            case 7:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 8:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }

      // Right. Goal 1500
      else if(command_value == 6){
          if(situation == 10 && done == 0){
            situation = 0;
          }
          else if(touch_under == LOW && situation == 0){
            situation = 1;
          }
          else if(situation == 6 && find_goal() == 1500){
              situation = 7;
          }
          else if((touch_left == LOW && touch_right == LOW) && situation == 7){
              situation = 8;
          }
          else if(done == 1){
              situation = 10;
          }
          
          switch(situation){
  
            case 0:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 1:
              val_output_L = 255;
              val_output_R = -255;
              Right();
              delay(150);
              situation = 2;
              break;
      
            case 2:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(600);
              situation = 3;
              break;
      
            case 3:
              val_output_L = -255;
              val_output_R = 255;
              Left();
              delay(150);
              situation = 4;
              break;
      
            case 4:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              delay(800);
              situation = 5;
              break;
      
            case 5:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(250);
              situation = 6;
              break;
      
            case 6:
              val_output_L = 100;
              val_output_R = -100;
              Right();
              break;
      
            case 7:
              val_output_L = 255;
              val_output_R = 255;
              Forward();
              break;
      
            case 8:
              val_output_L = -120;
              val_output_R = -120;
              Backward();
              delay(800);
              situation = 10;
      
            case 10:
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
      }
      else{
        val_output_L = 0;
        val_output_R = 0;
        Stop();

        situation = 10;
        done = 0;
      }
      
      nh.spinOnce();
    }
}
