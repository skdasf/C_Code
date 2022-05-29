#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string>
#include <WS2tcpip.h>
void prinerrorMsg(const std::string &error){
    std::cout<< error;
}

int main(int argc, char* argv[]){
    WSADATA wsdata;
    SOCKET hserSock,hClntSock;
    SOCKADDR_IN serAddr,clnAddr;
    int szClnetAddr;
    char msg [] = "hello ";
    if (argc!=3) {
        prinerrorMsg(" parameter  number wrong\n");
         return 0;
    }
    if (WSAStartup(MAKEWORD(2,2),&wsdata)!=0) {
        prinerrorMsg("error wsadata");
        return 0;
    }
    hserSock = socket(PF_INET,SOCK_STREAM,0);// 申请一个套接字
    if (hserSock == INVALID_SOCKET) {
        prinerrorMsg("error hosck");
        return 0;
    }
     auto test = argv[2];
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family = AF_INET;// IPV4
    serAddr.sin_port = htons(atoi(argv[2]));// Host to NetWork 大小端的转换模式
    serAddr.sin_addr.S_un.S_addr= htonl(INADDR_ANY);
   // inet_pton(AF_INET, argv[1], &clnAddr.sin_addr);
    if (bind(hserSock,(SOCKADDR*)&serAddr,sizeof(serAddr))==SOCKET_ERROR) {
        prinerrorMsg("Error Bind");
        return 0;
    }
    if (listen(hserSock,5)==SOCKET_ERROR){
        prinerrorMsg("Error Listen");
        return 0;
    }
    szClnetAddr = sizeof(clnAddr);
    hClntSock = accept(hserSock,(SOCKADDR*)&clnAddr,&szClnetAddr);// 接受客户端链接请求
    if (hClntSock == SOCKET_ERROR){
        prinerrorMsg("error accept");
       // return 0;
    }
    send(hClntSock,msg,sizeof(msg),0);
    closesocket(hClntSock);
    closesocket(hserSock);
    WSACleanup();
    return 0;
}