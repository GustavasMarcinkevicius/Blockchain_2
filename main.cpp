#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include "Funkcijos.h"
#include "Klases.h"

int main() {
    std::vector<User> users = generateUsers(10);

    std::cout << "=== Generated Users ===\n";
    for (const auto& user : users) {
        user.print();
    }

    return 0;

    auto txs = generateTransactions(users, 20);
    std::cout << "\n=== Generated Transactions ===\n";
    for (const auto& tx : txs) {
        std::cout << "Sender: " << tx.getSender()
                  << " -> Receiver: " << tx.getReceiver()
                  << " | Amount: " << tx.getAmount()
                  << " | ID: " << tx.getID() << '\n';
    }
}
