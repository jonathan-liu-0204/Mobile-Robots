
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int light_value = 0;
int received_light = 0;

void number_callback_light(const std_msgs::Int32 & msg2){
    light_value = msg2.data;
    received_light = 1;
}

// int answer_right;
// int received_right = 0;

// void number_callback_right(const std_msgs::Int32 & msg3){
//     answer_right = msg3.data;
//     received_right = 1;
// }


int command = -100;

int main(int argc, char **argv){
    ros::init(argc, argv, "cp3");
    ros::NodeHandle node_obj;

    std_msgs::Int32 msg_command;

    //ros::Publisher command_publisher = node_obj.advertise<std_msgs::Int32>("command_num", 1);
    ros::Subscriber light_subscriber = node_obj.subscribe("light_value", 1, number_callback_light);
    //ros::Subscriber right_subscriber = node_obj.subscribe("right_back", 1, number_callback_right);
    
    //std::cout << "Please enter command: " << std::endl;
    //std::cout << "1: start robot program" << std::endl;
    //std::cout << "2: test light sensor" << std::endl;
    //std::cin >> command;

    // if(command != -100){
	//     msg_command.data = command;
	//     command_publisher.publish(msg_command);
    // }

    while (ros::ok()){
	
	    if(received_light == 1){

            std::cout << "Current light value:  " << light_value << std::endl;
            ros::Duration(0.5).sleep();
            received_light = 0;

            // std::cout << "Arduino received right power:  " << answer_right << std::endl;
	    }
        else{
            ros::spinOnce();
        }
    }
    return 0;
}
