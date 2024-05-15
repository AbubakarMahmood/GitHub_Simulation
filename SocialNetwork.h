#pragma once
#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <string>
#include <fstream>
#include "exception.h"

struct SocialNetwork {
    std::string* users;
    size_t numUsers;
    std::string** adjacencyMatrix;

	SocialNetwork() : users(nullptr), numUsers(0), adjacencyMatrix(nullptr) {}
	SocialNetwork(size_t numUsers) {
		this->numUsers = numUsers;
		users = new std::string[numUsers];
		adjacencyMatrix = new std::string * [numUsers];
		for (int i = 0; i < numUsers; ++i) {
			adjacencyMatrix[i] = new std::string[numUsers];
			for (int j = 0; j < numUsers; ++j) {
				adjacencyMatrix[i][j] = "0";
			}
		}
	}


    // Destructor to free dynamically allocated memory
    ~SocialNetwork() {
		//Update FollowRelationships.csv file using final adjacency matrix
		std::ofstream file("FollowRelationships.csv", std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file FollowRelationships.csv" << std::endl;
        }
		else {
			for (int i = 0; i < numUsers; ++i) {
				for (int j = 0; j < numUsers; ++j) {
					if (adjacencyMatrix[i][j] == "1") {
						file << users[i] << " " << users[j] << std::endl;
					}
				}
			}
			file.close();
		}
		// Free memory

        delete[] users;
        for (int i = 0; i < numUsers; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    // Method to add a user to the network
    void addUser(const std::string& username, int index) {
        users[index] = username;
    }

	//get follower index
    int getFollowerIndex(const std::string& follower) {
		for (int i = 0; i < numUsers; ++i) {
			if (users[i] == follower) {
				return i;
			}
		}
		return -1;
    }

	//get followed index
    int getFollowedIndex(const std::string& followed) {
        for (int i = 0; i < numUsers; ++i) {
            if (users[i] == followed) {
				return i;
            }
        }
		return -1;
    }

    // Method to follow another user
    void follow(int followerIndex, int followedIndex) {
        if (followerIndex >= 0 && followerIndex < numUsers && followedIndex >= 0 && followedIndex < numUsers) {
            adjacencyMatrix[followerIndex][followedIndex] = "1";
        }
    }

    // Method to unfollow another user
    void unfollow(int followerIndex, int followedIndex) {
        if (followerIndex >= 0 && followerIndex < numUsers && followedIndex >= 0 && followedIndex < numUsers) {
            adjacencyMatrix[followerIndex][followedIndex] = "0";
        }
    }



	//isFollowing
	bool isFollowing(int followerIndex, int followedIndex ) {
		return adjacencyMatrix[followerIndex][followedIndex] == "1";
	}

};

#endif // SOCIALNETWORK_H
