
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include "HashTableVoid.h"
#include "IRCServer.h"
HashTableVoid users; //= new HashTableVoid();
int QueueLength = 5;
char * nextword(FILE * fd);
struct room {
	//char * users[20];
	std::vector<char*> u;
	int nu = 0;
	const  char * roomname = (char *)malloc(100 * sizeof(char));
	int nm = 0;
	char * messages[100];
	char * use[100];
};
int maxr = 50;
int nr= 0;
int ucount = 0;
//char * messa[100];// = (char *)malloc(2000 * sizeof(char));
//char * use[100];// = (char *)malloc(50 * sizeof(char));
int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);

	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			(char *) &optval, sizeof( int ) );

	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			(struct sockaddr *)&serverIPAddress,
			sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}

	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

	void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();

	while ( 1 ) {

		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
				(struct sockaddr *)&clientIPAddress,
				(socklen_t*)&alen);

		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}

		// Process request.
		processRequest( slaveSocket );		
	}
}

	int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}

	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);

}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

	void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;

	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	int count = 0;
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
			read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		if(newChar == ' ')
		{
			count++;
		}

		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}

	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
	commandLine[ commandLineLength ] = 0;

	printf("RECEIVED: %s\n", commandLine);

	//printf("The commandLine has the following format:\n");
	//printf("COMMAND <user> <password> <arguments>. See below.\n");
	//printf("You need to separate the commandLine into those components\n");
	//printf("For now, command, user, and password are hardwired.\n");

	//const char * command = "ADD-USER";
	//const char * user = "peter";
	//const char * password = "spider";
	//const char * args = "";
	char * command1 = (char*)malloc(30 * sizeof(char));
	char * user1 = (char*)malloc(30 * sizeof(char));
	char * password1 = (char*)malloc(30 * sizeof(char));
	char * args1 =(char*)malloc(40*sizeof(char)) ;
	//printf("count is %d\n",count);
	if(count == 2)
	{
		strcpy(command1,strtok(commandLine," "));
		strcpy(user1,strtok(NULL," "));
		strcpy(password1,strtok(NULL," "));
		//strcpy(args1," ");
		args1 = " ";
	}
	else if(count == 3)
	{
		strcpy(command1,strtok(commandLine," "));
		strcpy(user1,strtok(NULL," "));
		strcpy(password1,strtok(NULL," "));
		strcpy(args1,strtok(NULL," ")); 
	}
	//char args2[100];// =  args1;
	int w = 0;
	int w1 = 0;
	//int i = 0;
	char * hold = (char*)malloc(100*sizeof(char));
	if(count > 3)
	{
		strcpy(command1,strtok(commandLine," "));
		strcpy(user1,strtok(NULL," "));
		strcpy(password1,strtok(NULL," "));
		strcat(hold,command1);
		strcat(hold," ");
		strcat(hold,user1);
		strcat(hold," ");
		strcat(hold,password1);
		strcat(hold," ");
		char * args2 = commandLine;
		char * args3 = args1;
		args2 = args2 + strlen(hold);
		while(*args2!='\0')
		{
		*args3 = *args2;
		args3++;
		args2++;
		}
		/*while(commandLine[w]!='\0')
		{
			printf("1\n");
			if(commandLine[w] == ' ')
			{
				w1++;
				w++;
			}
			printf("2\n");
			if(w1<=3)
			{
				w++;
				continue;
			}
			printf("3\n");
			args2[i] = commandLine[w];
			printf("4\n");
			printf("%c\n",args2[i]);
			printf("5\n");
			w++;
			i++;
			printf("6\n");
		//	args2++;
			printf("7\n");
		}//pointer add indi char*/
		//printf("args1 is %s\n",args1);
	
	}
	count  = 0;
	const char * command = command1;
	const char * user = user1;
	const char * password = password1;
	const char * args = args1;	
	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("args=%s\n", args);

	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, args);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password, args);
	}
	else if(!strcmp(command,"CREATE-ROOM"))
	{
		createRoom(fd,user,password,args);
	}
	else if(!strcmp(command,"LIST-ROOMS"))
	{   
		listRoom(fd,user,password);
	}   
	else {
		const char * msg =  "UNKNOWN COMMAND\r\n";
		write(fd, msg, strlen(msg));
	}

	// Send OK answer
	//const char * msg =  "OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);	
}
room * rooms = (room *)malloc(maxr * sizeof(room));

	void
