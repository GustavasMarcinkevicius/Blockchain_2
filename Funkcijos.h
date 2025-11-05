#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <algorithm>
#include "Klases.h"
#include <unordered_map>
#include <chrono>


std::vector<User> generateUsers(int n) {
    std::vector<User> users;
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<long long> balanceDist(100, 1000000);

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

void processBlockTransactions(const std::vector<Transaction>& blockTxs, std::vector<User>& users) {
    for (const auto& tx : blockTxs) {
        for (auto& user : users) {
            if (user.getPublicKey() == tx.getSender()) {
                user.setBalance(user.getBalance() - tx.getAmount());
            }
            if (user.getPublicKey() == tx.getReceiver()) {
                user.setBalance(user.getBalance() + tx.getAmount());
            }
        }
    }
}

std::string computeMerkleRoot(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) return "";

    std::vector<std::string> layer;
    for (const auto& tx : transactions) {
        layer.push_back(hash(tx.getID()));  
    }

    while (layer.size() > 1) {
        std::vector<std::string> nextLayer;

        for (size_t i = 0; i < layer.size(); i += 2) {
            if (i + 1 < layer.size()) {
                nextLayer.push_back(hash(layer[i] + layer[i+1]));
            } else {
                nextLayer.push_back(hash(layer[i] + layer[i]));
            }
        }

        layer = nextLayer;  
    }

    return layer[0];
}

std::vector<Transaction> filterValidTransactions(
    const std::vector<Transaction>& blockTxs,
    const std::vector<User>& users
) {
    std::unordered_map<std::string, long long> balances;


    //Sukuriu laikinas balansu kopijas, kad zmogus, turintis 1000, negaletu issiusti kelis kartus po 999
    for (const auto& user : users) {
        balances[user.getPublicKey()] = user.getBalance();
    }

    std::vector<Transaction> validTxs;

    for (const auto& tx : blockTxs) {
        if (tx.getSender() == tx.getReceiver()) continue; 

        //ID tikrinimas (neturetu sufeilint)
        std::string txInfo = tx.getSender() + tx.getReceiver() + std::to_string(tx.getAmount());
        if (tx.getID() != hash(txInfo)) {
        std::cout << "Invalid transaction ID, sender: " << tx.getSender() << '\n';
        continue;
        }
        long long senderBalance = balances[tx.getSender()];

        if (senderBalance >= tx.getAmount()) {
            validTxs.push_back(tx);

            balances[tx.getSender()] -= tx.getAmount();
            balances[tx.getReceiver()] += tx.getAmount();
        }
        else {
            std::cout << "Transaction amount is bigger than the senders balance" << '\n';
                        txPool.erase(std::remove_if(txPool.begin(), txPool.end(),
                        [&](const Transaction& t){ return t.getID() == tx.getID(); }),
                        txPool.end());
        }
    }

    return validTxs;
}

//bloko kasimas laiku
bool tryMineBlock(Block& block, const std::string& prevHash, const std::string& merkleRoot, int difficulty, int timeLimitMs = 5000) {
    auto start = std::chrono::steady_clock::now();
    long long nonce = 0;

    while (true) {
        std::string header = prevHash + std::to_string(block.getTimestamp()) +
                             merkleRoot + std::to_string(nonce) + std::to_string(difficulty);
        std::string blockHash = hash(hash(header));

        if (blockHash.substr(0, difficulty) == std::string(difficulty, '0')) {
            block.setHash(blockHash);
            block.setNonce(nonce);
            return true;
        }

        nonce++;

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= timeLimitMs) {
            std::cout << "Time limit reached\n";
            return false;
        }
    }
}


// Pagrindinis kasimo procesas
void mineCandidateBlocks(Blockchain& bc, std::vector<Transaction>& txs, std::vector<User>& users, int timeLimitMs, int difficulty = 3) {
    int candidateCount = 5;
    int txPerBlock = 100;

    while (!txs.empty()) {
        bool minedAny = false;

        for (int i = 0; i < candidateCount && !txs.empty(); ++i) {
            std::vector<Transaction> blockTxs = pickRandomTransactions(txs, txPerBlock);
            blockTxs = filterValidTransactions(blockTxs, users);
            if (blockTxs.empty()) {
            std::cout << "No valid transactions left for this block, skipping...\n";
            minedAny = false;
            break; 
            }
            std::string merkleRoot = computeMerkleRoot(blockTxs);
            std::string prevHash = bc.getLastBlock().getHash();
            if (prevHash.empty()) prevHash = std::string(64, '0');

            Block candidate(bc.getChain().size() + 1, blockTxs, prevHash);

            if (tryMineBlock(candidate, prevHash, merkleRoot, difficulty, timeLimitMs)) {
                processBlockTransactions(blockTxs, users);
                bc.addBlock(candidate);

                for (const auto& tx : blockTxs) {
                    txs.erase(std::remove_if(txs.begin(), txs.end(),
                                [&](const Transaction& t){ return t.getID() == tx.getID(); }),
                              txs.end());
                }

                minedAny = true;
                std::cout << "Mined Block #" << bc.getChain().size()
                          << " | Nonce: " << candidate.getNonce()
                          << " | Remaining transactions: " << txs.size() << "\n";
                break; 
            }
        }

        if (!minedAny) {
            std::cout << "No blocks mined this round. Increasing time limit...\n";
            timeLimitMs *= 2;
        }
    }
}

