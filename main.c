#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#define FONTSIZE 10
int PrintMenuOS()
{
	int i, j;
	char data_M[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"  *    *  ",
		" ***  *** ",
		" * *  * * ",
		" * *  * * ",
		" *  **  * ",
		" *      * ",
		" *      * ",
		" *      * ",
		"          "
	};
	char data_e[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"          ",
		"    **    ",
		"   *  *   ",
		"  *    *  ",
		"  ******  ",
		"  *       ",
		"   *      ",
		"    ***   ",
		"          "
	};
	char data_n[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"          ",
		"    **    ",
		"   *  *   ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"          "
	};
	char data_u[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"          ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"  *    *  ",
		"   *  **  ",
		"    **  * ",
		"          "
	};
	char data_O[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"   ****   ",
		"  *    *  ",
		" *      * ",
		" *      * ",
		" *      * ",
		" *      * ",
		"  *    *  ",
		"   ****   ",
		"          "
	};
	char data_S[FONTSIZE][FONTSIZE] =
	{
		"          ",
		"    ****  ",
		"   **     ",
		"  **      ",
		"   ***    ",
		"     **   ",
		"      **  ",
		"     **   ",
		"  ****    ",
		"          "
	};
	for(i=0; i<FONTSIZE; i++)
	{
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_M[i][j]);
		}
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_e[i][j]);
		}
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_n[i][j]);
		}
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_u[i][j]);
		}
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_O[i][j]);
		}
		for(j=0; j<FONTSIZE; j++)
		{
			printf("%c", data_S[i][j]);
		}
		printf("\n");
	}
return 0;
}


int Quit(int argc, char *argv[])
{
	/* add XXX clean ops */
}

#include"syswrapper.h"
#define MAX_CONNECT_QUEUE   1024
int Replyhi()

{

	char szBuf[MAX_BUF_LEN] = "\0";

	char szReplyMsg[MAX_BUF_LEN] = "hi\0";

	InitializeService();

	while (1)

	{

		ServiceStart();

		RecvMsg(szBuf);

		SendMsg(szReplyMsg);

		ServiceStop();

	}

	ShutdownService();

	return 0;

}



int StartReplyhi(int argc, char *argv[])

{

	int pid;

	/* fork another process */

	pid = fork();

	if (pid < 0)

	{

		/* error occurred */

		fprintf(stderr, "Fork Failed!");

		exit(-1);

	}

	else if (pid == 0)

	{

		/*	 child process 	*/

		Replyhi();

		printf("Reply hi TCP Service Started!\n");

	}

	else

	{

		/* 	parent process	 */

		printf("Please input hello...\n");

	}

}

int Hello(int argc, char *argv[])

{

	char szBuf[MAX_BUF_LEN] = "\0";

	char szMsg[MAX_BUF_LEN] = "hello\0";

	OpenRemoteService();

	SendMsg(szMsg);

	RecvMsg(szBuf);

	CloseRemoteService();

	return 0;

}



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <arpa/inet.h>
#define SERVER_PORT 8888
#define BUFF_LEN 1024

int httpclient()
{
        int sockfd, ret, i, h;
        struct sockaddr_in servaddr;
        char str1[4096], str2[4096], buf[BUFSIZE], *str;
        socklen_t len;
        fd_set   t_set1;
        struct timeval  tv;
         
         //创建套接字
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
                printf("创建网络连接失败,本线程即将终止---socket error!\n");
                exit(0);
        };
 
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
                printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
                exit(0);
        };
 
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
                printf("连接到服务器失败,connect error!\n");
                exit(0);
        }
        printf("与远端建立了连接\n");
        memset(str2, 0, 4096);
        strcat(str2, "theDataToPost");
        str=(char *)malloc(128);
        len = strlen(str2);
        sprintf(str, "%d", len);
 
        memset(str1, 0, 4096);
        strcat(str1, "GET /index.html HTTP/1.1\n");
        strcat(str1, "Host: www.github.com\n");
        strcat(str1, "Content-Type: text/html\n");
        strcat(str1, "Content-Length: ");
        strcat(str1, str);
        strcat(str1, "\n\n");
 
        strcat(str1, str2);
        strcat(str1, "\r\n\r\n");
        printf("%s\n",str1);
 
        ret = write(sockfd,str1,strlen(str1));
        if (ret < 0) {
                printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
                exit(0);
        }else{
                printf("send request successfully，%d bytes\n\n", ret);
        }
 
        FD_ZERO(&t_set1);
        FD_SET(sockfd, &t_set1);
 
        while(1){
                sleep(2);
                tv.tv_sec= 0;
                tv.tv_usec= 0;
                h= 0;
                printf("--------------->1");
                h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
                printf("--------------->2");
 
                //if (h == 0) continue;
                if (h < 0) {
                        close(sockfd);
                        printf("在读取数据报文时SELECT检测到异常，该异常导致线程终止！\n");
                        return -1;
                };
 
                if (h > 0){
                        memset(buf, 0, 4096);
                        i= read(sockfd, buf, 4095);
                        if (i==0){
                                close(sockfd);
                                printf("读取数据报文时发现远端关闭，该线程终止！\n");
                                return -1;
                        }
                        printf("%s\n", buf);
                }
        }
        close(sockfd);
 
 
        return 0;
}

void udp_server(int fd){
	char buf[BUFF_LEN];
	socklen_t len;
	int count;
	struct sockaddr_in clent_addr;
	while(1){
		memset(buf, 0, BUFF_LEN);
		len = sizeof(clent_addr);
		count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);
		if(count == -1){
			printf("recieve data fail!\n");
			return;
		}
		printf("msg from client: %s\n",buf);
		memset(buf, 0, BUFF_LEN);
		sprintf(buf, "I have recieved %d bytes data!\n", count);
		printf("msg sent by server: %s\n",buf);
		sendto(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, len);
	}
}

