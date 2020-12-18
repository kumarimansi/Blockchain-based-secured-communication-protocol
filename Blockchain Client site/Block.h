//
//  Block.h
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#ifndef Block_h
#define Block_h

#include "Details.h"

// Block Class
class Block
{
private:
    int index;
    size_t blockHash;
    size_t previousHash;
    size_t generateHash();

public:
    // Constuctor
    Block(int idx, Details d, size_t prevHash);

    // Get Index
    int getIndex();

    // Get Original Hash
    size_t getHash();

    // Get Previous Hash
    size_t getPreviousHash();

    // Transaction Data
    // Would ordinarily be a private member with a "getter": getData()
    Details data;

    // Validate Hash
    bool isHashValid();
};

#endif /* Block_h */
