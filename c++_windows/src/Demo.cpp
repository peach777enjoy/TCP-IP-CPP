#include <iostream>
#include <thread>
#include <mutex>
#include "SocketUtils.h"
#include "RealTimeData.h"
using namespace std;

volatile bool flag = true;
mutex mtx;

void dashboard(TCPClient *clientDashboard, TCPClient *clientFeedback){
    clientDashboard->ClearError();
    clientDashboard->EnableRobot();
    Sleep(6000);
    clientDashboard->User(0);
    clientDashboard->Tool(0);
    clientFeedback->JointMovJ(0,60,0,0,0,0);
    Sleep(8000);
    clientFeedback->JointMovJ(0,30,0,0,0,0);
    Sleep(8000);

    mtx.lock();
    flag = false;
    mtx.unlock();
}

void feedback(TCPClient *clientFeedback){
    char *buf = (char*)malloc(2048*sizeof(char));
    RealTimeData_t pack;
    RealTimeData_t *p = &pack;
    int ret;
    uint64_t temp;
    uint8_t *p_temp = (uint8_t*)(&temp);

    while(true){
        Sleep(50);
        mtx.lock();
        if (flag){
            ret = clientFeedback->RecvData(buf,1440); 
            memcpy(&pack,buf,sizeof(pack));
            memcpy(&temp,buf+48,sizeof(uint64_t));
            printf("ret = %d\n",ret);
            if(ret > 0 ){      
                //dump_hex(buf,sizeof(RealTimeData_t));     
                printf("0x%016llx\n",temp);   
                if(temp!=0x123456789abcdef){
                    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                    mtx.unlock();
                    continue;
                }
                
                // printf("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n",
                //     buf[48],buf[49],buf[50],buf[51],
                //     buf[52],buf[53],buf[54],buf[55]);                        
                printf("%02x %02x %2x %02x %02x %02x %02x %02x\n",
                    p_temp[0],p_temp[1],p_temp[2],p_temp[3],
                    p_temp[4],p_temp[5],p_temp[6],p_temp[7]);
                //print_params(&pack);
            } else {
                perror("recv err");
            }
            mtx.unlock();

        } else {
            mtx.unlock();
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    TCPClient *tcpDashboard = new TCPClient();
    TCPClient *tcpFeedback = new TCPClient();
    if(tcpDashboard->ConnectServer("192.168.5.1", 29999) < 0){
        return -1;
    }
    if(tcpFeedback->ConnectServer("192.168.5.1", 30003) < 0){
        return -2;
    }

    thread thread1(feedback, tcpFeedback);
    thread thread2(dashboard, tcpDashboard, tcpFeedback);
    thread1.join();
	thread2.join();
    tcpDashboard->Close();
    tcpFeedback->Close();
    return 0;
}
