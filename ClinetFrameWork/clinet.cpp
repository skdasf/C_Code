#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string>
#include <WS2tcpip.h>
#define  STRLEN 1024
void prinerrorMsg(const std::string& error) {
    std::cout << error;
}

int main(int argc, char* argv[]) {
    WSADATA wsdata;
    SOCKET  hClntSock;
    SOCKADDR_IN clnAddr;
    int szClnetAddr;
    char msg[STRLEN];
    if (argc != 3) {
        prinerrorMsg(" parameter  number wrong\n");
        return 0;
    }
    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        prinerrorMsg("error wsadata");
        return 0;
    }
    hClntSock = socket(PF_INET, SOCK_STREAM, 0);// 申请一个套接字
    if (hClntSock == INVALID_SOCKET) {
        prinerrorMsg("error hosck");
        return 0;
    }
    memset(&clnAddr, 0, sizeof(clnAddr));
    clnAddr.sin_family = AF_INET;// IPV4
    auto test = argv[1];
    auto test2 = argv[2];
    inet_pton(AF_INET,argv[1],&clnAddr.sin_addr.S_un.S_addr);
    clnAddr.sin_port = htons(atoi(argv[2]));// Host to NetWork 大小端的转换模式
   
   if (connect(hClntSock,(SOCKADDR*)&clnAddr,sizeof(clnAddr)) == SOCKET_ERROR) {
        prinerrorMsg("connect error");
   }
   auto strlen =  recv(hClntSock, msg, sizeof(msg), 0);
   if (strlen == -1) {
    prinerrorMsg("recv error");
   } else {
   std::cout<<msg;
   }
    closesocket(hClntSock);
    WSACleanup();
    return 0;
}