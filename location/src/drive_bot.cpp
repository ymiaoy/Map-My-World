#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "location/DriveToTarget.h"

ros::Publisher motor_command_publisher;

geometry_msgs::Twist getVelocity(float req_linear_x, float req_angular_z)
{


    geometry_msgs::Twist msg;
    msg.linear.x = req_linear_x;
    msg.angular.z = req_angular_z;
    ROS_INFO_STREAM("the velocity data is : ");
    return msg;

}



bool handle_drive_request(location::DriveToTarget::Request& req, location::DriveToTarget::Response& res)
{
    ROS_INFO("DriveToTarget Request received: linear_x:%1.2f, angular_z:%1.2f ", (float)req.linear_x, (float)req.angular_z);

    geometry_msgs::Twist wheel_velocity = getVelocity(req.linear_x, req.angular_z);

    geometry_msgs::Twist robot_msg;
    robot_msg.linear.x = wheel_velocity.linear.x;
    robot_msg.angular.z = wheel_velocity.angular.z;



    motor_command_publisher.publish(robot_msg);

    ros::Duration(1).sleep();
    res.msg_feedback = "wheel linear set - linear_x: " + std::to_string(robot_msg.linear.x) + " , angular_z: " + std::to_string(robot_msg.angular.z);
    ROS_INFO_STREAM(res.msg_feedback);


    return true;


}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;

    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    ros::ServiceServer server = n.advertiseService("/location/command_robot", &handle_drive_request);

    ROS_INFO("ready to send command: ");


    ros::spin();



}











