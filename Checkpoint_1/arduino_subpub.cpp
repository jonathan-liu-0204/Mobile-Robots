#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

// void messageCb(const std_msgs::Empty&toggle_msg){
//     digitalWrite(13, HIGH-digitalRead(13)); // blink the led
// }

std_msgs::Int32 answer;
int receive = 0;

void number_callback(const std_msgs::Int32 & msg){
    int cal = msg.data;
    cal = cal * 2;
    answer.data = cal;
    receive = 1;
}

ros::Subscriber<std_msgs::Int32> sub("initial_num", number_callback);

ros::Publisher result("result", &answer);

void setup(){
    nh.initNode();
    nh.subscribe(sub);

    nh.advertise(result);
}

void loop(){

    if(receive == 1){
      result.publish(&answer);
      receive = 0;
    }
    else{
      nh.spinOnce();
    }
    
    //nh.spinOnce();
    //delay(1000);
//    result.publish(&answer);
}
