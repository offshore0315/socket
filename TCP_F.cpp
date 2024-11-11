#include <Winsock2.h>//加裁头文件
#include <stdio.h>//加载标准输入输出头文件
int main()
{
	WORD wVersionRequested;//版本号
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );//1.1版本的套接字
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) { return 0; }//加载套接字库，加裁失败则返回
	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ){
		WSACleanup( );
		return 0;
	}//如果不是1.1的则退出
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);//创建套接字（socket）。
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//转换Unsigned short为网络字节序的格式 
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)); 
	//将套接字绑定到一个本地地址和端口上（bind） listen(sockSrv,5);
	//将套接字设为监听模式，准备接收客户请求（listen）。
	SOCKADDR_IN addrClient;//定义地址族
	int len=sizeof(SOCKADDR);//初始化这个参数，这个参数必须被初始化
	while(1){
	SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
	//accept的第三个参数一定要有初始值。
	//等待客户请求到来；当请求到来后，接受连接请求，
	//返回一个新的对应于此次连接的套接字（accept）。 
	//此时程序在此发生阻塞
	char sendBuf[100];
	sprintf(sendBuf,"Welcome %s to www.msn.com.cn",inet_ntoa(addrClient.sin_addr)); 
	//用返回的套接字和客户端进行通信（send/recv）。
	send(sockConn,sendBuf,strlen(sendBuf)+1,0);
	char recvBuf[100];
	recv(sockConn,recvBuf,100,0);
	printf("%s\n",recvBuf);
	closesocket(sockConn);//关闭套接字。等待另一个用户请求
	}
}

