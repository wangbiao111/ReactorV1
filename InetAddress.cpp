#include "InetAddress.h"
#include <string.h>
using std::string;


namespace wb
{

	InetAddress::InetAddress(unsigned short port)
	{
		::memset(&_addr,0,sizeof(struct sockaddr_in));
		_addr.sin_family = AF_INET;
		_addr.sin_port = htons(port);
		
		//INADDR_ANY服务器监听所有可用网卡的连接，
		//无论客户端通过哪个 IP 地址访问服务器。
		_addr.sin_addr.s_addr = INADDR_ANY;//代表本机地址
	}
	
	InetAddress::InetAddress(const string & ip,unsigned short port)
	{
		::memset(&_addr,0,sizeof(struct sockaddr_in));
		_addr.sin_family = AF_INET;
		_addr.sin_port = htons(port);
		_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	}
	
	InetAddress::InetAddress(const struct sockaddr_in &addr)
		:_addr(addr)
	{
	}

	InetAddress::~InetAddress() 
	{

	}


	string InetAddress::ip() const
	{
		return string(::inet_ntoa(_addr.sin_addr));
	}

	unsigned short InetAddress::port() const
	{
		return ntohs(_addr.sin_port);
	}

}

