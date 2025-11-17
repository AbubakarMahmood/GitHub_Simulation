#ifndef FILE_H
#define FILE_H

#include <string>
#include "Commit.h"
using namespace std;

// Define a struct for File
struct FileNode {
    string fileName;
    FileNode* next;
    CommitList commits;
    // Constructor
	FileNode(const string& _fileName) : fileName(_fileName), next(nullptr), commits() {}
};

// Define a class for File
class File {
private:
    FileNode* head;

public:
    // Constructor
    File() : head(nullptr) {}

    // Destructor
    ~File() {
        FileNode* current = head;
        while (current != nullptr) {
            FileNode* next = current->next;
            delete current;
            current = next;
        }
    }

    // Function to add a file to the list
    void addFile(const string& fileName) {
        FileNode* newNode = new FileNode(fileName);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            FileNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to display all files in the list
    void displayFiles() {
        FileNode* temp = head;
        while (temp != nullptr) {
            cout << temp->fileName << endl;
            temp = temp->next;
        }
    }

	// Function to search for a file in the list
	FileNode* search(const string& fileName) {
		FileNode* temp = head;
		while (temp != nullptr) {
			if (temp->fileName == fileName) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}
};

#endif // FILE_H
