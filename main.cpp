#include <string>
#include <vector>
#include <ctime>

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
};

#include <string>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    long long amount;
    std::string transaction_id; 

public:
    Transaction(const std::string& s, const std::string& r, long long a)
        : sender(s), receiver(r), amount(a)
    {
        transaction_id = s + r + std::to_string(a);
    }

    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    long long getAmount() const { return amount; }
    std::string getID() const { return transaction_id; }
};

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
        : index(idx), transactions(txs), prev_hash(prevHash), difficulty(diff), nonce(0)
    {
        timestamp = std::time(nullptr);
    }

    std::string getHash() const { return hash; }
    std::string getPrevHash() const { return prev_hash; }
    const std::vector<Transaction>& getTransactions() const { return transactions; }

    void mineBlock() {
        // PoW placeholder (later real hash calculation)
        hash = "000fakehash";
    }
};

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain() {}

    void addBlock(const Block& block) {
        chain.push_back(block);
    }

    Block getLastBlock() const {
        return chain.back();
    }
};