
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int answer_left;
int received_left = 0;

void number_callback_left(const std_msgs::Int32 & msg2){
    answer_left = msg2.data;
    received_left = 1;
}

int answer_right;
int received_right = 0;

void number_callback_right(const std_msgs::Int32 & msg3){
    answer_right = msg3.data;
    received_right = 1;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "cp3");
    ros::NodeHandle node_obj;


    ros::Subscriber left_subscriber = node_obj.subscribe("left_back", 1, number_callback_left);
    ros::Subscriber right_subscriber = node_obj.subscribe("right_back", 1, number_callback_right);

    while (ros::ok()){
	
	    if(received_left == 1 && received_right == 1){
            std::cout << "Arduino received left power:  " << answer_left << std::endl;
            std::cout << "Arduino received right power:  " << answer_right << std::endl;

	    }
        else{
            ros::spinOnce();
        }
    }
    return 0;
}
