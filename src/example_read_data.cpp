#include <string>
#include <iostream>
#include <cstdio>
#include <scn/scan.h>
// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"
#include "ros/ros.h"
#include "geometry_msgs/Vector3Stamped.h"

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

void my_sleep(unsigned long milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds); // 100 ms
#else
    usleep(milliseconds * 1000); // 100 ms
#endif
}

int run(int argc, char **argv)
{
    // port, baudrate, timeout in milliseconds
    
    while (true)
    {
        
    }
    return 0;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "serial_listener");
    ros::NodeHandle nh;
    ros::Publisher vector3_pub = nh.advertise<geometry_msgs::Vector3Stamped>("serial_vec3", 1000);
    ros::Rate loop_rate(10);

    int last_index = 0;

    serial::Serial my_serial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(10)); // 10ms timeout
    cout << "Is the serial port open?";
    if (my_serial.isOpen())
        cout << " Yes." << endl;
    else
    {
        cout << " No." << endl;
        return -1;
    }

    geometry_msgs::Vector3Stamped vec3_msg;
    vec3_msg.header.frame_id = "measured_point";
    vec3_msg.header.stamp = ros::Time::now();
    vec3_msg.vector.x = 0;
    vec3_msg.vector.y = 0;
    vec3_msg.vector.z = 0;

    while (ros::ok())
    {
        string result = my_serial.read(100);
        if (result.length() == 0)
        {
            ROS_WARN_THROTTLE(1, "No data available");
        }
        else if (auto parse_result = scn::scan<int, double, double, double>(result, "{}_{}_{}_{}\r\n"))
        {
            auto [a, b, c, d] = parse_result->values();
            if (a == last_index)
            {
                ROS_WARN_THROTTLE(1, "Data is the same as last time");
            }
            else if (a != last_index + 1)
            {
                ROS_WARN_THROTTLE(1, "Data is not consecutive");
            }
            cout << "Index = " << a << ", X = " << b << ", Y = " << c << ", Z = " << d << endl;
            vec3_msg.header.stamp = ros::Time::now();
            vec3_msg.vector.x = b;
            vec3_msg.vector.y = c;
            vec3_msg.vector.z = d;
            vector3_pub.publish(vec3_msg);
            last_index = a;
        }
        else
        {
            ROS_WARN_THROTTLE(1, "Data available but could not parse it");
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
