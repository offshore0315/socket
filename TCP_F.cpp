#include <Winsock2.h>//�Ӳ�ͷ�ļ�
#include <stdio.h>//���ر�׼�������ͷ�ļ�
int main()
{
	WORD wVersionRequested;//�汾��
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );//1.1�汾���׽���
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) { return 0; }//�����׽��ֿ⣬�Ӳ�ʧ���򷵻�
	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ){
		WSACleanup( );
		return 0;
	}//�������1.1�����˳�
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);//�����׽��֣�socket����
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//ת��Unsigned shortΪ�����ֽ���ĸ�ʽ 
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)); 
	//���׽��ְ󶨵�һ�����ص�ַ�Ͷ˿��ϣ�bind�� listen(sockSrv,5);
	//���׽�����Ϊ����ģʽ��׼�����տͻ�����listen����
	SOCKADDR_IN addrClient;//�����ַ��
	int len=sizeof(SOCKADDR);//��ʼ���������������������뱻��ʼ��
	while(1){
	SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
	//accept�ĵ���������һ��Ҫ�г�ʼֵ��
	//�ȴ��ͻ������������������󣬽�����������
	//����һ���µĶ�Ӧ�ڴ˴����ӵ��׽��֣�accept���� 
	//��ʱ�����ڴ˷�������
	char sendBuf[100];
	sprintf(sendBuf,"Welcome %s to www.msn.com.cn",inet_ntoa(addrClient.sin_addr)); 
	//�÷��ص��׽��ֺͿͻ��˽���ͨ�ţ�send/recv����
	send(sockConn,sendBuf,strlen(sendBuf)+1,0);
	char recvBuf[100];
	recv(sockConn,recvBuf,100,0);
	printf("%s\n",recvBuf);
	closesocket(sockConn);//�ر��׽��֡��ȴ���һ���û�����
	}
}

