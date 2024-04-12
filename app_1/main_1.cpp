#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "../code_1/Blockchain.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Welcome to BuffCUoin!" << endl;

    Blockchain buffCUoin;

    bool quit = false;
    while (!quit) {
        int option;
        string inputLine;
        string sender;
        string receiver;
        string Samount;
        string miner;
        string address;
        int amount;
        int balance;
        bool vaild;
        cout << "======Main Menu======" << endl;
        cout << "1. Add Transaction" << endl;
        cout << "2. Verify Blockchain" << endl;
        cout << "3. Mine Pending Transactions" << endl;
        cout << "4. Print BlockChain" << endl;
        cout << "5. Get Balance of Address" << endl;
        cout << "6. Quit" << endl;
        cout << "->  ";
        cin >> inputLine;
        option = stoi(inputLine);
        switch(option) {
            case 1:
                cout << "Enter sender address: ";
                cin >> sender;
                cout << "Enter receiver address: ";
                cin >> receiver;
                cout << "Enter amount: ";
                cin >> Samount;
                amount = stoi(Samount);

                buffCUoin.addTransaction(sender, receiver, amount);
                break;

            case 2:
                vaild = buffCUoin.isChainValid();
                if(vaild){
                    cout << "Blockchain is valid." << endl;
                }
                else{
                    cout << "Blockchain is not valid." << endl;
                }
                break;
            
            case 3:
                cout << "Enter miner address: ";
                cin >> miner; 
                buffCUoin.minePendingTransactions(miner);
                cout << miner << " has succesfully mined the block." << endl;
                break;

            case 4:
                buffCUoin.prettyPrint();
                break;

            case 5:
                cout << "Enter address: ";
                cin >> address;
                balance = buffCUoin.getBalanceOfAddress(address);
                cout << address << " has " << balance << " BuffCUoins." <<endl;
                break;
            
            case 6:
                quit = true;
                cout << "Goodbye..." << endl;
                break;

            default:
                cout << "Not a valid input. Please input a number 1-5." << endl;
                break;

        }
    }
    
    return 0;
}