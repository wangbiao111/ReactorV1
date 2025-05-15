#include "TcpConnection.h"
#include "InetAddress.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>
using std::string;

namespace wb
{

	TcpConnection::TcpConnection(int fd)
	:_sock(fd)
	,_sockIo(fd)
	,_localAddr(getLocalAddr(fd))
	,_peerAddr(getPeerAddr(fd))
	,_isShutdownWrite(false)
	{
		
	}
	
	TcpConnection::~TcpConnection()
	{
		if(!_isShutdownWrite)
		{
			shutdown();
		}
	}
	
	void TcpConnection::send(const string & msg)
	{
		_sockIo.writen(msg.c_str(),msg.size());
	}
	
	string TcpConnection::receive()
	{
		char buff[65535] = {0};
		//readline，消息边界是’\n‘
		_sockIo.readLine(buff,sizeof(buff));
		return string(buff);
	}
	
	
	//这两个方法是类图中没有的
	//获取五元组信息
	string TcpConnection::toString() const
	{
		std::ostringstream oss;
		oss<<"tcp"<<_localAddr.ip()<<":"<<_localAddr.port()<<"-->"
			<<_peerAddr.ip()<<":"<<_peerAddr.port();
		return oss.str();
	}
	
	void TcpConnection::shutdown()
	{
		if(!_isShutdownWrite)
		{
			_isShutdownWrite = true;
			_sock.shutdownWrite();
		}
	}
	

	InetAddress TcpConnection::getLocalAddr(int fd)
	{
		struct sockaddr_in addr;
		socklen_t len = sizeof(struct sockaddr);
		if(getsockname(_sock.fd(),(struct sockaddr *)&addr,&len)==-1)
		{
			perror("getsockname");
		}
		return InetAddress(addr);
	}
	
	InetAddress TcpConnection::getPeerAddr(int fd)
	{
		//指向 sockaddr 结构体的指针，
		//用于存储套接字的地址信息（如 IP 地址、端口号）。
		struct sockaddr_in addr;
		
		//addrlen
		//指向 socklen_t 类型的指针，表示 addr 结构体的长度
		socklen_t len = sizeof(struct sockaddr);
		
		//成功返回0，addr中存储对端套接字的地址信息
		//失败返回-1
		if(getpeername(_sock.fd(),(struct sockaddr *)&addr,&len)==-1)
		{
			perror("getpeername");
		}
		return InetAddress(addr);
	}
	
}
