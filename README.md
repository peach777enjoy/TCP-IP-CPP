# 先读我

## 1. 运行 Demo 需以下步骤
1. 电脑可用网线连接控制器的网口，然后设置固定 IP，与控制器 IP 在同一网段下。也可无线连接控制器。

   - 四轴机器人（如MG400等）     有线连接时连接LAN1：ip为192.168.1.6 , 有线连接时连接LAN2：ip为192.168.2.6
   - 六轴机器人（如CR系列等）    有线连接：ip为192.168.5.1 , 无线连接：ip为192.168.1.6
  
2. 尝试 ping 通控制器 IP，确保在同一网段下。

## 2. 文件说明

所有文件都可根据机器人TCP/IP远程控制方案（https://github.com/Dobot-Arm/TCP-IP-Protocol）自行修改。

1. Demo.cpp:             main() 程序入口，为主要流程。

2. RealTimeData.h/cpp:   实时反馈数据的数据结构，打印实时反馈数据。
   
3. SocketUtils.h/cpp:    对tcp通讯的基本操作（连接、断开、收发数据等），与dobot通讯的相关指令进行封装。

4. CMakeLists.txt:       cmake 生成makefile的配置文件。

   

## 3. 测试环境
1. Windows 测试环境
   - os: Windows 10 64-bit
   - cmake: 官网发布版本即可
   - gcc: x86_64 posix
   - ide: VSCode
  

2. Ubuntu 测试环境
   - os: Ubuntu 20.04 desktop 64-bit
   - cmake: 官网发布版本即可
   - gcc: x86_64_linux_gnu
   - ide: VSCode


---


# Readme

## 1. The following steps are required to run Demo
1. The computer can be connected to the network port of the controller with a network cable, and then set a fixed IP, which is in the same network segment as the controller IP. The controller can also be connected wirelessly.

    - Four-axis robot (such as MG400, etc.) When wired connection, connect to LAN1: ip is 192.168.1.6 , When wired connection, connect to LAN2: ip is 192.168.2.6 .
    - Six-axis robot (such as CR series, etc.) Wired connection: ip is 192.168.5.1 ,Wireless connection: ip is 192.168.1.6 .

2. Try to ping the controller IP to make sure it is in the same network segment.


## 2. File description
All files can be modified according to the robot TCP/IP remote control scheme (https://github.com/Dobot-Arm/TCP-IP-Protocol).

1. Demo.cpp: main() program entry, which is the main process.

2. RealTimeData.h/cpp: Data structure of real-time feedback data, print real-time feedback data.
   
3. SocketUtils.h/cpp: encapsulate the basic operations of tcp communication (connect, disconnect, send and receive data, etc.), and related instructions for dobot communication.

4. CMakeLists.txt: cmake generates the configuration file of the makefile.


## 3. Test environment
1. Windows test environment
    -os: Windows 10 64-bit
    -cmake: Just publish the version on the official website
    -gcc: x86_64 posix
    -ide: VSCode
  
  
2. Ubuntu test environment
    -os: Ubuntu 20.04 desktop 64-bit
    -cmake: Just publish the version on the official website
    -gcc: x86_64_linux_gnu
    -ide: VSCode