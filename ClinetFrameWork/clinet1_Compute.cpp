#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>

#include <WS2tcpip.h>
#define  STRLEN 1024
#define  PrintInfo(n) std::cout<<n<<std::endl;
void prinerrorMsg(const std::string& error) {
    std::cout << error;
}
bool checkOperation(const char &t) {
    if ( t=='*' || t=='/' || t=='+' || t=='-') {
        return true;
    }
    return false;
}


int main(int argc, char* argv[]) {
    WSADATA wsdata;
    SOCKET  hClntSock;
    SOCKADDR_IN clnAddr;
    int szClnetAddr;
    char msg[STRLEN];
     int res;
    // ����ı��ʽ
    int OperationNum = 0;
    std::vector<int> OperationContainer;// �洢������
    char Operation ;
    PrintInfo("�������������")
    std::cin >> OperationNum;

    OperationContainer.resize(OperationNum + 2);

    OperationContainer[0] = OperationNum;
   PrintInfo("���������������")
    for (auto i = 1 ;i<=OperationNum;i++) {

        std::cin>> OperationContainer[i];// cin  �Կո����
    }

    PrintInfo("�����������")
        std::cin >> Operation;
    while (!checkOperation(Operation)) {
        PrintInfo("���������Ϸ�,����������")
            std::cin >> Operation;
    }
    OperationContainer[OperationNum+1] = (int)Operation;

    if (argc != 3) {
        prinerrorMsg(" parameter  number wrong\n");
        return 0;
    }
    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        prinerrorMsg("error wsadata");
        return 0;
    }
    hClntSock = socket(PF_INET, SOCK_STREAM, 0);// ����һ���׽���
    if (hClntSock == INVALID_SOCKET) {
        prinerrorMsg("error hosck");
        return 0;
    }
    memset(&clnAddr, 0, sizeof(clnAddr));
    clnAddr.sin_family = AF_INET;// IPV4
    inet_pton(AF_INET, argv[1], &clnAddr.sin_addr.S_un.S_addr);
    clnAddr.sin_port = htons(atoi(argv[2]));// Host to NetWork ��С�˵�ת��ģʽ

    if (connect(hClntSock, (SOCKADDR*)&clnAddr, sizeof(clnAddr)) == SOCKET_ERROR) {
        prinerrorMsg("connect error");
    }
    // ����������ĸ���
    auto sendDataEdge = send(hClntSock,(char*)OperationNum,4,0);
   
    //this_thread::sleep_for(std::chrono::seconds(1));
    // ���ȴ�������ĸ���
    auto sendData = send(hClntSock,(char*)OperationContainer.data(),(OperationContainer.size())*4,0);

    int strlen = 0;
    while (1) {
        strlen = recv(hClntSock, (char*)&res, 4, 0);
        if (strlen!=0 || strlen!=-1) {
          break;
        }
    }
    std::cout <<"result: " << msg; //���
 
    closesocket(hClntSock);
    WSACleanup();
    return 0;
}