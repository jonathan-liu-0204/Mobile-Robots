#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int command_value = 0;
int received_command = 0;

void number_callback_command(const std_msgs::Int32 & msg){
    command_value = msg.data;
    received_command = 1;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "start");
    ros::NodeHandle node_obj;

    ros::Publisher command_publisher = node_obj.advertise<std_msgs::Int32>("command_num", 1);
    ros::Subscriber command_back = node_obj.subscribe("command_back", 1, number_callback_command);
    
    int command = -999; 
    std_msgs::Int32 msg_command;   

    std::cout  << std::endl << "Please enter command: ";
    std::cin >> command;

    if(command != -999){
	    msg_command.data = command;
	    command_publisher.publish(msg_command);
        command = -999;
    }

    while (ros::ok()){

        if(received_command == 1){

            std::cout << "Return Command Value:  " << command_value << std::endl;
            ros::Duration(0.5).sleep();
            received_command = 0;

            std::cout  << std::endl << "Please Enter Command: ";
            std::cin >> command;

            if(command != -999){
	            msg_command.data = command;
	            command_publisher.publish(msg_command);
                command = -999;
            }
	    }
        else{
            ros::spinOnce();
        }
    }
    return 0;
}
