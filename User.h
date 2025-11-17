#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Repository.h"
#include "SocialNetwork.h"
#include "exception.h"

// For SHA-256 hashing in C++/CLI
#using <System.dll>
using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;

// Define a struct for User
struct User {
    std::string username;
    std::string password;
    RepositoryManager repos;
    std::string followers, following;
    // Constructor
    User() = default;
    User(const std::string& _username, const std::string& _password) : username(_username), password(_password) {}
};

// Define a class for custom Hashtable with double hashing and rehashing
class CustomHashtable {
private:
    static const int INITIAL_SIZE = 100; // Initial size of the table
    static const double LOAD_FACTOR_THRESHOLD; // Threshold for rehashing
    static const int PRIME_FOR_SECOND_HASH; // Prime number for double hashing
    struct Node {
        User user;
        bool deleted; // Flag to mark deleted entries
        Node() : deleted(false) {}
    };
    Node* table;
    int size;
    int capacity;

    // Hash function for the first hash
    int hash1(const std::string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % capacity; // Basic hash function
        }
        return hash;
    }

    // Hash function for the second hash in double hashing
    int hash2(const std::string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 37 + ch) % PRIME_FOR_SECOND_HASH; // Another prime number for variation
        }
        return hash;
    }

    // Method to rehash the table when the load factor exceeds the threshold
    void rehash() {
        int newCapacity = capacity * 2; // Double the capacity
        Node* newTable = new Node[newCapacity];
        for (int i = 0; i < capacity; ++i) {
            if (!table[i].deleted) {
                int index = hash1(table[i].user.username);
                int step = hash2(table[i].user.username);
                while (newTable[index].user.username != "") {
                    index = (index + step) % newCapacity; // Apply double hashing
                }
                newTable[index].user = table[i].user;
                newTable[index].deleted = false;
            }
        }
        delete[] table;
        table = newTable;
        capacity = newCapacity;
    }

public:
    CustomHashtable() : size(0), capacity(INITIAL_SIZE) {
        table = new Node[capacity];

    }

    ~CustomHashtable() {
        delete[] table;
    }

    // Method to insert a user into hashtable
    void insert(const User& user) {
        if (size >= capacity * LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
        int index = hash1(user.username);
        int step = hash2(user.username);
        while (table[index].user.username != "") {
            index = (index + step) % capacity; // Apply double hashing
        }
        table[index].user = user;
        table[index].deleted = false;
        size++;
    }

    // Method to retrieve a user from hashtable
    User* retrieve(const std::string& username) {
        int index = hash1(username);
        int step = hash2(username);
        while (table[index].user.username != "" || table[index].deleted) {
            if (table[index].user.username == username && !table[index].deleted) {
                return &(table[index].user);
            }
            index = (index + step) % capacity; // Apply double hashing
        }
        return nullptr; // User not found
    }

    // Method to check if a username exists in hashtable
    bool exists(const std::string& username) {
        return retrieve(username) != nullptr;
    }

    // Method to get the size of the hashtable
    int getSize() const {
        return size;
    }
};

extern const double LOAD_FACTOR_THRESHOLD;
extern const int PRIME_FOR_SECOND_HASH;

// Define a class for managing user accounts
class UserManager {
private:
    User* currentUser;
    SocialNetwork* network;
    CustomHashtable users; // Replace unordered_map with custom CustomHashtable

    // Create a text file for every new user's repositories
    void createRepoFile(const std::string& username) {
        std::ofstream file(username + "'sRepos.csv");
        if (!file.is_open()) {
            std::cerr << "Error: Unable to create file " << username << "'sRepos.csv" << std::endl;
        }
        file.close();
    }

    // Create a text file for every new user's followers
    void createFollowersFile(const std::string& username) {
        std::ofstream file(username + "'sFollowers.csv");
        if (!file.is_open()) {
            std::cerr << "Error: Unable to create file " << username << "'sFollowers.csv" << std::endl;
        }
        file.close();
    }

public:
    UserManager() {
        currentUser = nullptr;
        network = new SocialNetwork(); // Initialize an empty social network
		loadUsersFromFile("users.csv"); // Load users from file
    }

