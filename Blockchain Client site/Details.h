//
//  Details.h
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//
#include<iostream>
#ifndef Details_h
#define Details_h
using namespace std;
struct Details
{
    std::string chat;
    std::string senderKey;
    std::string receiverKey;
    time_t timestamp;

    Details(){};

    Details(std::string Buff, std::string sender, std::string receiver, time_t time)
    {
        chat = Buff;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
    };
    public:
    void print_it()
    {
        cout<<chat<<endl;
    }
};

#endif /* TransactionData_h */
