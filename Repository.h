#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <string>
#include <fstream>
#include "exception.h"
#include "File.h"
using namespace std;
struct Repository
{
	string name;
	int forkCount;
	bool isPublic; 
    Repository* left = nullptr;
    Repository* right = nullptr;
	File files;
    Repository(const string& _name, int _forkCount, bool _isPublic) : name(_name), forkCount(_forkCount), isPublic(_isPublic), files() {}
};

class RepositoryManager
{
private:
	Repository* root;
	Repository* current;

	// Helper function to recursively delete all nodes in the tree
	void deleteTree(Repository* node)
	{
		if (node != nullptr)
		{
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

public:

	RepositoryManager()
	{
		root = nullptr;
		current = nullptr;
	}
	~RepositoryManager()
	{
		deleteTree(root);
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
        {//Empty Tree
            root = newNode;
            current = root;
        }
        else
        {//Tree Not Empty
            Repository* temp = root;
            while (temp != nullptr)
            {
                if (newNode->name < temp->name)
                {//Left traversal
                    if (temp->left == nullptr)
                    {//Empty Left side
                        temp->left = newNode;
                        break;
                    }
                    else
                    {//Continue Traversal
                        temp = temp->left;
                    }
                }
				else if (newNode->name > temp->name)
                {//Right Traversal
                    if (temp->right == nullptr)
                    {//Rightside Empty
                        temp->right = newNode;
                        break;
                    }
                    else
                    {//Continue Traversal
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

	Repository* search(const string& repoName)
	{
		Repository* temp = root;
		while (temp != nullptr)
		{
			if (repoName < temp->name)
			{
				temp = temp->left;
			}
			else if (repoName > temp->name)
			{
				temp = temp->right;
			}
			else
			{
				return temp;
			}
		}
		return nullptr;
	}



};

#endif // REPOSITORY_H