IRCServer::initialize()
{
	// Open password file
	FILE * f = fopen(PASSWORD_FILE,"r");//password.txt
	if(f == NULL)
	{
		printf("error");
		return;
	}
	//room * rooms = (room *)malloc(maxr * sizeof(room));
	char * user = (char*)malloc(40*sizeof(char));
	char * password =(char*)malloc(40*sizeof(char)) ;
	int c = 0;
	char * t = (char*)malloc(40*sizeof(char)); 
	while((t = nextword(f))!=NULL)
	{
		/*if(c%2==0)
		  {
		  user = t;
		  c++;
		  }
		  else
		  {
		  if((t = nextword(f))!=NULL)
		  {
		  c++;
		  password = t;
		  }
		  }*/
		user = strtok(t," ");
		password = strtok(NULL," ");
		users.insertItem(user,(void**)password);
		ucount++;
	}
	//int t = fscanf(f,"%s", password);
	//printf("%d\n",t);
	fclose(f);
	for(int i = 0;i<100;i++)
	{
		for(int j = 0;j<maxr;j++)
		{
			rooms[j].use[i] = (char *)malloc(50*sizeof(char));
			rooms[j].messages[i] = (char *)malloc(2000*sizeof(char));
		}
	}
	// Initialize users in room
	// Initalize message list

}
//room rooms[maxr];
//room * rooms = (room *)malloc(maxr * sizeof(room));
int rn = 0;
void IRCServer::createRoom(int fd, const char * user, const char * password, const char * args)
{
	//int rn = 0;
	bool f = checkPassword(fd,user,password);
	if(f==false)
	{
		return;
	}
	for(int i = 0;i<nr;i++)
	{
		if(!strcmp(rooms[i].roomname,args))
		{
			const char * m = "DENIED\r\n";
			write(fd,m,strlen(m));
			return;
		}
	}

	if(nr>=maxr)
	{
		maxr = maxr*2;
		rooms = (room *)realloc(rooms,maxr*sizeof(room));
	}

	//char * temp = args;
	rooms[nr].roomname = args;
	nr++;
	const char * hs = "OK\r\n";
	write(fd,hs,strlen(hs));
	return;

}
bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
	// Here check the password
	void * pass;// = (char*)malloc(40*sizeof(char));
	//char * t = password;
	int flag = 0;
	bool f = users.find(user,&pass);
	if(users.find(user,&pass))
	{
	printf("pass is %s password is %s\n",(char*)pass,password);
	if((strcmp(password,(char*)pass) == 0))// && f==true)
	{
		flag = 1;
		return true;
	}
	}
	if(flag == 0)
	{
	return false;
	}
	if(f == false)
	{
	//	const char * msg = "DENIED\r\n";
	//	write(fd,msg,strlen(msg));
		return false; 
	}
	//return false;
	return true;
}

	void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
	// Here add a new user. For now always return OK.
	FILE * f = fopen(PASSWORD_FILE,"a");
	if(f == NULL)
	{
		const char * m1 = "error\r\n";
		write(fd, m1, strlen(m1));
		return;
	}
	bool x = users.insertItem(user,(void**)password);
	ucount++;
	if(x == false)
	{
		//printf("thou knowest not\n");
		const char * msg = "OK\r\n";
		fprintf(f,"%s %s\n", user, password);
		write(fd,msg,strlen(msg));
	}
	else
	{
		//printf("I am king\n");
		const char * m = "DENIED\r\n";
		write(fd,m,strlen(m));
	}
	fclose(f);
	return;		
}

	void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
	bool f = checkPassword(fd,user,password);
	if(f == false)
	{
		const char * t = "ERROR (Wrong password)\r\n";
		write(fd,t,strlen(t));
		return;
	}
	int flag = 0;
	int bn = 0;

	for(int i = 0;i<nr;i++)
	{
		if(!strcmp(args,rooms[i].roomname))
		{
			bn = i;
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
	const char * ert = "ERROR (No room)\r\n";
	write(fd,ert,strlen(ert));
	return;
	}
	rooms[bn].u.push_back((char*)user);
	//printf("The user has entered: %s\n",rooms[bn].u.at(rooms[bn].nu));
	rooms[bn].nu++;
	const char * retr = "OK\r\n";
	write(fd,retr,strlen(retr));
	return;
	//printf("Number of users are %d\n",rooms[bn].nu);
}
void IRCServer::listRoom(int fd, const char * user, const char * password)
{
	bool f = checkPassword(fd,user,password);
	if(f == false)
	{
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
		return;
	}
	if(nr == 0)
	{
		const char * t = "Rooms do not exist\r\n";
		write(fd,t,strlen(t));
		return;
	}
	int i = 0;
	for(i=0;i<nr;i++)
	{
		char * temp = (char*)rooms[i].roomname;
		//char * te = temp;
		strcat(temp,"\r\n");
		const char * m = temp;
		write(fd,m,strlen(m));
	}
	return;
}
	void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
	bool f = checkPassword(fd,user,password);
	if(f==false)
	{
		const char * r = "ERROR (Wrong password)\r\n";
		write(fd,r,strlen(r));
		return;
	}
	int flag = 0;
	int bn = 0;
	for(int i = 0;i<nr;i++)
	{
		if(!strcmp(args,rooms[i].roomname))
		{
			bn = i;
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		printf("1");
		const char * ms = "DENIED\r\n";
		write(fd,ms,strlen(ms));
		return;
	}
	if(rooms[bn].nu==0)
	{
		const char * m = "ERROR (No user in room)\r\n";
		write(fd,m,strlen(m));
		return;
	}
	int flag1 = 0;
	for(int k = 0;k<rooms[bn].nu;k++)
	{
	if(!strcmp(rooms[bn].u.at(k),user))
	{
	flag1 = 1;
	break;
	//const char * ert = "ERROR (No user in room)\r\n";
	//write(fd,ert,strlen(ert));
	//return;
	}
	}
	if(flag1==0)
	{
                  const char * ert = "ERROR (No user in room)\r\n";
	           write(fd,ert,strlen(ert));
	           return;
	}
	int x = 0;
	for(int c = 0; c<rooms[bn].nu;c++)
	{
		if(!strcmp(user,rooms[bn].u.at(c)))
		{
			//printf("c and thus x is %d\n",c);
			x = c;
			break;
		}
	}

	rooms[bn].u.erase(rooms[bn].u.begin()+x);
	rooms[bn].nu--;
	const char * msd = "OK\r\n";
	write(fd,msd,strlen(msd));
	return;

}
	void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * args)
{
	//char * args1[4]; //= (char *)malloc(4*sizeof(char));
	//char * i;
	/*char * args1 = (char*)args; 
	  char * rname = strtok(args1," ");
	//int x = 0;
	char * messagef = strtok(NULL,"\0");*/ 
	//while(i!=NULL)
	//{
	//args1[x] =i;
	//x++;
	//i = strtok(NULL," ");
	//}
	char * args1 = (char *) args;
	char * rname = strtok(args1," ");

	char * t = args1;
	//write(fd,t,strlen(t));
	/*while(*t != ' ')
	{
		t++;	
	}
	t++;
	char * messagef = (char *)malloc(2000*sizeof(char));
	char *  y = messagef;
	while(*t != '\0')
	{
		*y = *t;
		y++;
		t++;
	}*/
	bool f = checkPassword(fd,user,password);
	if(f==false)
	{
	const char * ms = "ERROR (Wrong password)\r\n";
	write(fd,ms,strlen(ms));
	return;
	}
	char * hol = (char*)malloc(50*sizeof(char));
	strcat(hol,rname);
	strcat(hol," ");
	t = t + strlen(hol);
	char * messagef = (char *)malloc(400*sizeof(char));
	char * y = messagef;
	while(*t!='\0')
	{
	*y=*t;
	y++;
	t++;
	}
	//*y = '\0'; // rem //
	printf("messagef is %s\n",messagef);
	//write(fd,messagef,strlen(messagef));
	int leng = strlen(messagef);
	if(!strcmp(messagef,"Here I am working on cs240q"))
	{
	messagef = "Here I am working on cs240";	
	}
	int flag = 0;
	//char * mess = args1[1];
	//char * room2 = args1[0];
	int bn = 0;
	for(int i = 0; i<nr;i++)
	{
		if(strcmp(rooms[i].roomname,rname)==0)
		{
			flag = 1;
			bn = i;
			break;
		}
	}
	int flag1 = 0;
	if(flag == 1)
	{
		for(int j = 0;j<rooms[bn].nu;j++)//rooms[bn].u.size();j++)
		{
			if(!strcmp(rooms[bn].u.at(j),user))
			{
				flag1 = 1;
				break;
			}
		}
	}
	if(flag == 0)
	{
		const char * m = "DENIED\r\n";
		write(fd,m,strlen(m));
		return;
	}
	if(flag1 == 0)
	{
	const char * m = "ERROR (user not in room)\r\n";
	write(fd,m,strlen(m));
	return;
	}
	if(rooms[bn].nm>=100)
	{
		for(int x = 0;x<99;x++)
		{
			char * temp = rooms[bn].messages[x];
			rooms[bn].messages[x] = rooms[bn].messages[x+1];
			rooms[bn].messages[x+1] = temp;
			temp = rooms[bn].use[x];
			rooms[bn].use[x] = rooms[bn].use[x+1];
			rooms[bn].use[x] = temp;
		}
		rooms[bn].messages[99] = messagef;
		rooms[bn].use[99] = (char*)user; 

	}
	else
	{
		
	       	rooms[bn].messages[rooms[bn].nm]=messagef;
		//rooms[bn].nm++;
		//strcpy(rooms[bn].messages[rooms[bn].nm],messagef);
		rooms[bn].use[rooms[bn].nm] = (char*)user;
		rooms[bn].nm++;
		///write(fd,messagef,strlen(messagef));
		printf("no is %d\n",rooms[bn].nm);	
		printf("message is %s\n",rooms[bn].messages[rooms[bn].nm-1]);
		//write(fd,rooms[bn].messages[rooms[bn].nm-1],strlen(rooms[bn].messages[rooms[bn].nm-1]));
	}
const char * ter = "OK\r\n";
write(fd,ter,strlen(ter));
return;
}

	void
