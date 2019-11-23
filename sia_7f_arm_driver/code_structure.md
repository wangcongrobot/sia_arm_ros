# 代码结构

建议按照功能将代码划分为不同层次的结构，并封装成类，该包可以分为三个C++类：

1. 机械臂

- robot_abstract.h 数据结构：可以声明一个类，包含机械臂相关的数据类型，并在构造函数里附初值
- motion_planner.h 函数应包括与串口直接的通讯功能
- motion_planner.cpp 

2. 串口通讯

- 功能结构
  - 接收与发送
  - 解析与打包

- 文件结构
  - serial_data.h 通讯协议，封装一个类，一个.h文件即可
  - serial.h 类声明
  - serial.cp 类定义

3. ROS相关
- sia_7f_arm_ros.h
- sia_7f_arm_ros.cpp


ros package的命名规则可以参考[ur ros](https://github.com/ros-industrial/universal_robot)