#include "SocketUtils.h"
#include <sstream>
using std::stringstream;

TCPClient::TCPClient(){
    //load socket
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock");
    }
    //create socket
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == sockClient){
        printf("Socket() error:%d", WSAGetLastError());
    }
    memset(&addrSrv, 0, sizeof(addrSrv));
}

TCPClient::~TCPClient(){
    Close();
}

int TCPClient::ConnectServer(const char* ip, int port, uint32_t blockTimeMs){
    memset(&addrSrv, 0, sizeof(addrSrv));
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);

    struct timeval timev;
    timev.tv_sec   = (long)blockTimeMs/1000;
    timev.tv_usec  = (long)(blockTimeMs%1000) * 1000;
    if (setsockopt(sockClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&timev, sizeof(struct timeval)) != 0){
        perror("[TCPClient::ConnectServer] :");
        return -3;
    }
    //make a connection request to the server
    if (connect(sockClient, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR){
        printf("Connect failed:%d", WSAGetLastError());
        return -4;
    }
    return 0;
}

int TCPClient::SendData(const char* bufSend){
    int ret = send(sockClient, bufSend, strlen(bufSend), 0);
    if (-1 == ret){
        printf("send failed:%d\n", WSAGetLastError());
        return -1;
    }
    printf("send -> %s %d\n", bufSend, ret);
    return ret;
}
  
int TCPClient::RecvData(char* bufRev, uint32_t bufSize, uint32_t timeOutMs){
    timeval timev = {(long)timeOutMs/1000, (long)(timeOutMs%1000) * 1000};        
    if (setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&timev, sizeof(struct timeval)) != 0){
        printf("[TCPClient::Recvdata] set time out faild!!!!!  \n");
        return -2;
    }  
    int ret = recv(sockClient, bufRev, bufSize, 0);
    if (-1 == ret){
        printf("recv failed:%d\n", WSAGetLastError());
        return -1;
    }
    printf("rec <- %s %d\n", bufRev, ret);
    return ret;
}

int TCPClient::SendAndRecvData(const char *bufSend, char * bufRev, uint32_t bufSize, uint32_t revTimeOutMs){
    int sendRet = SendData(bufSend);
    if(sendRet < 0){
        printf("sendAndRecv failed:%d\n", WSAGetLastError());
        return -2;
    }
    Sleep(500);
    int recvRet = RecvData(bufRev, bufSize, revTimeOutMs);
    if(recvRet < 0){
        printf("sendAndRecv failed:%d\n", WSAGetLastError());
        return -1;
    }
    return recvRet;
}
    
int TCPClient::Close(){
    if(-1 == closesocket(sockClient)){
        printf("close failed:%d\n", WSAGetLastError());
        return -1;
    }
    if(-1 == WSACleanup()){
        printf("WSACleanUp failed:%d\n", WSAGetLastError());
        return -2;
    }
    return 0;
}