int udp_server_handler(){
	int server_fd, ret;
	struct sockaddr_in ser_addr; 
	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_fd < 0){
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(SERVER_PORT);
	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
		printf("socket bind fail!\n");
		return -1;
	}
	udp_server(server_fd);
	close(server_fd);
	return 0;
}

int start_udp_server(){
	int pid;
	pid = fork();
	if( pid < 0 ){
		exit(1);

	}else if( pid == 0 ){

		udp_server_handler();

	}else{

		printf("Please input udpclient\n");

	}

}


void udp_client(int fd, struct sockaddr* dst){
	socklen_t len;
	struct sockaddr_in src;
	char buf[BUFF_LEN] = "hello UDP";
	len = sizeof(*dst);
	printf("msg sent by client: %s\n",buf);
	sendto(fd, buf, BUFF_LEN, 0, dst, len);
	memset(buf, 0, BUFF_LEN);
	recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);
	printf("msg from server: %s\n", buf);
}


int start_udp_client (int argc, char *argv[]){
	int client_fd;
	struct sockaddr_in ser_addr;
	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(SERVER_PORT);
	udp_client(client_fd, (struct sockaddr*)&ser_addr);
	close(client_fd);
	return 0;
}


#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#define MAX_IFS 64

int BringUpNetInterface()

{

	printf("Bring up interface:lo\n");

	struct sockaddr_in sa;

	struct ifreq ifreqlo;

	int fd;

	sa.sin_family = AF_INET;

	sa.sin_addr.s_addr = inet_addr("127.0.0.1");

	fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strncpy(ifreqlo.ifr_name, "lo",sizeof("lo"));

	memcpy((char *) &ifreqlo.ifr_addr, (char *) &sa, sizeof(struct sockaddr));

	ioctl(fd, SIOCSIFADDR, &ifreqlo);

	ioctl(fd, SIOCGIFFLAGS, &ifreqlo);

	ifreqlo.ifr_flags |= IFF_UP|IFF_LOOPBACK|IFF_RUNNING;

	ioctl(fd, SIOCSIFFLAGS, &ifreqlo);

	close(fd);

	

	printf("Bring up interface:eth0\n");

	sa.sin_family = AF_INET;

	sa.sin_addr.s_addr = inet_addr("192.168.40.254");

	fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strncpy(ifreqlo.ifr_name, "eth0",sizeof("eth0"));

	memcpy((char *) &ifreqlo.ifr_addr, (char *) &sa, sizeof(struct sockaddr));

	ioctl(fd, SIOCSIFADDR, &ifreqlo);

	ioctl(fd, SIOCGIFFLAGS, &ifreqlo);

	ifreqlo.ifr_flags |= IFF_UP|IFF_RUNNING;

	ioctl(fd, SIOCSIFFLAGS, &ifreqlo);

	close(fd);



	printf("List all interfaces:\n");

	struct ifreq *ifr, *ifend;

	struct ifreq ifreq;

	struct ifconf ifc;

	struct ifreq ifs[MAX_IFS];

	int SockFD;

 

 

	SockFD = socket(PF_INET, SOCK_DGRAM, 0);

 

 

	ifc.ifc_len = sizeof(ifs);

	ifc.ifc_req = ifs;

	if (ioctl(SockFD, SIOCGIFCONF, &ifc) < 0)

	{

		printf("ioctl(SIOCGIFCONF): %m\n");

		return 0;

	}

 

	ifend = ifs + (ifc.ifc_len / sizeof(struct ifreq));

	for (ifr = ifc.ifc_req; ifr < ifend; ifr++)

	{

		printf("interface:%s\n", ifr->ifr_name);

#if 0

		if (strcmp(ifr->ifr_name, "lo") == 0)

		{

			strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));

			ifreq.ifr_flags == IFF_UP;

			if (ioctl (SockFD, SIOCSIFFLAGS, &ifreq) < 0)

			{

			  printf("SIOCSIFFLAGS(%s): IFF_UP %m\n", ifreq.ifr_name);

			  return 0;

			}			

		}

#endif

		if (ifr->ifr_addr.sa_family == AF_INET)

		{

			strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));

			if (ioctl (SockFD, SIOCGIFHWADDR, &ifreq) < 0)

			{

			  printf("SIOCGIFHWADDR(%s): %m\n", ifreq.ifr_name);

			  return 0;

			}

 

			printf("Ip Address %s\n", inet_ntoa( ( (struct sockaddr_in *)  &ifr->ifr_addr)->sin_addr)); 

			printf("Device %s -> Ethernet %02x:%02x:%02x:%02x:%02x:%02x\n", ifreq.ifr_name,
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[0],
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[1],
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[2],
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[3],
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[4],
				(int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[5]);
		}
	}

	return 0;
}

int main(){
	BringUpNetInterface();
	PrintMenuOS();
	SetPrompt("MenuOS>>");
	MenuConfig("version","MenuOS V1.0(Based on Linux 3.18.6)",NULL);
	MenuConfig("quit","Quit from MenuOS",Quit);
	MenuConfig("replyhi", "Reply hi TCP Service", StartReplyhi);
	MenuConfig("hello", "Hello TCP Client", Hello);
	MenuConfig("udpserver", "udp server", start_udp_server);
	MenuConfig("udpclient", "udp client", start_udp_client);
        MenuConfig("httpclient","http client", httpclient);
	ExecuteMenu();
 }
