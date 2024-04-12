#include<iostream>
#include <sstream>


#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1;
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

void Block::setPreviousHash(string _previousHash) {
    // TODO
    previousHash = _previousHash;
}

string Block::calculateHash() {
    // TODO
    string transactionsPart = "";
    for(int i = 0; i < transactions.size(); i++){
        transactionsPart.append(transactions[i].toString());
    }
    
    string noncePart = to_string(nonce);

    string timePart = asctime(localtime(&timestamp));

    string toBeHashed = noncePart.append(transactionsPart.append(timePart.append(previousHash)));

    string hash = sha256(toBeHashed);

    return hash;
}

void Block::mineBlock(unsigned int difficulty) {
    // TODO
    string zeros = "0000000000000000000000000000000";
    string hash2 = "";
    while(hash2.substr(0, difficulty) != zeros.substr(0, difficulty)){
        hash2 = calculateHash();
        nonce++;
    }

    hash = hash2;
    
}

string Block::toString() {
    // TODO
    return "";
}

vector<Transaction> Block::getTransactions(){
    return transactions;
}

string Block::getPreviousHash(){
    return previousHash;
}

string Block::getHash(){
    return hash;
}