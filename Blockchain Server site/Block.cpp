
//  Block.cpp
//  BlockChainExample

#include <stdio.h>
#include <string>
#include "Block.h"
#include "Details.h"


// Constructor with params
Block::Block(int idx, Details d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

// private functions
int Block::getIndex()
{
    return index;
}

/*
 Generates hash for current block
 - Includes previousHash in generation
 - ^ Very important
*/
size_t Block::generateHash()
{
    // creating string of transaction data
    std::string toHashS = data.chat + data.receiverKey + data.senderKey + std::to_string(data.timestamp);
   // printf("\n\n The cobined form is %s\n\n\n",toHashS);
    // 2 hashes to combine
    std::hash<std::string> tDataHash; // hashes transaction data string
    std::hash<std::string> prevHash; // re-hashes previous hash (for combination)

    // combine hashes and get size_t for block hash
    return tDataHash(toHashS) ^ (prevHash(std::to_string(previousHash)) << 1);
}

// Public Functions
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}
