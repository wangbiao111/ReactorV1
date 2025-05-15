#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	wb::Acceptor acceptor(8000);
    cout<<"before ready."<<endl;
	acceptor.ready();
	
    cout<<"before accept."<<endl; 
	wb::TcpConnection conn(acceptor.accept());
	cout<<conn.toString()<<"has connected!"<<endl;
	conn.send("welcome to server.");
	printf(">recv client data:\n");
	cout<<conn.receive()<<endl;
	
	return 0;
}
