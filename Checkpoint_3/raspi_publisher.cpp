
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
#include <wiringPi.h>

int l_motor_cb;
int received_l_motor = 0;

int r_motor_cb;
int received_r_motor = 0;

int caught = 0;

int connected = 0;

std_msgs::Int32 msg_left_motor;
std_msgs::Int32 msg_right_motor;

void num_cb_r_motor(const std_msgs::Int32 & msg2){
    l_motor_cb = msg2.data;
    received_l_motor = 1;
}

void num_cb_l_motor(const std_msgs::Int32 & msg2){
    answer_touch = msg2.data;
    received_touch = 1;
}

void find_target(){
    while(digitalRead(11) == 0){
        left_motor_publisher.publish(80);
        right_motor_publisher.publish(-80);
    }
    
    left_motor_publisher.publish(0);
    right_motor_publisher.publish(0);

    std::cout << "I find the target !!!" << std::endl;
}

void catch_object(){
    while(digitalRead(7) == 0){
        left_motor_publisher.publish(100);
        right_motor_publisher.publish(100);
    }

    caught = 1;

    left_motor_publisher.publish(0);
    right_motor_publisher.publish(0);
}

int main(int argc, char **argv){

    wiringPiSetup();
    pinMode( 5, INPUT); //left touch sensor
    pinMode( 3, INPUT); //right touch sensor
    pinMode( 7, INPUT); //under touch sensor
    pinMode(11, INPUT); //light sensor

    ros::init(argc, argv, "cp3");
    ros::NodeHandle node_obj;

    ros::Publisher left_motor_publisher = node_obj.advertise<std_msgs::Int32>("left", 1);
    ros::Subscriber left_motor_subscriber = node_obj.subscribe("left_back", 1, num_cb_l_motor);

    ros::Publisher right_motor_publisher = node_obj.advertise<std_msgs::Int32>("right", 1);
    ros::Subscriber right_motor_subscriber = node_obj.subscribe("right_back", 1, num_cb_r_motor);

    while(ros::ok()){

        if(received_l_motor == 1 && received_r_motor == 1){
            std::cout << "Arduino received left power:  " << l_motor_cb << std::endl;
            std::cout << "Arduino received right power:  " << r_motor_cb << std::endl;
            
            connected = 1;
            received_l_motor = 0;
            received_r_motor = 0;
        }

        if(connected == 1){

            //both touch
            if(caught == 0 && (digitalRead(5) == 0) && (digitalRead(3) == 0)){

                std::cout << "OUCH !!!!!!!!!" << std::endl;
                find_target();
                catch_object();
            }
            
            // keep going forward if nothing detected
            if(caught == 0){
                left_motor_publisher.publish(100);
                right_motor_publisher.publish(100);
            }

            if(received_l_motor == 1){
                std::cout << "Arduino received left power:  " << l_motor_cb << std::endl;
                received_l_motor = 0;
            }

            if(received_r_motor == 1){
                std::cout << "Arduino received right power:  " << r_motor_cb << std::endl;
                received_r_motor = 0;
            }
        }
        else{
            ros::spinOnce();
        }
    }

    // ros::init(argc, argv, "cp2");
    // ros::NodeHandle node_obj;

    // ros::Publisher left_publisher = node_obj.advertise<std_msgs::Int32>("left", 1);
    // ros::Subscriber left_subscriber = node_obj.subscribe("left_back", 1, number_callback_left);

    // ros::Publisher right_publisher = node_obj.advertise<std_msgs::Int32>("right", 1);
    // ros::Subscriber right_subscriber = node_obj.subscribe("right_back", 1, number_callback_right);



    // int input_left = -1;
    // std_msgs::Int32 msg_left;

    // std::cout << "user's left input is ";
    // std::cin >> input_left;

    // if(input_left != -999){
	//     msg_left.data = input_left;
	//     left_publisher.publish(msg_left);
    // }

    // int input_right = -1;
    // std_msgs::Int32 msg_right;

    // std::cout << "user's right input is ";
    // std::cin >> input_right;

    // if(input_right != -999){
	//     msg_right.data = input_right;
	//     right_publisher.publish(msg_right);
    // }



    // while (ros::ok()){
	
	//     if(received_left == 1 && received_right == 1){
    //         std::cout << "Arduino received left power:  " << answer_left << std::endl;
    //         std::cout << "Arduino received right power:  " << answer_right << std::endl;

	//         received_left = 0;
    //         received_right = 0;

    //         int input_left = -1;
    //         std_msgs::Int32 msg_left;

    //         std::cout << "user's left input is ";
    //         std::cin >> input_left;

    //         if(input_left != -999){
    //             msg_left.data = input_left;
    //             left_publisher.publish(msg_left);
    //         }

    //         int input_right = -1;
    //         std_msgs::Int32 msg_right;

    //         std::cout << "user's right input is ";
    //         std::cin >> input_right;

    //         if(input_right != -999){
    //             msg_right.data = input_right;
    //             right_publisher.publish(msg_right);
    //         }
	//     }
    //     else{
    //         ros::spinOnce();
    //     }
    // }
    return 0;
}
