#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <Funkcijos.h>
#include <Klases.h>


int main() {
    std::vector<User> users = generateUsers(10);

    std::cout << "=== Generated Users ===\n";
    for (const auto& user : users) {
        user.print();
    }

    return 0;
}
