#include<ros/ros.h>
//在learning_communication功能包下创建了AddTwoInts.msg,则应包含以下头文件
#include<learning_communication/AddTwoInts.h>

//service回调函数,输入参数req,输出参数res
bool add(learning_communication::AddTwoInts::Request &req
        learning_communication::AddTwoInts::Response &res
        )
{
    //将输入参数中的请求参数相加，结果放到应答变量中
    //res中包括sum一个成员
    //req中包括a,b两个成员
    res.sum = req.a + req.b;

    ROS_INFO("request: x = %ld, y = %ld",(long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.sum);
}

int main(int argc, char **argv)
{
    //ROS节点初始化
    ros::init(argc, argv, "add_two_ints_server");

    //创建节点句柄
    ros::NodeHandle n;

    //创建一个add_two_ints的server, 注册回调函数add()
    ros::ServiceServer service = n.advertiseService("add_two_ints", add);

    //循环等待回调函数
    ROS_INFO("Ready to add two ints.");
    ros::spin();

    return 0;
}
