
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
    ros::init(argc, argv, "cp2");
    ros::NodeHandle node_obj;

    ros::Publisher left_publisher = node_obj.advertise<std_msgs::Int32>("left", 1);
    ros::Subscriber left_subscriber = node_obj.subscribe("left_back", 1, number_callback_left);

    ros::Publisher right_publisher = node_obj.advertise<std_msgs::Int32>("right", 1);
    ros::Subscriber right_subscriber = node_obj.subscribe("right_back", 1, number_callback_right);



    int input_left = -1;
    std_msgs::Int32 msg_left;

    std::cout << "user's left input is ";
    std::cin >> input_left;

    if(input_left != -999){
	    msg_left.data = input_left;
	    left_publisher.publish(msg_left);
    }

    int input_right = -1;
    std_msgs::Int32 msg_right;

    std::cout << "user's right input is ";
    std::cin >> input_right;

    if(input_right != -999){
	    msg_right.data = input_right;
	    right_publisher.publish(msg_right);
    }



    while (ros::ok()){
	
	    if(received_left == 1 && received_right == 1){
            std::cout << "Arduino received left power:  " << answer_left << std::endl;
            std::cout << "Arduino received right power:  " << answer_right << std::endl;

	        received_left = 0;
            received_right = 0;

            int input_left = -1;
            std_msgs::Int32 msg_left;

            std::cout << "user's left input is ";
            std::cin >> input_left;

            if(input_left != -999){
                msg_left.data = input_left;
                left_publisher.publish(msg_left);
            }

            int input_right = -1;
            std_msgs::Int32 msg_right;

            std::cout << "user's right input is ";
            std::cin >> input_right;

            if(input_right != -999){
                msg_right.data = input_right;
                right_publisher.publish(msg_right);
            }
	    }
        else{
            ros::spinOnce();
        }
    }
    return 0;
}
