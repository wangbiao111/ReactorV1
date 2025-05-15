#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

namespace wb
{
class SocketIO
{
public:
	explicit
	SocketIO(int fd);
	~SocketIO();
	
	//为什么写要加const 读不用加？	
	//从套接字读取数据写入buff
	int readn(char * buf,int len);
	//将buff中的数据写入套接字
	int writen(const char *buf,int len);
	int readLine(char * buf,int maxlen);

//这一步是做了什么？	
private:
	int recvpeek(char *buff,int len);
	

private:
	int _fd;
};
	
}

#endif