#include<cstdlib>
#include<ros/ros.h>
#include<learning_communication/AddTwoInts.h>

//定义的消息的类型为
//int64 a
//int64 b
//---
//int64 sum

int main(int argc, char **argv)
{
    //ROS节点初始化
    ros::init(argc, argv, "add_two_ints_client");

    //从终端命令行中获取两个相加数
    if (argc != 3)
    {
        ROS_INFO("usage: add_two_ints_client X Y");
        return 1;
    }

    //创建节点句柄
    ros::NodeHandle n;

    //创建一个client, 请求add_two_int service
    //service消息类型是learning_communication::AddTwoInts
    ros::serviceClient client = n.serviceClient<learning_communication::AddTwoInts>("add_two_ints");

    //创建learning_communication::AddTwoInts类型的service消息
    learning_communication::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    //发布service请求,等待加法运算的应答结果
    if (client.call(srv))
    {
        ROS_INFO("sum: %ld", (long int)srv.response.sum);
    }
    else
    {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }

    return 0;
}
