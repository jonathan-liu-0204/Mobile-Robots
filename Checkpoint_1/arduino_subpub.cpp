#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

// void messageCb(const std_msgs::Empty&toggle_msg){
//     digitalWrite(13, HIGH-digitalRead(13)); // blink the led
// }

std_msgs::Int32 answer;

void number_callback(const std_msgs::Int32::Constptr& msg){
    ROS_INFO("Received [%d]", msg->data);
    answer = msg.data * 2;
}

ros::Subscriber<std_msgs::Int32> sub("initial_num", &number_callback );

ros::Publisher result("result", &answer);

void setup(){
    nh.initNode();
    nh.subscribe(sub);

    nh.advertise(result);
}

void loop(){
    result.publish(&answer)
    nh.spinOnce();
}

// ros::Subscriber<std_msgs::Empty> sub("initial_num", &number_callback);

// std_msgs::Int32 num_result;
// ros::Publisher chatter("new_num", &num_result);
// // char hello[13] = "hello world";

// void setup(){
//     nh.initNode();
//     nh.advertise(new_num);
     
//     pinMode(13, OUTPUT);
//     nh.subscribe(sub);
// }

// void loop(){
//     nh.spinOnce();
//     delay(1);

//     num_result.data = msg.data;
//     num_result.data = num_result.data * 2;
//     chatter.publish(&num_result);
//     nh.spinOnce();
//     delay(500);
// }