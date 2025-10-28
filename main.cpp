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
    std::vector<User> users = generateUsers(10);

    std::cout << "=== Generated Users ===\n";
    for (const auto& user : users) {
        user.print();
    }

    auto txs = generateTransactions(users, 20);
    std::cout << "\n=== Generated Transactions ===\n";
    std::cout << std::left << std::setw(20) << "Sender" << std::setw(20) << "Receiver" << std::setw(20) << "Amount" << "TransactionID" << '\n';
for (const auto& tx : txs) {
    std::cout << std::left
              << std::setw(20) << tx.getSender()
              << std::setw(20) << tx.getReceiver()
              << std::setw(20) << tx.getAmount()
              << tx.getID()
              << '\n';
}

        return 0;
}
