#ifndef __TCPCONNECTION_H__
#define	__TCPCONNECTION_H__

#include "SocketIO.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Noncopyable.h"

#include <string>
using std::string;

namespace wb
{
	
class TcpConnection
:Noncopyable
{
public:
	TcpConnection(int fd);
	~TcpConnection();
	
	void send(const string & msg);
	string receive();
	
	
	//这两个方法是类图中没有的
	//获取五元组信息
	string toString() const;
	void shutdown();
	
private:
	InetAddress getLocalAddr(int fd);
	InetAddress getPeerAddr(int fd);
	
private:
	SocketIO _sockIo;
	Socket _sock;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	bool _isShutdownWrite;//是否要主动断开连接
};
}
#endif