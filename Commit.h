#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <iostream>
using namespace std;

// Define a struct for Commit
struct Commit {
    string commitMessage;
    Commit* next;

    // Constructor
    Commit() : next(nullptr) {}
    Commit(const string& message) : commitMessage(message), next(nullptr) {}
};

// Define a class for CommitList
class CommitList {
private:
    Commit* head;

public:
    // Constructor
    CommitList() : head(nullptr) {}

    // Destructor
    ~CommitList() {
        // Implement if needed
    }

    // Function to add a commit to the list
	void addCommit(const string& message) {
		Commit* newNode = new Commit(message);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Commit* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
};

#endif // COMMIT_H
