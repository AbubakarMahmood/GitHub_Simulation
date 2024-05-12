#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <string>
#include <fstream>
#include "exception.h"
using namespace std;
struct Repository
{
    string name;
	int forkCount;
	bool isPublic; 
    Repository* left = nullptr;
    Repository* right = nullptr; 
    Repository(const string& _name, int _forkCount, bool _isPublic) : name(_name), forkCount(_forkCount), isPublic(_isPublic) {}
};

class RepositoryManager
{
private:
	Repository* root;
	Repository* current;
	
public:

	RepositoryManager()
	{
		root = nullptr;
		current = nullptr;
	}
	~RepositoryManager()
	{

	}

	Repository* getRoot() const
	{
		return root;
	}

    void insert(const Repository& newRepo)
    {
        // Create a new node for the new repository
        Repository* newNode = new Repository(newRepo.name, newRepo.forkCount, newRepo.isPublic);

        if (root == nullptr)
        {
            root = newNode;
            current = root;
        }
        else
        {
            Repository* temp = root;
            while (temp != nullptr)
            {
                if (newNode->name < temp->name)
                {
                    if (temp->left == nullptr)
                    {
                        temp->left = newNode;
                        break;
                    }
                    else
                    {
                        temp = temp->left;
                    }
                }
				else if (newNode->name > temp->name)
                {
                    if (temp->right == nullptr)
                    {
                        temp->right = newNode;
                        break;
                    }
                    else
                    {
                        temp = temp->right;
                    }
                }
                else
                {
					// The repository already exists
					delete newNode;
                    break;
                }
            }
        }
    }

	void remove(const string& repoName)
	{
		Repository* temp = root;
		Repository* parent = nullptr;
		while (temp != nullptr)
		{
			if (repoName < temp->name)
			{
				parent = temp;
				temp = temp->left;
			}
			else if (repoName > temp->name)
			{
				parent = temp;
				temp = temp->right;
			}
			else
			{
				// Found the repository
				if (temp->left == nullptr && temp->right == nullptr)
				{
					// Case 1: The repository has no children
					if (parent == nullptr)
					{
						root = nullptr;
					}
					else if (parent->left == temp)
					{
						parent->left = nullptr;
					}
					else
					{
						parent->right = nullptr;
					}
					delete temp;
				}
				else if (temp->left == nullptr || temp->right == nullptr)
				{
					// Case 2: The repository has one child
					Repository* child = (temp->left != nullptr) ? temp->left : temp->right;
					if (parent == nullptr)
					{
						root = child;
					}
					else if (parent->left == temp)
					{
						parent->left = child;
					}
					else
					{
						parent->right = child;
					}
					delete temp;
				}
				else
				{
					// Case 3: The repository has two children
					Repository* successor = temp->right;
					Repository* successorParent = temp;
					while (successor->left != nullptr)
					{
						successorParent = successor;
						successor = successor->left;
					}
					temp->name = successor->name;
					temp->forkCount = successor->forkCount;
					temp->isPublic = successor->isPublic;
					if (successorParent->left == successor)
					{
						successorParent->left = successor->right;
					}
					else
					{
						successorParent->right = successor->right;
					}
					delete successor;
				}
				break;
			}
		}
	}



};

#endif // REPOSITORY_H