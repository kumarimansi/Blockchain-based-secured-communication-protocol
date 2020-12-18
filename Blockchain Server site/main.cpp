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


using namespace std;
#include <iostream>
#include <ctime>
#include <vector>
#include "Details.h"
#include "Block.h"
#include "Blockchain.h"

using namespace std;


char Buffer[128],usname[128],sender[128];

//HACKING BLOCKCHAIN
void hack(Blockchain awesomechain)
{
    system("cls");
    cout<<"Try to hack this last block as this can be a vulnerable one.\n\n";
    string newdata;
    Block *hackBlock = awesomechain.getLatestBlock();
    cout<<"Enter the New data to edit/change the last block: ";
    cin>>newdata;
    hackBlock->data.chat = newdata;
    system("cls");

    cout<<"\t\t_______After altering data of last block\n________";
    awesomechain.printChain();

}

//CREATING BLOCKCHAIN
void create_it(Blockchain *awesomechain,time_t data1Time,char *Buffer,int x)
{
                if(x==1){
                         Details data1(Buffer, sender, usname, time(&data1Time));
                         awesomechain->addBlock(data1);
                         cout<<"\n";
                }
                else{
                         Details data1(Buffer, usname, sender, time(&data1Time));
                        awesomechain->addBlock(data1);
                        cout<<"\n";
                }

}

//CONVERSATION FUNCTION
Blockchain convo(SOCKET msgsock,Blockchain awesomechain,time_t data1Time)
{
                    system("cls");

                cout<<"_____________________________________________________________________________________\n";
                cout<<"\t\t\t\t\t"<<sender<<" is ONLINE..."<<endl;
                cout<<"^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^\n";
    while(1){



            int retval = recv(msgsock, Buffer, sizeof(Buffer), 0);

                if (retval == SOCKET_ERROR)
                      {
                    printf("Server: recv() failed: error %d\n", WSAGetLastError());
                    closesocket(msgsock);
                    continue;
                }


                if (retval == 0)
                      {
                    printf("Server: Client closed connection.\n");
                    closesocket(msgsock);
                      continue;
                    }


                cout<<"\t\t\t\t\t\t\t"<<Buffer<<"\t||"<<endl;
                cout<<"\t\t\t\t\t\t\t----------------"<<sender<<"\t||"<<endl;

            create_it(&awesomechain,data1Time,Buffer,1);

            if (strncmp("exit", Buffer, 4) == 0) {
                            printf("Server Exit...\n");
                            getch();
                            break;
                        }


                cout<<"Type your message: ";
                gets(Buffer);

                retval = send(msgsock, Buffer, sizeof(Buffer), 0);
                create_it(&awesomechain,data1Time,Buffer,0);

                      if (retval == SOCKET_ERROR)
                      {
                             fprintf(stderr,"Server: send() failed: error %d\n", WSAGetLastError());
                       }


            if (strncmp("exit", Buffer, 4) == 0) {
                            printf("Server Exit...\n");
                            getch();
                            break;
                        }

            cout<<"--------------------------------------------------------------------------------------\n";

    }
                system("cls");
                awesomechain.printChain();
                getch();
                hack(awesomechain);
}


int main(int argc, char **argv)
{
    Blockchain awesomechain;         // Start Blockchain
    time_t data1Time;               // Data for first block

    char *ip_address= NULL;
    unsigned short port=DEFAULT_PORT;
    int retval;
    int fromlen;
    int i;
    int socket_type = DEFAULT_PROTO;
    struct sockaddr_in local, from;

    WSADATA wsaData;
    SOCKET listen_socket, msgsock;


    // Request Winsock version 2.2

    cout<<"Enter your custom user name: ";
    gets(usname);
    cout<<usname;
    getch();

    system("cls");
    if ((retval = WSAStartup(0x202, &wsaData)) != 0)
       {
        fprintf(stderr,"Server: WSAStartup() failed with error %d\n", retval);
        WSACleanup();
        return -1;
    }

    else
       printf("Server: WSAStartup() is OK.\n");



    local.sin_family = AF_INET;
    local.sin_addr.s_addr = (!ip_address) ? INADDR_ANY:inet_addr(ip_address);
   /* Port MUST be in Network Byte Order */
    local.sin_port = htons(port);
    // TCP socket
    listen_socket = socket(AF_INET, socket_type,0);



    if (listen_socket == INVALID_SOCKET){
        fprintf(stderr,"Server: socket() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    else
       printf("Server: socket() is OK.\n");


    if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
       {
        fprintf(stderr,"Server: bind() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    else
              printf("Server: bind() is OK.\n");


    if (socket_type != SOCK_DGRAM)
       {
        if (listen(listen_socket,5) == SOCKET_ERROR)
              {
            fprintf(stderr,"Server: listen() failed with error %d\n", WSAGetLastError());
            WSACleanup();
            return -1;
        }
       else
              printf("Server: listen() is OK.\n");
    }
    printf("Server: %s: I'm listening and waiting for the connection\non port %d, protocol %s\n", argv[0], port, (socket_type == SOCK_STREAM)?"TCP":"UDP");
printf("I am listening \n\n");

while(1){
        fromlen =sizeof(from);
        if (socket_type != SOCK_DGRAM)

              {

            msgsock = accept(listen_socket, (struct sockaddr*)&from, &fromlen);

            if (msgsock == INVALID_SOCKET)

           {
                fprintf(stderr,"Server: accept() error %d\n", WSAGetLastError());
                WSACleanup();
                return -1;
            }

           else
              printf("Server: accept() is OK.\n");

              printf("Server: accepted connection from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port)) ;
        }

        else
            msgsock = listen_socket;


retval = recv(msgsock, Buffer, sizeof(Buffer), 0);

if(retval==SOCKET_ERROR)
    cout<<"Sender name not known\n";

 strcpy(sender, Buffer);
send(msgsock, usname, sizeof(usname), 0);



convo(msgsock,awesomechain,data1Time);

}
getch();
    return 0;
}
