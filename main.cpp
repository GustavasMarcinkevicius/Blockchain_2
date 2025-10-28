#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include "Funkcijos.h"
#include "Klases.h"
#include <iomanip>

int main() {
    std::vector<User> users = generateUsers(1000);


    //GENERATED USERS PRINT
    std::cout << "=== Generated Users ===\n";
    std::cout << std::left << std::setw(20) << "Users"  << std::setw(25) << "Public Key" << "Balance" << '\n';
    std::cout << "-----------------------------------------------------------------------------------" << '\n';
    int count = 0;
    for (const auto& user : users) {
        if (count++ == 10) break;
        user.print();
    }

    std::cout << std::left << std::setw(20) << "..."  << std::setw(25) << "..." << "..." << '\n';


    auto txs = generateTransactions(users, 10000);


    //NEW TRANSACTIONS PRINT
    std::cout << "\n=== Generated Transactions ===\n";
    std::cout << std::left << std::setw(20) << "Sender" << std::setw(20) << "Receiver" << std::setw(20) << "Amount" << "TransactionID" << '\n';
    std::cout << "-----------------------------------------------------------------------------------" << '\n';
    count = 0;
    for (const auto& tx : txs) {
        if (count++ == 10) break;
    std::cout << std::left << std::setw(20) << tx.getSender() << std::setw(20) << tx.getReceiver() << std::setw(20) << tx.getAmount() << tx.getID()<< '\n';
}
    std::cout << std::left << std::setw(20) << "..."  << std::setw(20) << "..." << std::setw(20) << "..." << "..." << '\n';




    
    // //TRANSACTION FOR NEW BLOCK PRINT
    // std::cout << "\n=== Transactions for New Block ===\n";
    // std::cout << std::left << std::setw(20) << "Sender" << std::setw(20) << "Receiver" << "Amount" <<'\n';
    // std::cout << "-----------------------------------------------------------------------------------" << '\n';
    // count = 0;
    // for (const auto& tx : blockTxs) {
    //     if (count++ == 10) break;
    //     std::cout << std::left << std::setw(20) << tx.getSender() << std::setw(20) << tx.getReceiver()
    //             << tx.getAmount() << '\n';
    // }
    // std::cout << std::left << std::setw(20) << "..."  << std::setw(20) << "..." << "..." << '\n';

Blockchain bc;

while (!txs.empty()) {
    int count = std::min(100, (int)txs.size());
    std::vector<Transaction> blockTxs(txs.begin(), txs.begin() + count);
    std::string prevHash = bc.getLastBlock().getHash();
    Block newBlock(bc.getChain().size() + 1, blockTxs, prevHash);
    newBlock.setHash("000fakehash"); 

    bc.addBlock(newBlock);
    txs.erase(txs.begin(), txs.begin() + count);

    std::cout << " | Hash: " << newBlock.getHash()   << " | Prev Hash: " << newBlock.getPrevHash() << " ===\n";

    // newBlock.printBlockTransactions();
}

std::cout << "Blockchain size: " << bc.getChain().size() << " block(s)" << '\n';
std::cout << "Remaining transactions in pool: " << txs.size() << std::endl;

return 0;
}
