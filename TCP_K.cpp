#include <Winsock2.h>
#include <stdio.h>

int main(){
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );//加载套接字库
	if ( err != 0 ) { return 0; }
	if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ){
	WSACleanup( );
	return 0;
	}
	SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);//创建套接字（socket）。
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	//向服务器发出连接请求（connect）。
	char recvBuf[100];//和服务器端进行通信（send/recv）。
	recv(sockClient,recvBuf,100,0);
	printf("%s\n",recvBuf);
	send(sockClient,"This is blues_j",strlen("This is blues_j")+1,0);
	closesocket(sockClient);//关闭套接字。
	WSACleanup();//必须调用这个函数清除参数
}

