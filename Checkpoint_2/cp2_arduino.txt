//The sample code for driving one way motor encoder
#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <PID_v1.h>


double val_output_L = 0; //Power supplied to the motor PWM value.
double val_output_R = 0; //Power supplied to the motor PWM value.

ros::NodeHandle nh;

std_msgs::Int32 answer_left;
int receive_left = 0;

void number_callback_left(const std_msgs::Int32 & msg_l){
    answer_left.data = msg_l.data;
    receive_left = 1;
}

std_msgs::Int32 answer_right;
int receive_right = 0;

void number_callback_right(const std_msgs::Int32 & msg_r){
    answer_right.data = msg_r.data;
    receive_right = 1;
}

ros::Subscriber<std_msgs::Int32> sub_left("left", number_callback_left);
ros::Publisher result_left("left_back", &answer_left);

ros::Subscriber<std_msgs::Int32> sub_right("right", number_callback_right);
ros::Publisher result_right("right_back", &answer_right);


#define L298N_IN1   9
#define L298N_IN2   8
#define L298N_IN3   11
#define L298N_IN4   10

const byte encoder0pinA_R = 2;
const byte encoder0pinB_R = 4;
const byte encoder0pinA_L = 12;
const byte encoder0pinB_L = 9;

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

//double val_output_L = 0; //Power supplied to the motor PWM value.
//double val_output_R = 0; //Power supplied to the motor PWM value.

double Setpoint_L;
double Setpoint_R;

// double Kp_L = 0.6, Ki_L = 5, Kd_L = 0;
// double Kp_R = 0.6, Ki_R = 5, Kd_R = 0;

// PID myPID_L(&abs_duration_L, &val_output_L, &Setpoint_L, Kp_L, Ki_L, Kd_L, DIRECT);
// PID myPID_R(&abs_duration_R, &val_output_R, &Setpoint_R, Kp_R, Ki_R, Kd_R, DIRECT);

void setup(){

   Serial.begin(9600);//Initialize the serial port

   pinMode(L298N_IN1, OUTPUT);         
   pinMode(L298N_IN2, OUTPUT);     
   pinMode(L298N_IN3, OUTPUT);     
   pinMode(L298N_IN4, OUTPUT); 
   
   pinMode(E_left, OUTPUT);
   pinMode(E_right, OUTPUT);
   
   Setpoint_L =80;  //Set the output value of the PID
   Setpoint_R =80;  
   
   // myPID_L.SetMode(AUTOMATIC);//PID is set to automatic mode
   // myPID_R.SetMode(AUTOMATIC);
   // myPID_L.SetSampleTime(100);//Set PID sampling frequency is 100ms
   // myPID_R.SetSampleTime(100);
   
   digitalWrite(L298N_IN1, LOW);     
   digitalWrite(L298N_IN2, LOW);      
   digitalWrite(L298N_IN3, LOW);      
   digitalWrite(L298N_IN4, LOW); 
   
   EncoderInit();//Initialize the module

   nh.initNode();
    
   nh.subscribe(sub_left);
    
   nh.advertise(result_left);

   nh.subscribe(sub_right);

   nh.advertise(result_right);
}

void EncoderInit(){

  Direction_L = true;//default -> Forward  
  Direction_R = true;//default -> Forward

  pinMode(encoder0pinB_L,INPUT);
  attachInterrupt(1, wheelSpeed_L, CHANGE);
  
  pinMode(encoder0pinB_R,INPUT);
  attachInterrupt(0, wheelSpeed_R, CHANGE);
}

void wheelSpeed_L(){

  int Lstate_L = digitalRead(encoder0pinA_L);
  
  if((encoder0PinALast_L == LOW) && Lstate_L==HIGH){
    
    int val_L = digitalRead(encoder0pinB_L);
    
    if(val_L == LOW && Direction_L){
      Direction_L = false; //Reverse
    }
    else if(val_L == HIGH && !Direction_L){
      Direction_L = true;  //Forward
    }
  }
  encoder0PinALast_L = Lstate_L;

  if(!Direction_L)  duration_L++;
  else  duration_L--;
}

void wheelSpeed_R(){
  
  int Lstate_R = digitalRead(encoder0pinA_R);
  
  if((encoder0PinALast_R == LOW) && Lstate_R==HIGH){
    
    int val_R = digitalRead(encoder0pinB_R);
    
    if(val_R == LOW && Direction_R){
      Direction_R = false; //Reverse
    }
    else if(val_R == HIGH && !Direction_R){
      Direction_R = true;  //Forward
    }
  }
  encoder0PinALast_R = Lstate_R;

  if(Direction_R)  duration_R++;
  else  duration_R--;
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


void loop(){

      if(receive_left == 1 && receive_right == 1){
        result_left.publish(&answer_left);
        result_right.publish(&answer_right);
  
        receive_left = 0;
        receive_right = 0;

        val_output_L = answer_left.data;
        val_output_R = answer_right.data;
      }
      else{
        
        if((val_output_L > 0) && (val_output_R > 0)){
          Forward();
        }
        else if((val_output_L < 0) && (val_output_R < 0)){
          Backward();
        }
        else if((val_output_L > 0) && (val_output_R < 0)){
          Right();
        }
        else if((val_output_L < 0) && (val_output_R > 0)){
          Left();
        }
        else if((val_output_L == 0) && (val_output_R == 0)){
          Stop();
        }
        else if((val_output_L == 0) && (val_output_R > 0)){
          Left_0_positive();
        }
        else if((val_output_L == 0) && (val_output_R < 0)){
          Right_0_negative();
        }
        else if((val_output_L > 0) && (val_output_R == 0)){
          Right_positive_0();
        }
        else if((val_output_L < 0) && (val_output_R == 0)){
          Left_negative_0();
        }
        
        nh.spinOnce();
      }

//      Forward();

      //Forward(); //Motor Forward
      // abs_duration_L = abs(duration_L);
      // abs_duration_R = abs(duration_R);
      
      // result_L=myPID_L.Compute(); //PID conversion is complete and returns 1
      // result_R=myPID_R.Compute();

      // result_L = 1;
      // result_R = 1;
      
      // if(result_L){
      // Serial.print("Pluse L: ");
      // Serial.println(duration_L);
      // duration_L = 0; //Count clear, wait for the next count
      // }

      // if(result_R){
      // Serial.print("Pluse R: ");
      // Serial.println(duration_R);
      // duration_R = 0; //Count clear, wait for the next count
      // }
}
