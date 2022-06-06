#include <HMemoryTools.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <regex.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <pthread.h>

#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/prctl.h>
#include <assert.h>
#include <sys/socket.h>
#define SERVER_PORT 56636
#include <netinet/in.h>
#include <arpa/inet.h>
#define printf(...)      \
	printf(__VA_ARGS__); \
	fflush(stdout);
using namespace std;
long int *posAddr = (long int *)malloc(8 * 100);
long int jzAddr = (long int)malloc(8 * 10);
long int zmAddr = (long int)malloc(8 * 10);
long int jdAddr = (long int)malloc(8 * 10);
int jk = 1;
int zgs = 0;
float mzfx = 0;
float matrix[50];
void Search_Matrix();
void Search_Object();
FILE *F;
FILE *yz;
float px;  // width
float py;  // height
float zxx, zxy;
float Bar;
int main(int argc, char **argv)
{
    SetTar("com.tencent.tmgp.pubgmhd");
	printf("_DEBUGCXX  argc = %d argv[1] = %s\n", argc, argv[1]);
	long defaultPort = SERVER_PORT;
	if (argc == 2)
	{
		sscanf(argv[1], "[%ld]", &defaultPort);
		printf("_DEBUGCXX  defaultPort = %d\n", defaultPort);
	}

	int clientSocket;
	struct sockaddr_in serverAddr;

	char sendbuf[200];
	char recvbuf[200];

	int iDataNum;
	int i = 0;
	int ret = 1;

	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("error while creating socket");
		return 1;
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(defaultPort);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connection 0");
		return 1;
	}
	 sleep(1);
     px = 2480.0;
     py = 1080.0;
     Bar = 89;
     zxx = px / 2.0 - Bar;
     zxy = py / 2.0;
     py = py / 2.0;
     px = px / 2.0;
     char data[2024] = { 0 };
     char cs[1024];
     char staData[1024] = "";
     char res[64] = "[0-9]+";
     char data2[1024] = { 0 };
     char status[64] = { 0 };
     char status2[64] = { 0 };
    // int ret;
     int staRet;
     int staRet2;
     FILE *p = NULL;
     char buf[64] = { 0 };
     SetSearchRange(A_ANONMYOUS);
     int a = 1;
     int fdf = -1;
     char iszm[2] = "";
     char iszmm[5] = "";
     float my_x;
     float my_y;
     float my_z;
     BypassGameSafe();
     Search_Matrix();
     std::thread t(Search_Object);
     for (;;)
     {
          int fd = -1;
          int i;
          FREEZE bu;
          while (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
          {
           	char str[1024];
	       	char con[1024] = "";
               for (i = 0; i < 16; i++)
               {
                    int a = 1;
                    float fhjz = GetAddress_FLOAT(jzAddr + i * 4);
                    matrix[i] = fhjz;
               }
               char aaa[2048] = "";
               char b[164];
               int zbs = 0;
               int xxxtmp = 9999;
               int tmpzx = 0;
               float Distance;
               
               for (i = 0; i < ResCount; i++)
               {
                    if (getPID("com.tencent.tmgp.pubgmhd")==-1){
                    sleep(0.01);
		            send(clientSocket, ",,,,,,,", 7, 0);
		            close(clientSocket);
		            exit(1);
		            }
                    int zms = 0;
                    int xxx[ResCount];
                    float hp = GetAddress_FLOAT(posAddr[i] - 5);
                    float obj_x = GetAddress_FLOAT(posAddr[i] - 2);
                    float obj_y = GetAddress_FLOAT(posAddr[i] - 3);
                    float obj_z = GetAddress_FLOAT(posAddr[i] - 4);
                    float isr = GetAddress_FLOAT(posAddr[i] - 1);
                    if (isr != 0.0)
                    {
                         continue;
                    }
                    float z_x = GetAddress_FLOAT(jzAddr - 8);
                    float z_y = GetAddress_FLOAT(jzAddr - 7);
                    float z_z = GetAddress_FLOAT(jzAddr - 6);
                    int rjb = GetAddress_DWORD(posAddr[i] - 9);
                    float camear_z = matrix[3] * obj_x + matrix[7] * obj_y + matrix[11] * obj_z + matrix[15];
                    float r_x = px + (matrix[0] * obj_x + matrix[4] * obj_y + matrix[8] * obj_z + matrix[12]) / camear_z * px;
                    float r_y = py - (matrix[1] * obj_x + matrix[5] * obj_y + matrix[9] * (obj_z - 5) + matrix[13]) / camear_z * py;
                    float r_w = py - (matrix[1] * obj_x + matrix[5] * obj_y + matrix[9] * (obj_z + 205) + matrix[13]) / camear_z * py;
                    double m = sqrt(pow(obj_x - z_x, 2) + pow(obj_y - z_y, 2) + pow(obj_z - z_z, 2)) * 0.01;
                    if (m > 800.0)
                    {
                         continue;
                    }
                    sprintf(b, "%f,%f,%f,%f,%f,%f,%d,%d;\n", 
                    r_x - (r_y - r_w) / 4 - 80,// x
                    r_y, //y
                    (r_y - r_w) / 2,// w
                    r_y - r_w,// h
                    m-3,// m
                    hp// hp
                    );
                    strcat(con, b);
               }
               sleep(0.01);
		       send(clientSocket, con, strlen(con), 0);
          }
          close(clientSocket);
          return 1;
          exit(1);
     }
}


void Search_Matrix()
{
    int gs;
    void *jg;
    PMAPS buf;
    SetSearchRange(A_ANONMYOUS);
    MemorySearch("1.00010001659", &gs, FLOAT);
    MemoryOffset("-2147483648", 0x378, &gs, DWORD);
    buf = GetResults();
    jzAddr = buf->addr + 152;
    free(buf->value);
    ClearResults();
}

void Search_Object()
{
    int n;
    for (;;)
    {
        n++;
        int zgs = 0;
        MemorySearch("479.5", &zgs, FLOAT);
        MemoryOffset("3", 4, &zgs, FLOAT);
        int i;
        float ax;
        PMAPS zbdz = Res;
        for (i = 0; i < ResCount; i++)
        {
            posAddr[i] = zbdz->addr;
            zbdz = zbdz->next;
        }
        if (zgs == 0)
        ClearResults();
        sleep(2);
     }
}