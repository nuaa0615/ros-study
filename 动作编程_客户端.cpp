#include<actionlib/client/simple_action_client.h>
#include<learnning_communication/DoDishesAction.h>

//定义的动作消息为：
//uint32 dishwasher_id#定义目标
//---
//uint32 total_dishes_cleaned#定义结果
//--
//float32 percent_complete#定义反馈

typedef actionlib::SimpleActionClient<learnning_communication::DoDishesAction> Client;

//当action完成后会调用该回调函数一次
void doneCB(const actionlib::SimpleActionClientGoalState& state,
            const learnning_communication::DoDishesActionResultConstPtr& result)
{
    ROS_INFO("Yay! The dishes are now clean");
    ros::shutdown();
}

//当action激活后调用该回调函数一次
void activeCB()
{
    ROS_INFO("goal just went active");
}

//当收到feedback后调用该回调函数
void feedbackCB(const learnning_communication::DoDishesFeedbackConstPtr& feedback)
{
    ROS_INFO("percent_complete : %f", feedback->percent_complete);
}

int int main (int argc, char const* argv[])
{
    ros::init (argc, argv,"do_dishes_client" );

    //定义一个客户端
    Client client("do_dishes", true);

    //等待服务器
    ROS_INFO("Waiting for aaction server to start");
    client.waitForServer();
    ROS_INFO("action server started, send goal");

    //创建一个action的goal
    learnning_communication::DoDishesGoal goal;
    goal.dishwasher_id = 1;

    //发送action的goal给服务器，并设置回调函数
    client.sendGoal(goal, &doneCB, &activeCB, &feedbackCB);

    ros::spin();

    return 0;
}
