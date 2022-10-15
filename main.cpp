#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <random>

std::string input = "";
std::string msg = "";
std::string key = "";

char Xor(char x, char y){
    if (x == y) {
        return '0';
    }
    return '1';
}

std::string RetBitset(std::string str) {
    std::string Bitset;
    for (size_t i = 0; i < str.size(); i++) {
        Bitset += std::bitset<8>(str.c_str()[i]).to_string();
    }
    return Bitset;
}

std::string RandomString(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

std::string EncStr(std::string msg) {
    std::string key = RandomString(msg.length());
    std::cout << "Decryption key: " + key << std::endl;

    std::string keyBitset = RetBitset(key);
    std::string msgBitset = RetBitset(msg);
    std::cout << "Original:  " + msgBitset << std::endl;

    for (size_t i = 0; i < msgBitset.length(); i++)
    {
        msgBitset[i] = Xor(msgBitset[i], keyBitset[i]);
    }
    return msgBitset;
}

std::string DecStr(std::string msg, std::string key) {
    std::string keyBitset = RetBitset(key);

    for (size_t i = 0; i < msg.length(); i++)
    {
        msg[i] = Xor(msg[i], keyBitset[i]);
    }
    return msg;
}

int main()
{
    srand(time(0));

    std::cout << "[1] Encrypt\n";
    std::cout << "[2] Decrypt\n";
    std::cin >> input;

    if (input == "1") {
        system("cls");
        std::cout << "Message: ";
        std::cin >> msg;

        std::cout << "Encrypted: " + EncStr(msg) << std::endl;
    }
    else {
        system("cls");
        std::cout << "Message: ";
        std::cin >> msg;

        std::cout << "Key: ";
        std::cin >> key;

        std::cout << "Decrypted: " + DecStr(msg, key) << std::endl;
    }
}
