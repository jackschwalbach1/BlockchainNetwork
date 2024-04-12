#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    Transaction genesis("BFC","BFC",0);
    pending.push_back(genesis);

    Block gBlock(pending, time(nullptr), "In the beginning..");
    chain.push_back(gBlock);

    Transaction freeMoney("BFC","make money by mining",0);
    pending.push_back(freeMoney);

    difficulty = 4;
    miningReward = 10;
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(string src, string dst, int coins) {
    // TODO
    if(getBalanceOfAddress(src) > coins || src == "BFC"){
        Transaction newt = Transaction(src,dst,coins);
        pending.push_back(newt);
        cout << src << " has paid "<< dst << " " << coins << " BuffCUoins" << endl;
    }
    else{
      cout << "Cannot add transaction, " << src << " has insufficient coins" << endl;
    }
}

bool Blockchain::isChainValid() { 
    // TODO
    bool isValid = true;
    for(int i = 0; i < chain.size()-1; i++){
        if(chain[i].getHash() != chain[i+1].getPreviousHash()){
            isValid = false;
        }
    }
    return isValid;

}

bool Blockchain::minePendingTransactions(string minerAddress) {
    // TODO
    //reward miner
   addTransaction("BFC", minerAddress, miningReward);

   Block newBlock = Block(pending, time(nullptr), getLatestBlock().getHash());
    newBlock.mineBlock(difficulty);
  
    //push newBlock to chain
   chain.push_back(newBlock);
   
   //clear pending list
    pending.erase(pending.begin(), pending.end());

   return true;
}

int Blockchain::getBalanceOfAddress(string address) {
    // TODO
    //traversing the entire block chain to calculate balance
    int balance = 0;
    for(int i = 0; i < chain.size(); i++){
        Block b = chain[i];
        for(int j = 0; j < b.getTransactions().size(); j++){
             if(b.getTransactions()[j].getReceiver() == address){
                 balance += b.getTransactions()[j].getAmount();
 
             }
             if(chain[i].getTransactions()[j].getSender() == address){
                balance -= b.getTransactions()[j].getAmount();
             }
        }
    }

    // cout << address << " has " << balance << " coins" << endl;
    return balance;
}

void Blockchain::prettyPrint() {
    // TODO
    cout << "\n";
    for(int i = 0; i < chain.size(); i++){
        for(int j = 0; j < chain[i].getTransactions().size(); j++){
             if((j+1) == chain[i].getTransactions().size())
             {
                 cout << chain[i].getTransactions()[j].toString();
             }
             else{
                cout << chain[i].getTransactions()[j].toString() << " ";
             }
             
        }

        if((i+1) != chain.size()){
           cout << "\n     |" << endl;
           cout << "     v" << endl;
        }
        
    }
    cout << "\n" << endl;;
}


int Blockchain::getminingReward(){
   return miningReward;
}