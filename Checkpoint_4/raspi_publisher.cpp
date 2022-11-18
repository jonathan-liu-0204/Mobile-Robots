#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int light_value = 0;
int received_light = 0;

void number_callback_light(const std_msgs::Int32 & msg2){
    light_value = msg2.data;
    received_light = 1;
}

int IR_value = 0;
int received_IR = 0;

void number_callback_IR(const std_msgs::Int32 & msg3){
    IR_value = msg2.data;
    received_IR = 1;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "cp3");
    ros::NodeHandle node_obj;

    std_msgs::Int32 msg_command;

    //ros::Publisher command_publisher = node_obj.advertise<std_msgs::Int32>("command_num", 1);
    //ros::Subscriber right_subscriber = node_obj.subscribe("right_back", 1, number_callback_right);

    ros::Subscriber light_subscriber = node_obj.subscribe("light_value", 1, number_callback_light);
    ros::Subscriber IR_subscriber = node_obj.subscribe("IR_value", 1, number_callback_IR);


    while (ros::ok()){
	
	    if(received_light == 1 && received_IR == 1){

            std::cout << "Current light value:  " << light_value << std::endl;
            std::cout << "Current IR value:  " << IR_value << std::endl;
            ros::Duration(0.5).sleep();
            received_light = 0;
            received_IR = 0;
	    }
        else if(received_light == 1){

            std::cout << "Current light value:  " << light_value << std::endl;
            ros::Duration(0.5).sleep();
            received_light = 0;
	    }
        else if(received_IR == 1){

            std::cout << "Current IR value:  " << IR_value << std::endl;
            ros::Duration(0.5).sleep();
            received_IR = 0;
	    }
        else{
            ros::spinOnce();
        }
    }
    return 0;
}