int TCPClient::EnableRobot(){
    const char* t = "EnableRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::DisableRobot(){
    const char* t = "DisableRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ClearError(){
    const char* t = "ClearError()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ResetRobot(){
    const  char* t = "ResetRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::SpeedFactor(int speed){
    stringstream fmt;                       
    fmt << "SpeedFactor(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::User(int index){
    stringstream fmt;                       
    fmt << "User(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::Tool(int index){
    stringstream fmt;                       
    fmt << "Tool(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::RobotMode(){
    const char* t = "RobotMode()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::PayLoad(float weight, float inertia){
    stringstream fmt;                       
    fmt << "PayLoad(" << weight << "," << inertia << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::DO(int index, int val){
    stringstream fmt;                       
    fmt << "DO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::DOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "DOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::ToolDO(int index, int val){
    stringstream fmt;                       
    fmt << "ToolDO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::ToolDOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "ToolDOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AO(int index, int val){
    stringstream fmt;                       
    fmt << "AO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "AOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AccJ(int speed){
    stringstream fmt;                       
    fmt << "AccJ(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AccL(int speed){
    stringstream fmt;                       
    fmt << "AccL(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SpeedJ(int speed){
    stringstream fmt;                       
    fmt << "SpeedJ(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SpeedL(int speed){
    stringstream fmt;                       
    fmt << "SpeedL(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::Arch(int index){
    stringstream fmt;                       
    fmt << "Arch(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::CP(int ratio){
    stringstream fmt;                       
    fmt << "CP(" << ratio << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::LimZ(int value){
    stringstream fmt;                       
    fmt << "LimZ(" << value << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SetArmOrientation(int r, int d, int n, int cfg){
    stringstream fmt;                       
    fmt << "SetArmOrientation(" << r << "," << d << "," << n << "," << cfg << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::PowerOn(){
    const char* t = "PowerOn()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::RunScript(char *project_name){
    printf("%s\n", project_name);
    char bufRev[1024] = {0};
    return SendAndRecvData(project_name, bufRev);
}

int TCPClient::StopScript(){
    const char* t = "StopScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::PauseScript(){
    const char* t = "PauseScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ContinueScript(){
    const char* t = "ContinueScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::GetHoldRegs(int id, int addr, int count, int type){
    stringstream fmt;                       
    fmt << "GetHoldRegs(" << id << "," << addr << "," << count << "," << type << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SetHoldRegs(int id, int addr, int count, int table, int type){
    stringstream fmt;                       
    fmt << "SetHoldRegs(" << id << "," << addr << "," << count << "," << table << "," << type << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}


int TCPClient::MovJ(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "MovJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovL(float x, float y, int z, float a, float  b, float c){
    stringstream fmt;                       
    fmt << "MovL(" << x << "," << y << "," << z << "," << a << "," << b << "," << c << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::JointMovJ(float j1, float j2, float j3, float  j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "JointMovJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Jump(){
    stringstream fmt;                       
    fmt << "Jump(" << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::RelMovJ(float offset1, float offset2, float offset3, float offset4, float offset5, float offset6){
    stringstream fmt;                       
    fmt << "RelMovJ(" << offset1 << "," << offset2 << "," << offset3 << "," << offset4 << "," << offset5 << "," << offset6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::RelMovL(float offsetX, float offsetY, float offsetZ){
    stringstream fmt;                       
    fmt << "RelMovL(" << offsetX << "," << offsetY << "," << offsetZ << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovLIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize){
    stringstream fmt;                       
    fmt << "MovLIO(" << x << "," << y << "," << z << "," << a << "," << b << "," << c;
    for(int i=0; i< rowSize; i++) {
        fmt << ",{" << dynArrayIO[i][0] << "," << dynArrayIO[i][1] << "," << dynArrayIO[i][2] << "," << dynArrayIO[i][3] << "}";
    }
    fmt << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovJIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize){
    stringstream fmt;                       
    fmt << "MovJIO(" << x << "," << y << "," << z << "," << a << "," << b << "," << c;
     for(int i=0; i< rowSize; i++) {
        fmt << ",{" << dynArrayIO[i][0] << "," << dynArrayIO[i][1] << "," << dynArrayIO[i][2] << "," << dynArrayIO[i][3] << "}";
    }
    fmt << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Arc(float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2){
    stringstream fmt;                       
    fmt << "Arc(" << x1 << "," << y1 << "," << z1 << "," << a1 << "," << b1 << "," << c1
                    << x2 << "," << y2 << "," << z2 << "," << a2 << "," << b2 << "," << c2 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Circle(int count, float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2){
    stringstream fmt;                       
    fmt << "Circle(" << count << x1 << "," << y1 << "," << z1 << "," << a1 << "," << b1 << "," << c1
                            << x2 << "," << y2 << "," << z2 << "," << a2 << "," << b2 << "," << c2 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::ServoJ(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "ServoJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::ServoP(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "ServoP(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}