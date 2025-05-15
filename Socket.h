#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "Noncopyable.h"

namespace wb
{
	
class Socket
:Noncopyable
{
public:
	Socket();
	
	explicit
	Socket(int fd);

	int fd() const{
		return _fd;
	}
	
	void shutdownWrite();
	
	~Socket();
	
private:
	int _fd;
};
}


#endif
