#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>
#include <chrono>   



std::string wordToBinary(const std::string& text) {
    std::string binary;
    for (unsigned char c : text) {
        binary += std::bitset<8>(c).to_string();
    }
    return binary;
}

char fourNumbersToHex(const std::string& nibble) {
    int value = std::bitset<4>(nibble).to_ulong();
    if (value < 10) return '0' + value;
    return 'A' + (value - 10);
}

std::string binaryToHex(const std::string& binary) {
    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4) {
        hex += fourNumbersToHex(binary.substr(i, 4));
    }

    return hex;
}


std::string hash(std::string input){

    int seed = (input.length()%10)+9;
    input = wordToBinary(input);
    while (input.length() < 32){
        input += input;
        input += "1011101";
    }
    

    int amount_of_1 = 0;
    int amount_of_0 = 0;
    for (int i=0; i<input.length(); i++){
        if (input[i] == '1')
        amount_of_1 += i;
        else amount_of_0 += i;
    }

    if (amount_of_1 < 0)
    amount_of_1 *= -1;

    if (amount_of_0 < 0)
    amount_of_0 *= -1;


    // std::cout << "amount of 1, 0 = " << amount_of_1 << "    " << amount_of_0 << std::endl;


    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed;
    int smaller = ((amount_of_0 < amount_of_1) ? amount_of_0 : amount_of_1);
    if ((bigger % smaller) == 0)
        smaller++;

    
    if (bigger < 0)
    bigger *= -1;

    if (smaller < 0)
    smaller *= -1;



    if (bigger > 10000){

        bigger = bigger%10000 + 10000;
        smaller = smaller%10000 + 10000;

    }

    // std::cout << "bigger = " << bigger << " smaller = " << smaller << std::endl;

    while (input.size() < 256){ 
        input += input;
    }

    auto start = std::chrono::high_resolution_clock::now();
    int current = 0;
    for (int i=0; i<bigger; i++){
        // std::cout << "b" << std::endl;
        char temp = input[current];
        int next_pos = (current + smaller - i) % input.length();
        // std::cout << "current = " << current  << " next = " << next_pos << std::endl;
        input[current] = input[next_pos];
        input[next_pos] = temp;
        current = next_pos; 
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "duration of first loop " << duration.count() << "ms" << std::endl;



    input = binaryToHex(input);
    input = wordToBinary(input);

    current = 0;
    for (int i=0; i<bigger; i++){
    char temp = input[current];
    int next_pos = (current + smaller - i) % input.length();
    input[current] = input[next_pos];
    input[next_pos] = temp;
    current = next_pos; 
    }


    std::string Hashed = input.substr(0, 256);

    Hashed = binaryToHex(Hashed);
    if (bigger % 10 == 0)
    Hashed[0] = '0';
    if (bigger % 10 == 0){
    Hashed[1] = '0';
    // std::cout << "Hashed = " << Hashed << '\n';
    }
    return Hashed;
}

