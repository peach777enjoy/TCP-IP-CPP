
#include <iostream>
#include <string.h>
#include <vector>
#include <WinSock.h>
#pragma comment(lib, "ws2_32.lib")
using std::string;

class TCPClient {
public:
    TCPClient();
    ~TCPClient();
    int ConnectServer(const char* ip, int port, uint32_t blockTimeMs = 1000);
    int SendData(const char* bufSend);
    int RecvData(char* bufRev, uint32_t bufSize = 1024, uint32_t timeOutMs = 1000);
    int SendAndRecvData(const char *bufSend, char * bufRev, uint32_t bufSize = 1024, uint32_t revTimeOutMs = 1000);
    int Close();


    int EnableRobot();
    int DisableRobot();
    int ClearError();
    int ResetRobot();
    int SpeedFactor(int speed);
    int User(int index);
    int Tool(int index);
    int RobotMode();
    int PayLoad(float weight, float inertia);
    int DO(int index, int val);
    int DOExecute(int index, int val);
    int ToolDO(int index, int val);
    int ToolDOExecute(int index, int val);
    int AO(int index, int val);
    int AOExecute(int index, int val);
    int AccJ(int speed);
    int AccL(int speed);
    int SpeedJ(int speed);
    int SpeedL(int speed);
    int Arch(int index);
    int CP(int ratio);
    int LimZ(int value);
    int SetArmOrientation(int r, int d, int n, int cfg);
    int PowerOn();
    int RunScript(char *project_name);
    int StopScript();
    int PauseScript();
    int ContinueScript();
    int GetHoldRegs(int id, int addr, int count, int type);
    int SetHoldRegs(int id, int addr, int count, int table, int type);
    int SetSafeSkin(int status);
    int SetObstacleAvoid(int status);
    int GetTraceStartPose(string traceName, float &x, float &y, float &z, float &a, float &b, float &c);
    int GetPathStartPose(string traceName, float &j1, float &j2, float &j3, float &j4, float &j5, float &j6);
    int PositiveSolution(float j1, float j2, float j3, float j4, float j5, float j6);
    int InverseSolution(float x, float y, int z, float a, float  b, float c);
    int SetCollisionLevel(int level);
    int HandleTrajPoints(string traceName);
    int GetSixForceData();
    int GetAngle();
    int GetPose();
    int EmergencyStop();
    int Sync();

    int MovJ(float j1, float j2, float j3, float j4, float j5, float j6);
    int MovL(float x, float y, int z, float a, float  b, float c);
    int JointMovJ(float j1, float j2, float j3, float  j4, float j5, float j6);
    int Jump();
    int RelMovJ(float offset1, float offset2, float offset3, float offset4, float offset5, float offset6);
    int RelMovL(float offsetX, float offsetY, float offsetZ);
    int MovLIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize);
    int MovJIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize);
    int Arc(float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2);
    int Circle(int count, float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2);
    int ServoJ(float j1, float j2, float j3, float j4, float j5, float j6);
    int ServoP(float j1, float j2, float j3, float j4, float j5, float j6);
    int MoveJog(string axisID);
    int StartTrace(string traceName);
    int StartPath(string traceName, int isConst, int cart);
    int StartFCTrace(string traceName);

private:
    WSADATA wsaData;
    SOCKADDR_IN addrSrv;
    SOCKET sockClient;
};