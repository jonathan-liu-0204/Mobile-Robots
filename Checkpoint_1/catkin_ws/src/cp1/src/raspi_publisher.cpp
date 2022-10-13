
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int answer;
int received = 0;

void number_callback(const std_msgs::Int32 & msg2){
    answer = msg2.data;
    received = 1;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "demo_topic_publisher");
    ros::NodeHandle node_obj;
    ros::Publisher number_publisher = node_obj.advertise<std_msgs::Int32>("initial_num", 1);
    ros::Subscriber number_subscriber = node_obj.subscribe("result", 1, number_callback);

    int inputNum = -1;
    std_msgs::Int32 msg;

    std::cout << "user's input is ";
    std::cin >> inputNum;

    if(inputNum > 0){
        msg.data = inputNum;
        number_publisher.publish(msg);
    }

    while (ros::ok()){
        if(received == 1){
            std::cout << "message from Arduino is " << answer << std::endl;
            received = 0;

            int inputNum = -1;
                std_msgs::Int32 msg;

                std::cout << "user's input is ";
                std::cin >> inputNum;

            if(inputNum >= 0){
                msg.data = inputNum;
                number_publisher.publish(msg);
            }
        }
        ros::spinOnce();
    }
    return 0;
}
