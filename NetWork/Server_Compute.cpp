#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <string>
#include <WS2tcpip.h>
#include <vector>
void prinerrorMsg(const std::string& error) {
    std::cout << error;
}

int compute(const std::vector<int> &data) {
  if (data.size()<3) {
    return -1;
  }
  auto len = data.size();
  char Oper =(char) data[len-1];
  int res = 0;
  switch (Oper) {
    case '+':  
    for(const auto & iter : data) {
      res +=iter;
    }
    return res;
    case '-':  
        for (const auto& iter : data) {
            res -= iter;
        }
        return res;
    case '*':  
        for (const auto& iter : data) {
            res *= iter;
        }
        return res;
    case '/':  
      break; // 暂时不支持除法
    default:
      break;
  }
  return -1;
}


int main(int argc, char* argv[]) {
    WSADATA wsdata;
    SOCKET hserSock, hClntSock;
    SOCKADDR_IN serAddr, clnAddr;
    int szClnetAddr;

    // 计算的数据边界
    int OperationNum;
    std::vector<int> OperationContainer;
    char msg[] = "hello ";
    if (argc != 3) {
        prinerrorMsg(" parameter  number wrong\n");
        return 0;
    }
    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        prinerrorMsg("error wsadata");
        return 0;
    }
    hserSock = socket(PF_INET, SOCK_STREAM, 0);// 申请一个套接字
    if (hserSock == INVALID_SOCKET) {
        prinerrorMsg("error hosck");
        return 0;
    }
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;// IPV4
    serAddr.sin_port = htons(atoi(argv[2]));// Host to NetWork 大小端的转换模式
    serAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, argv[1], &clnAddr.sin_addr);
    if (bind(hserSock, (SOCKADDR*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
        prinerrorMsg("Error Bind");
        return 0;
    }
    if (listen(hserSock, 5) == SOCKET_ERROR) {
        prinerrorMsg("Error Listen");
        return 0;
    }
    szClnetAddr = sizeof(clnAddr);
    hClntSock = accept(hserSock, (SOCKADDR*)&clnAddr, &szClnetAddr);// 接受客户端链接请求
    if (hClntSock == SOCKET_ERROR) {
        prinerrorMsg("error accept");
        // return 0;
    }
    if (auto stelen = recv(hClntSock, (char*)&OperationNum,4,0)==-1) {
        prinerrorMsg("rev error");
    }
    OperationContainer.resize(OperationNum+1);
    int recvlen= 0;
    int totalLen =0;
    while (1) {
        recvlen = recv(hClntSock, (char*)(OperationContainer.data())+totalLen, 1, 0); // (OperationContainer.size() + 1 ) - totalLen/4
        if (recvlen == 0 || recvlen == -1) {
            prinerrorMsg("recv error");
            continue;
        } 
        totalLen += recvlen;
        if (totalLen >=(OperationNum+1)*4 ) {
            break;
        }
       
    }
    auto res = compute(OperationContainer);
    send(hClntSock, (char*)&res, 4, 0);
    closesocket(hClntSock);// 没有发出去就断开了
    closesocket(hserSock);
    WSACleanup();
    return 0;
}