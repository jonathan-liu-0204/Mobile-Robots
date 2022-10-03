#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

// void messageCb(const std_msgs::Empty&toggle_msg){
//     digitalWrite(13, HIGH-digitalRead(13)); // blink the led
// }

std_msgs::Int32 answer;

void number_callback(const std_msgs::int32_t::Constptr& msg){
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