#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace wb
{
class Acceptor
{
public:
	Acceptor(unsigned short port);
	Acceptor(const string & ip,unsigned short port);
	~Acceptor();
	
	void ready();
	int accept();
	
private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();
	
	
private:
	//Socket中有文件描述符	
	Socket _listensock;
	//InetAddress是一个struct sockaddr_in结构体
	InetAddress _addr;
};
}

#endif