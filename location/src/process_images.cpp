
#include "ros/ros.h"
#include "location/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <ostream>

// Define a global client that can request services
ros::ServiceClient client;
bool moving_state = false;

// This function calls the command_robot service to drive the robot in the specified direction

/*$ rosservice call /location/command_robot "linear_x: 0.5
angular_z: 0.0"  # This request should drive your robot forward

$ rosservice call /location/command_robot "linear_x: 0.0
angular_z: 0.5"  # This request should drive your robot left

$ rosservice call /location/command_robot "linear_x: 0.0
angular_z: -0.5"  # This request should drive your robot right

$ rosservice call /location/command_robot "linear_x: 0.0
angular_z: 0.0"  # This request should bring your robot to a complete stop*/


void drive_robot(float lin_x, float ang_z)
{
    location::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    // TODO: Request a service and pass the velocities to it to drive the robot
    if(!client.call(srv))
    {
        ROS_ERROR("Failed to call command_robot service .");
    }
    ROS_INFO_STREAM("Run correct !");

}


// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image& img) {
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    int white_pixel = 255;
    bool pixel_is_white = false;
    for (int row = 0; row < img.height; row++) {
        for (int column = 0; column < img.width; column++) {
            int red = img.data[row * img.step + column * 3];
            int green = img.data[row * img.step + column * 3 + 1];
            int blue = img.data[row * img.step + column * 3 + 2];

            if (red == 255 && green == 255 && blue == 255) {
                pixel_is_white = true;
                ROS_INFO_STREAM("there is a white ball! ");

                int ball_column = column;
                // left
                ROS_INFO_STREAM("white's colum " << column);

                if (ball_column < 200) {
                    ROS_INFO_STREAM("turn left");
                    drive_robot(0.0, 0.5);
                }

                    // right
                else if (ball_column > 500) {
                    ROS_INFO_STREAM("turn right");
                    drive_robot(0.0, -0.5);
                }

                drive_robot(0.5, 0);
                return;
            }
        }
    }
    if (!pixel_is_white){
        drive_robot(0.0, 0.0);
        drive_robot(0.0, -1.0);
        return;
    }
}
    // Then, identify if this pixel falls in the left, mid, or right side of the image

    // Depending on the white ball position, call the drive_bot function and pass velocities to it

    // Request a stop when there's no white ball seen by the camera


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<location::DriveToTarget>("/location/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 5, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