    ~UserManager() {
        delete network; // Free memory
    }

    // Method to load users from file and initialize social network
    void loadUsersFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            std::cerr << "Creating new users file..." << std::endl;
            // Create the file if it doesn't exist
            std::ofstream createFile(filename);
            if (createFile.is_open()) {
                createFile.close();
                std::cout << "New users file created successfully." << std::endl;
            }
            network = new SocialNetwork(0);
            return;
        }

        std::string username, password;
        while (file >> username >> password) { // Use space as separator in .csv file
            User newUser(username, password);
            users.insert(newUser);
        }
        file.close();

        // Initialize social network with the final size of the hashtable
        network = new SocialNetwork(users.getSize());

        // Populate the users array in the social network
        file.open(filename);
        if (file.is_open()) {
            int index = 0;
            while (file >> username >> password) {
                network->addUser(username, index);
                ++index;
            }
            file.close();
        }
        else {
            std::cerr << "Error: Unable to reopen file " << filename << " for network initialization" << std::endl;
        }
    }

    // Method to get network
    SocialNetwork* getNetwork() {
        return network;
    }

    // Method to login
    bool login(const std::string& username, const std::string& password) {
        User* user = users.retrieve(username);
        if (user && user->password == hashPassword(password)) {
            currentUser = user;
            return true;
        }
        return false;
    }

    // Method to check if a user is logged in
    bool isLoggedIn() {
        return currentUser != nullptr;
    }

    // Method to get the current user
    User* getCurrentUser() {
        return currentUser;
    }

    // Method to set the current user
    void

        setCurrentUser(User* user) {
        currentUser = user;
    }

    // Method to log out
    void logout() {
        currentUser = nullptr; // Set current user to null, indicating no user is logged in
    }

    // Method to hash a password using SHA-256
    std::string hashPassword(const std::string& password) {
        // Convert std::string to managed String^
        String^ managedPassword = gcnew String(password.c_str());

        // Create SHA256 instance
        SHA256^ sha256 = SHA256::Create();

        // Convert string to bytes
        array<Byte>^ passwordBytes = Encoding::UTF8->GetBytes(managedPassword);

        // Compute hash
        array<Byte>^ hashBytes = sha256->ComputeHash(passwordBytes);

        // Convert hash bytes to hex string
        StringBuilder^ sb = gcnew StringBuilder();
        for (int i = 0; i < hashBytes->Length; i++) {
            sb->Append(hashBytes[i].ToString("x2"));
        }

        // Convert managed String^ back to std::string
        String^ hashString = sb->ToString();
        std::string result;
        for (int i = 0; i < hashString->Length; i++) {
            result += (char)hashString[i];
        }

        return result;
    }

    // Method to register a new user
    bool registerUser(const std::string& username, const std::string& password) {
        if (!users.exists(username)) {
            User newUser(username, hashPassword(password));
            users.insert(newUser);

            // Open users.csv file for writing
            std::ofstream file("users.csv", std::ios::app);
            if (file.is_open()) {
                // Write the new user's information to the file
                file << username << " " << hashPassword(password) << std::endl; // Use space as separator
                file.close(); // Close the file after writing
                createRepoFile(username); // Create a text file for the new user's repositories
                createFollowersFile(username); // Create a text file for the new user's followers
                return true; // User registered successfully
            }
            else {
                std::cerr << "Error: Unable to open file users.csv for writing" << std::endl;
                return false; // Error opening file
            }
        }
        else {
            return false; // User already exists
        }
    }

    // Method to retrieve a user
    User getUser(const std::string& username) {
        return *users.retrieve(username);
    }

    // Method to check if a username exists
    bool usernameExists(const std::string& username) {
        return users.exists(username);
    }
};

#endif // USERMANAGER_H
