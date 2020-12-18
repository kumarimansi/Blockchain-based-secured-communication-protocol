/* Server program example for IPv4 */

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include<conio.h>

#define DEFAULT_PORT 2002
// default TCP socket type
#define DEFAULT_PROTO SOCK_STREAM


//using namespace std;
#include <iostream>
#include <ctime>
#include <vector>


#include "Details.h"
#include "Block.h"
#include "Blockchain.h"

char Buffer[128],usname[128],sender[128];


void hack(Blockchain awesomechain)
{
    getch();
    system("cls");
    cout<<"Try to hack the last message as it can be vulnerable block...\n\n";
    string newdata;
    Block *hackBlock = awesomechain.getLatestBlock();
    cout<<"Enter the New data to edit the last block: ";
    cin>>newdata;
    hackBlock->data.chat = newdata;
    system("cls");

    cout<<"\t\t_______After altering data of last block\n________";
    awesomechain.printChain();

}


void create_it(Blockchain *awesomechain,time_t data1Time,char *Buffer,int x)
{
                if(x==1){
                         Details data1(Buffer, sender, usname, time(&data1Time));
                         awesomechain->addBlock(data1);
                }
                else{
                         Details data1(Buffer, usname, sender, time(&data1Time));
                        awesomechain->addBlock(data1);
                }

}

void convo(SOCKET conn_socket,Blockchain awesomechain,time_t data1Time)
{
    system("cls");

    cout<<"_____________________________________________________________________________________\n";
    cout<<"\t\t\t\t\t"<<sender<<" is ONLINE ..."<<endl;
    cout<<"-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^^-^-^-^-^-\n";



   char Buffer[128];
   while(1){

        cout<<"Type your message: ";
        gets(Buffer);

        int retval = send(conn_socket, Buffer, sizeof(Buffer), 0);

        if (retval == SOCKET_ERROR)
        {
            cout<<stderr<<"Client: send() failed: error %d.\n"<< WSAGetLastError()<<endl;
            WSACleanup();

        }

            create_it(&awesomechain,data1Time,Buffer,0);

            if (strncmp("exit", Buffer, 4) == 0) {
                            printf("Server Exit...\n");
                            getch();
                            break;
                        }

        retval = recv(conn_socket, Buffer, sizeof(Buffer), 0);

        if (retval == SOCKET_ERROR)
       {
            cout<<stderr<<"Client: recv() failed: error %d.\n"<<WSAGetLastError()<<endl;
            closesocket(conn_socket);
            WSACleanup();

        }

        if (retval == 0)

       {
            cout<<"Client: Server closed connection.\n"<<endl;
            closesocket(conn_socket);
            WSACleanup();

        }


            create_it(&awesomechain,data1Time,Buffer,1);


                cout<<"\t\t\t\t\t\t\t"<<Buffer<<"\t||"<<endl;
                cout<<"\t\t\t\t\t\t\t----------------"<<sender<<"\t||"<<endl;
                cout<<"--------------------------------------------------------------------------------------\n";

                        if (strncmp("exit", Buffer, 4) == 0) {
                            printf("Server Exit...\n");
                            getch();
                            break;

                        }
   }
                system("cls");
                awesomechain.printChain();
                hack(awesomechain);
}

int main(int argc, char **argv)
{
     // Start Blockchain
    Blockchain awesomechain;
    time_t data1Time;

    char Buffer[128];


    char *server_name= "localhost";
    unsigned short port = DEFAULT_PORT;
    int retval, loopflag = 0;
    int i, loopcount, maxloop=-1;
    unsigned int addr;

    int socket_type = DEFAULT_PROTO;
    struct sockaddr_in server;
    struct hostent *hp;

    WSADATA wsaData;

    SOCKET  conn_socket;

    cout<<"Enter your custom user name: ";
    gets(usname);
    cout<<usname;

    if ((retval = WSAStartup(0x202, &wsaData)) != 0)
    {
       cout<<"Client: WSAStartup() failed with error \n"<<stderr<<retval;
        WSACleanup();
        return -1;
    }

    else
       cout<<"Client: WSAStartup() is OK.\n";

    // Attempt to detect if we should call gethostbyname() or gethostbyaddr()

    if (isalpha(server_name[0]))
    {   // server address is a name
       hp = gethostbyname(server_name);
    }

    else
    { // Convert nnn.nnn address to a usable one
       addr = inet_addr(server_name);
        hp = gethostbyaddr((char *)&addr, 4, AF_INET);
    }

    if (hp == NULL )
    {
        cout<<stderr<<"Client: Cannot resolve address "<<server_name<< WSAGetLastError();
        WSACleanup();
        exit(1);
    }

    else
       cout<<"Client: gethostbyaddr() is OK.\n";

    // Copy the resolved information into the sockaddr_in structure

    memset(&server, 0, sizeof(server));
    memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(port);


    conn_socket = socket(AF_INET, socket_type, 0); /* Open a socket */
    if (conn_socket <0 )
    {
        cout<<stderr<<"   Client: Error Opening socket: Error "<<WSAGetLastError();
        WSACleanup();
        return -1;
    }
    else
       cout<<"Client: socket() is OK.\n";

    cout<<"Client: Client connecting to: "<< hp->h_name<<endl;

    if (connect(conn_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)

    {
        cout<<stderr<<"Client: connect() failed: "<< WSAGetLastError();
        WSACleanup();
        return -1;
    }

    else

    cout<<"Client: connect() is OK.\n";

    loopcount = 0;

    send(conn_socket, usname, sizeof(usname), 0);
    retval = recv(conn_socket, Buffer, sizeof(Buffer), 0);

    if(retval==SOCKET_ERROR)
        cout<<"Sender name not known\n";

    strcpy(sender, Buffer);

    convo(conn_socket,awesomechain,data1Time);

    getch();
    return 0;
}
