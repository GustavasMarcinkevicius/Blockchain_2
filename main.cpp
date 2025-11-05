#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include "Funkcijos.h"
#include "Klases.h"
#include <iomanip>
#include "Hash.h"


int main() {


    //USERS
    std::vector<User> users = generateUsers(1000);
    std::cout << "=== Generated Users ===\n";
    std::cout << std::left << std::setw(20) << "Users"  << std::setw(25) << "Public Key" << "Balance" << '\n';
    std::cout << "-----------------------------------------------------------------------------------" << '\n';
    int count = 0;
    for (const auto& user : users) {
        if (count++ == 10) break;
        user.print();
    }
    std::cout << std::left << std::setw(20) << "..."  << std::setw(25) << "..." << "..." << '\n';



    //TRANSACTIONS
    std::vector<Transaction> txs = generateTransactions(users, 10000);
    std::cout << "\n=== Generated Transactions ===\n";
    std::cout << std::left << std::setw(20) << "Sender" << std::setw(20) << "Receiver" << std::setw(20) << "Amount" << "TransactionID" << '\n';
    std::cout << "----------------------------------------------------------------------------------------------------------------------------" << '\n';
    count = 0;
    for (const auto& tx : txs) {
        if (count++ == 10) break;
    std::cout << std::left << std::setw(20) << tx.getSender() << std::setw(20) << tx.getReceiver() << std::setw(20) << tx.getAmount() << tx.getID()<< '\n';
}
    std::cout << std::left << std::setw(20) << "..."  << std::setw(20) << "..." << std::setw(20) << "..." << "..." << '\n';





    Blockchain bc;

    mineCandidateBlocks(bc, txs, users, 5000, 3); //.., time(ms), difficulty

    std::cout << "Blockchain size: " << bc.getChain().size() << " block(s)" << '\n';
    std::cout << "Remaining transactions in pool: " << txs.size() << '\n';
    std::cout << '\n';
    printBlockInfo(bc[49]);

    return 0;
}