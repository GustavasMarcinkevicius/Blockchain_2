#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <algorithm>
#include "Klases.h"

std::vector<User> generateUsers(int n) {
    std::vector<User> users;
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<long long> balanceDist(100, 1'000'000);

    for (int i = 0; i < n; ++i) {
        std::string name = "User" + std::to_string(i + 1);
        std::string pubKey = "pubkey_" + std::to_string(i + 1);
        long long balance = balanceDist(rng);
        users.emplace_back(name, pubKey, balance);
    }
    return users;
}

std::vector<Transaction> generateTransactions(const std::vector<User>& users, int n) {
    std::vector<Transaction> transactions;
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int> userDist(0, users.size() - 1);
    std::uniform_int_distribution<long long> amountDist(1, 2000);

    for (int i = 0; i < n; ++i) {
        int senderIdx = userDist(rng);
        int receiverIdx;
        do { receiverIdx = userDist(rng); } while (receiverIdx == senderIdx);

        long long amount = amountDist(rng);

        if (amount > users[senderIdx].getBalance())
            continue;

        transactions.emplace_back(users[senderIdx].getPublicKey(),
                                  users[receiverIdx].getPublicKey(),
                                  amount);
    }
    return transactions;
}

std::vector<Transaction> pickRandomTransactions(const std::vector<Transaction>& allTxs, int count) {
    std::vector<Transaction> selected;

    if (allTxs.size() <= count)
        return allTxs;

    std::vector<int> indices(allTxs.size());
    for (int i = 0; i < allTxs.size(); ++i) indices[i] = i;

    std::mt19937_64 rng(std::random_device{}());
    std::shuffle(indices.begin(), indices.end(), rng);

    for (int i = 0; i < count; ++i) {
        selected.push_back(allTxs[indices[i]]);
    }

    return selected;
}