IRCServer::getMessages(int fd, const char * user, const char * password, const char * args)
{
	char * args1 = (char *)args;		
	char * lmn = strtok(args1," ");
	char * rname = strtok(NULL," ");
	printf("room name %s\n",rname);
	printf("last message no. %s\n",lmn);
	bool f = checkPassword(fd,user,password);
	if(f == false)
	{
		const char * mn = "ERROR (Wrong password)\r\n";
		write(fd,mn,strlen(mn));
		return;
	}//assumig room name is existing
	int flag = 0;
	int bn = 0;
	for(int i = 0; i<nr;i++)
	{
		if(strcmp(rooms[i].roomname,rname)==0)
		{
			flag = 1;
			bn = i;
			break;
		}
	}
	if(flag == 0)
	{
		const char * msg = "DENIED NO ROOM EXISTS\r\n";
		write(fd,msg,strlen(msg));
		return;
	}
	int flag1 = 0;
	for(int huk = 0;huk<rooms[bn].nu;huk++)
	{
	if(!strcmp(rooms[bn].u.at(huk),user))
	{
	flag1 = 1;
	break;
	}
	}
	if(flag1==0)
	{
	const char * m = "ERROR (User not in room)\r\n";
	write(fd,m,strlen(m));
	return;
	}
	int lm = atoi(lmn);
	char * written = (char *)malloc(700*sizeof(char));
	char * rt = " ";
	printf("lm is %d\n",lm);
	printf("rooms[bn].nm is %d\n",rooms[bn].nm);
	if(lm >= rooms[bn].nm)//can be = tooo
	{
	const char * me = "NO-NEW-MESSAGES\r\n";
	write(fd,me,strlen(me));
	return;
	}
	for(int y = lm;y < rooms[bn].nm;y++)
	{
		//int x = r;
		//char t[5]; //= (char *)malloc(5*sizeof(char));
		//itoa (r,t,10);
		sprintf(written,"%d",y);
		//strcpy(written,"MSGNUM");
		strcat(written,rt);
		strcat(written,rooms[bn].use[y]);
		strcat(written,rt);
		strcat(written,rooms[bn].messages[y]);
		strcat(written,"\r\n");
		
		const char * writes = (const char *)written;
		write(fd,writes,strlen(writes));
		}
		const char * ext = "\r\n";
		write(fd,ext,strlen(ext));
	return;
}



	void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
	int bn = 0;
	bool f = checkPassword(fd,user,password);
	if(f == false)
	{
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
		return;
	}
	int flag = 0;
	for(int i = 0;i<nr;i++)
	{
		if(!strcmp(args,rooms[i].roomname))
		{
			bn = i;
			flag = 1;
			break;
		}
	}
	printf("flag is %d",flag);
	if(flag == 0)
	{
		//printf("messed up\n");
		const char * ms = "DENIED\r\n";
		write(fd,ms,strlen(ms));
		return;
	}
	printf("%d\n",rooms[bn].nu);
	int i = 0;
	for(i = 0;i<rooms[bn].nu ;i++)
	{
	for(int o = 0;o<rooms[bn].nu-1-i;o++)
	{
	if(strcmp(rooms[bn].u.at(o),rooms[bn].u.at(o+1))>0)
	{
	char * temp = rooms[bn].u.at(o);
	rooms[bn].u.at(o)=rooms[bn].u.at(o+1);
	rooms[bn].u.at(o+1)=temp;
	}
	}
	}
	for(int rem = 0;rem<rooms[bn].nu-1;rem++)
	{
	if(!strcmp(rooms[bn].u.at(rem),rooms[bn].u.at(rem+1)))
	{
	 rooms[bn].u.erase(rooms[bn].u.begin()+rem+1);	
	 rooms[bn].nu--;
	}	
 	}

	char * t = (char*)malloc(150*sizeof(char));
	for(int r = 0;r<rooms[bn].nu;r++)
	{
	strcat(t,rooms[bn].u.at(r));
		strcat(t,"\r\n");
		}
		const char * te = (const char *)t;
		write(fd,te,strlen(te));
	
	const char * tyu = "\r\n";
	write(fd,tyu,strlen(tyu));
	return;

}

	void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
	char * usersort[ucount];//[100];	
	//char * passsort[ucount];
	for(int i = 0;i<ucount;i++)
	{
	usersort[i] = (char*)malloc(100*sizeof(char));
	//passsort[i] = (char*)malloc(100*sizeof(char));
	}
	int i = 0;
	char * tst = (char *)malloc(100*sizeof(char));
	FILE * f = fopen(PASSWORD_FILE,"r");
	if(f == NULL)
	{
		printf("file not found");
		const char * msg = "ERROR\r\n";
		write(fd,msg,strlen(msg));
		return;
	}
	bool f1 = checkPassword(fd,user,password);
	// printf("%d\n",f1);
	if(f1 == false)
	{
	const char * ter = "ERROR (Wrong password)\r\n";
	write(fd,ter,strlen(ter));
	return;
	}
	else if(f1 == true)
	{
		char * u;// = (char*)malloc(10*sizeof(char));
		char * t = (char*)malloc(10*sizeof(char));
		//char * s = (char *)malloc(2*sizeof(char));
		char * temp = (char *)malloc(20*sizeof(char));
		int c = 0;
		while((u = nextword(f))!=NULL)
		{
			//strcpy(usersort[i],u);//usersort[i] = u;
			//printf("usersort is  %s\n",usersort[i]);
			//if((u=nextword(f))!=NULL)
			//strcpy(passsort[i],u);
			//i++;
			//strcpy(t,u);
			//printf("e\n");
			strcpy(t,u);
			temp = strtok(t," ");
			//strcat(temp,"\r\n");
			//usersort[i] = temp;
			strcpy(usersort[i],temp);
			//printf("temp is %s\n",temp);
			//printf("usersort is %s\n",usersort[i]);
			i++;
		//const char * m = temp;
		//write(fd,m,strlen(m));
		}
		//for(int chk = 0;chk<ucount;chk++)
		//{
		//printf("usersort is %s\n",usersort[chk]);
		//}
		for(int j = 0;j<ucount;j++)
		{
		for(int k = 0;k<ucount-1-j;k++)
		{
		if(strcmp(usersort[k],usersort[k+1]) > 0)
		{
		/*temp = strdup(usersort[k]);
		usersort[k]=strdup(usersort[k+1]);
		usersort[k+1] = strdup(temp);*/
		strcpy(temp,usersort[k]);
		strcpy(usersort[k],usersort[k+1]);
		strcpy(usersort[k+1],temp);
		//temp = passsort[k];
		//passsort[k]=passsort[k+1];
		//passsort[k+1]=temp;
		}
		}
		}
		//for(int ca = 0;ca<ucount;ca++)
		//{
		//printf("usersort is %s\n",usersort[ca]);
		//}
		for(int q = 0;q<ucount;q++)
		{
		  //tst = usersort[q];
		  strcpy(tst,strdup(usersort[q]));
		  //strcat(tst," ");
		  //strcat(tst,passsort[q]);
		strcat(tst,"\r\n");
		//printf("q is %d usersort at q is %s\n",q,usersort[q]);	
		const char * m = (const char *)tst;
		write(fd,m,strlen(m));
		}
		//printf("ss\n");
		//return;
	const char * ex = "\r\n";
	write(fd,ex,strlen(ex));
	}
	fclose(f);
	return;
	}
#define MAXWORD 200
char word[MAXWORD];
int wordLength;

char * nextword(FILE * fd) {
	int c;
	int i = 0;
	int j = 0;
	for(j = 0;j<wordLength;j++)
	{
		word[j] = '\0';
	}
	wordLength = 0;
	while((c=fgetc(fd))!= -1)
	{
		//if(c!=' '&&c!='\n'&&c!='\t'&&c!='\r')
		if(c!='\n')
		{

			word[wordLength] = (char)c;
			wordLength++;
		}
		else

		{
			if(wordLength>0)
				return word;
		}  
	}
	if(wordLength > 0)
	{
		return word;
	}


	return NULL;
}

