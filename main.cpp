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

// int main() {
//     std::vector<User> users = generateUsers(1000);


//     //GENERATED USERS PRINT
//     std::cout << "=== Generated Users ===\n";
//     std::cout << std::left << std::setw(20) << "Users"  << std::setw(25) << "Public Key" << "Balance" << '\n';
//     std::cout << "-----------------------------------------------------------------------------------" << '\n';
//     int count = 0;
//     for (const auto& user : users) {
//         if (count++ == 10) break;
//         user.print();
//     }

//     std::cout << std::left << std::setw(20) << "..."  << std::setw(25) << "..." << "..." << '\n';


//     auto txs = generateTransactions(users, 10000);


//     //NEW TRANSACTIONS PRINT
//     std::cout << "\n=== Generated Transactions ===\n";
//     std::cout << std::left << std::setw(20) << "Sender" << std::setw(20) << "Receiver" << std::setw(20) << "Amount" << "TransactionID" << '\n';
//     std::cout << "----------------------------------------------------------------------------------------------------------------------------" << '\n';
//     count = 0;
//     for (const auto& tx : txs) {
//         if (count++ == 10) break;
//     std::cout << std::left << std::setw(20) << tx.getSender() << std::setw(20) << tx.getReceiver() << std::setw(20) << tx.getAmount() << tx.getID()<< '\n';
// }
//     std::cout << std::left << std::setw(20) << "..."  << std::setw(20) << "..." << std::setw(20) << "..." << "..." << '\n';



// Blockchain bc;

// std::cout << '\n';
// std::cout << "\n=== Generated blocks ===\n";


// int difficulty = 3;

// while (!txs.empty()) {
//     std::vector<Transaction> candidateTxs = pickRandomTransactions(txs, 100); 
//     candidateTxs = filterValidTransactions(candidateTxs, users);
    
//     std::string merkleRoot = computeMerkleRoot(candidateTxs);
//     std::string prevHash = bc.getLastBlock().getHash();
//     if (prevHash.empty())
//         prevHash = std::string(64, '0');

//     Block candidate(bc.getChain().size() + 1, candidateTxs, prevHash);

//     if (tryMineBlock(candidate, prevHash, merkleRoot, difficulty, 1000)) {
//         processBlockTransactions(candidateTxs, users);
//         bc.addBlock(candidate);

//         for (const auto& tx : candidateTxs) {
//             txs.erase(std::remove_if(txs.begin(), txs.end(),
//                         [&](const Transaction& t){ return t.getID() == tx.getID(); }),
//                       txs.end());
//         }

//         std::cout << "Mined Block #" << bc.getChain().size() 
//                   << " | Nonce: " << candidate.getNonce() << "\n";

//     std::cout << "Remaining transactions in pool: " << txs.size() << '\n';
//     }
// }



// std::cout << "Blockchain size: " << bc.getChain().size() << " block(s)" << '\n';
// std::cout << "Remaining transactions in pool: " << txs.size() << std::endl;


// bc[49].printBlockTransactions();

//     // print users after transactions
//     std::cout << "=== Users after Transactions ===\n";
//     std::cout << std::left << std::setw(20) << "Users"  << std::setw(25) << "Public Key" << "Balance" << '\n';
//     std::cout << "-----------------------------------------------------------------------------------" << '\n';
//     count = 0;
//     for (const auto& user : users) {
//         if (count++ == 10) break;
//         user.print();
//     }


// return 0;
// }

int main() {
    std::vector<User> users = generateUsers(1000);
    std::vector<Transaction> txs = generateTransactions(users, 10000);
    Blockchain bc;

    mineCandidateBlocks(bc, txs, users, 100, 2);

    std::cout << "Blockchain size: " << bc.getChain().size() << " block(s)" << '\n';
    std::cout << "Remaining transactions in pool: " << txs.size() << '\n';

    return 0;
}