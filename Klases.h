#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "Hash.h"

// ===== User class =====
class User {
private:
    std::string name;
    std::string public_key;
    long long balance;

public:
    User(const std::string& n, const std::string& pk, long long b)
        : name(n), public_key(pk), balance(b) {}

    std::string getName() const { return name; }
    std::string getPublicKey() const { return public_key; }
    long long getBalance() const { return balance; }

    void setBalance(long long b) { balance = b; }
    void changeBalance(long long amount) { balance += amount; }

    void print() const {
    std::cout << std::left
              << std::setw(20) << name
              << std::setw(25) << public_key
              << std::setw(15) << balance
              << '\n';
}


};

// ===== Transaction class =====
class Transaction {
private:
    std::string sender;
    std::string receiver;
    long long amount;
    std::string transaction_id;

public:
    Transaction(const std::string& s, const std::string& r, long long a)
        : sender(s), receiver(r), amount(a) {

        transaction_id = hash(s + r + std::to_string(a));


        // std::string transaction_id_unhashed = s + r + std::to_string(a);
        // transaction_id = hash(transaction_id_unhashed);
    }

    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    long long getAmount() const { return amount; }
    std::string getID() const { return transaction_id; }
};

// ===== Block class =====
class Block {
private:
    int index;
    std::vector<Transaction> transactions;
    std::string prev_hash;
    long long nonce;
    int difficulty;
    std::string hash;
    std::time_t timestamp;

public:
    Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash, int diff = 3)
        : index(idx), transactions(txs), prev_hash(prevHash), difficulty(diff), nonce(0) {
        timestamp = std::time(nullptr);
    }

    std::string getHash() const { return hash; }
    std::string getPrevHash() const { return prev_hash; }
    const std::vector<Transaction>& getTransactions() const { return transactions; }


    void setHash(const std::string& h) { hash = h; }

        void printBlockTransactions(int maxPrint = 100) const {
        std::cout << std::left
                  << std::setw(20) << "Sender"
                  << std::setw(20) << "Receiver"
                  << std::setw(15) << "Amount"
                  << "Transaction ID" << '\n';
        std::cout <<  "------------------------------------------------------------------------------------------------------------------------" << '\n';

        int printCount = std::min(maxPrint, (int)transactions.size());
        for (int i = 0; i < printCount; ++i) {
            const auto& tx = transactions[i];
            std::cout << std::left
                      << std::setw(20) << tx.getSender()
                      << std::setw(20) << tx.getReceiver()
                      << std::setw(15) << tx.getAmount()
                      << tx.getID() 
                      << '\n';
        }
    }

    void setNonce(long long n) { nonce = n; }
    long long getNonce() const { return nonce; }

};

// ===== Blockchain class =====
class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain() {}

    void addBlock(const Block& block) {
        chain.push_back(block);
    }

    Block getLastBlock() const {
        if (!chain.empty()) return chain.back();
        return Block(0, {}, "0");
    }

    const std::vector<Block>& getChain() const { return chain; }
    Block& operator[](size_t index) {
    return chain[index];
    }

    const Block& operator[](size_t index) const {
    return chain[index];
    }
};
