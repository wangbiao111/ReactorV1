#include "Acceptor.h"


namespace wb
{

	//如果只传端口，说明走的本机地址	
	Acceptor::Acceptor(unsigned short port)
	:_addr(port)
	,_listensock()
	{
		
	}
	
	Acceptor::Acceptor(const string & ip,unsigned short port)
	:_addr(ip,port)
	,_listensock()
	{
		
	}
	
	Acceptor::~Acceptor()
	{
		
	}
	
	void Acceptor::ready()
	{
		setReuseAddr(true);
		setReusePort(true);
		bind();
		listen();
	}
	
	int Acceptor::accept()
	{
		//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		//成功：返回一个新的套接字描述符，用于与客户端通信（称为已连接套接字）。
		int peerfd = ::accept(_listensock.fd(),NULL,NULL);
		if(peerfd = -1)
		{
			perror("accept");
		}
		return peerfd;
	}
	

	void Acceptor::setReuseAddr(bool on)
	{
		int one = on;
		if(setsockopt(_listensock.fd(),
						SOL_SOCKET,
						SO_REUSEADDR,
						&one,
						sizeof(one))<0)
		{
			perror("setsockopt");
		}
	}
	
	void Acceptor::setReusePort(bool on)
	{
		int one = on;
		if(setsockopt(_listensock.fd(),
						SOL_SOCKET,
						SO_REUSEADDR,
						&one,
						sizeof(one))<0)
		{
			perror("setsockopt");
		}
	}
	
	void Acceptor::bind()
	{
		int ret = ::bind(_listensock.fd(),
			(struct sockaddr *)_addr.getInetAddressPtr(),
			sizeof(struct sockaddr));
		//成功返回0，失败返回-1
		if(ret == -1)
		{
			perror("bind");
		}
	}
	
	
	
	void Acceptor::listen()
	{
		//128：这个参数代表的是连接请求队列的最大长度
		int ret = ::listen(_listensock.fd(),128);
		//返回0成功，1失败
		if(-1 == ret)
		{
			perror("listen");
		}
	}
	
}

