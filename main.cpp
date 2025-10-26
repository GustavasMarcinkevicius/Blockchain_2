#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>

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
        std::cout << "Name: " << name
                  << " | Public Key: " << public_key
                  << " | Balance: " << balance << '\n';
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
        transaction_id = s + r + std::to_string(a); // vėliau galima pakeisti į hash
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

    void mineBlock() {
        hash = "000fakehash"; //nepamirst pakeist
    }
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
        if (chain.empty()) {
            throw std::runtime_error("Blockchain is empty!");
        }
        return chain.back();
    }
};

// ===== User generation =====
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

// ===== Main =====
int main() {
    std::vector<User> users = generateUsers(10);

    std::cout << "=== Generated Users ===\n";
    for (const auto& user : users) {
        user.print();
    }

    return 0;
}
