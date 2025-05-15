#include "SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


namespace wb
{

	//explicit
	SocketIO::SocketIO(int fd)
	:_fd(fd){}
	
	SocketIO::~SocketIO(){}
	
	//为什么写要加const 读不用加？	
	//从套接字读取数据写入buff
	int SocketIO::readn(char * buff,int len)
	{
		int left = len;
		char *p = buff;
		
		while(left>0)
		{
			int ret = ::recv(_fd,p,left,0);
			if(ret == -1 && errno == EINTR)
			{
				continue;//软中段
			}else if(ret == -1){//链接错误
				perror("read");
				return len - left;
			}else if(ret == 0){//链接中断
				return len - left;
			}else{// >0 ?
			//正整数：实际接收到的字节数。
				left -= ret;
				p+=ret;
			}
		}
		return len - left;//正常退出
	}
	
	//将buff中的数据写入套接字
	int SocketIO::writen(const char *buff,int len)
	{
		int left = len;
		const char * p =buff;
		while(left>0)
		{
			int ret = ::send(_fd,p,left,0);
			if(ret == -1 && errno == EINTR)
			{
				continue;
			}else if(ret == -1)
			{
				perror("write");
				return len - left;
			}else{
				left -= ret;
				p += ret;
			}
		}
		return len - left;
	}
	
	int SocketIO::readLine(char * buff,int maxlen)
	{
		int left = maxlen - 1;
		char *p = buff;
		int ret;
		int total = 0;
		while(left > 0)
		{
			ret = recvpeek(p,left);
			//查找'\n'
			for(int idx = 0;idx!=ret;++idx)
			{
				if(p[idx]=='\n')//找到
				{
					int sz = idx + 1;
					readn(p,sz);
					total+=sz;
					p+=sz;
					*p = '\0';
					return total;
				}
			}
			//没有找到'\n'
			readn(p,ret);
			left-=ret;
			p+=ret;
			total+=ret;
		}
		*p = '\0';
		return total;
	}


	//这一步是做了什么？	
	//查看下缓冲区里有多少ret可以发
	int SocketIO::recvpeek(char *buff,int len)
	{
		int ret;
		do{
			ret = ::recv(_fd,buff,len,MSG_PEEK);
		}while(ret == -1 && errno == EINTR);
		return ret;
	}
	
}

