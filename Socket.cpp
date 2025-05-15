#include "Socket.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wb
{
	Socket::Socket()
	{
		_fd = socket(AF_INET,SOCK_STREAM,0);
		if(_fd == -1)
		{
			perror("socket");
		}
	}
	
	Socket::Socket(int fd)
	:_fd(fd)
	{}

	void Socket::shutdownWrite()
	{
		::shutdown(_fd,SHUT_WR);
	}
	
	//RAII
	Socket::~Socket()
	{
		::close(_fd);
	}
	

}


