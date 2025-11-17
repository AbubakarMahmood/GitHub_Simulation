#pragma once

#include "User.h"
#include "Repository.h"
#include "SocialNetwork.h"
#include "exception.h"
#include <string>
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <ostream>
#include <sstream>

namespace GithubSimulation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for SearchedUser
    /// </summary>
    public ref class SearchedUser : public System::Windows::Forms::Form
    {
        UserManager* userManager;
    private: System::Windows::Forms::DataGridView^ searchedUserReposdataGridView;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ SearchedUserRepoNameColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ SearchedUserRepoForkCountColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ SearchedUserRepoForkDescionColumn;
    private: System::Windows::Forms::Button^ searchUserFollowbutton;
    private: System::Windows::Forms::Button^ searchedUserUnfollowbutton;
    private: System::Windows::Forms::TextBox^ searchedUSerNametextBox;

           std::string* searchedUsername;
    public:
        SearchedUser(UserManager* _userManager, std::string _searchedUsername)
        {
            userManager = _userManager;
            searchedUsername = new std::string(_searchedUsername);
            InitializeComponent();
            LoadSearchedUserRepos();

            // Check if the current user is following the searched user
            bool isFollowing = userManager->getNetwork()->isFollowing(userManager->getNetwork()->getFollowerIndex(userManager->getCurrentUser()->username), userManager->getNetwork()->getFollowedIndex(*searchedUsername));

            // Enable or disable the follow and unfollow buttons accordingly
            searchUserFollowbutton->Enabled = !isFollowing;
            searchedUserUnfollowbutton->Enabled = isFollowing;
        }

        delegate void UserActionEventHandler(String^ username, bool isFollowed);
        event UserActionEventHandler^ UserFollowed;
        event UserActionEventHandler^ UserUnfollowed;
        // Define similar events for forking repositories
		delegate void RepoActionEventHandler(String^ repoName, int forkCount);
		event RepoActionEventHandler^ RepoForked;

        // Method to trigger the UserFollowed event
        void OnUserFollowed(String^ username, bool isFollowed) {
            UserFollowed(username, isFollowed);
        }
        // Method to trigger the UserUnfollowed event
        void OnUserUnfollowed(String^ username, bool isFollowed) {
            UserUnfollowed(username, isFollowed);
        }

		// Method to trigger the RepositoryForked event
        void OnRepoForked(String^ repoName, int forkCount) {
			RepoForked(repoName, forkCount);
        }


    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~SearchedUser()
        {
            if (components)
            {
                delete components;
            }
            delete searchedUsername;
        }

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            this->searchedUserReposdataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->SearchedUserRepoNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->SearchedUserRepoForkCountColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->SearchedUserRepoForkDescionColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->searchUserFollowbutton = (gcnew System::Windows::Forms::Button());
            this->searchedUserUnfollowbutton = (gcnew System::Windows::Forms::Button());
            this->searchedUSerNametextBox = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedUserReposdataGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // searchedUserReposdataGridView
            // 
            this->searchedUserReposdataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->searchedUserReposdataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
                this->SearchedUserRepoNameColumn,
                    this->SearchedUserRepoForkCountColumn, this->SearchedUserRepoForkDescionColumn
            });
            this->searchedUserReposdataGridView->Location = System::Drawing::Point(86, 112);
            this->searchedUserReposdataGridView->Name = L"searchedUserReposdataGridView";
            this->searchedUserReposdataGridView->RowHeadersWidth = 51;
            this->searchedUserReposdataGridView->RowTemplate->Height = 24;
            this->searchedUserReposdataGridView->Size = System::Drawing::Size(425, 233);
            this->searchedUserReposdataGridView->TabIndex = 0;
            this->searchedUserReposdataGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &SearchedUser::dataGridView1_CellContentClick);
            // 
            // SearchedUserRepoNameColumn
            // 
            this->SearchedUserRepoNameColumn->HeaderText = L"Name";
            this->SearchedUserRepoNameColumn->MinimumWidth = 6;
            this->SearchedUserRepoNameColumn->Name = L"SearchedUserRepoNameColumn";
            this->SearchedUserRepoNameColumn->ReadOnly = true;
            this->SearchedUserRepoNameColumn->Width = 125;
            // 
            // SearchedUserRepoForkCountColumn
            // 
            this->SearchedUserRepoForkCountColumn->HeaderText = L"Fork Count";
            this->SearchedUserRepoForkCountColumn->MinimumWidth = 6;
            this->SearchedUserRepoForkCountColumn->Name = L"SearchedUserRepoForkCountColumn";
            this->SearchedUserRepoForkCountColumn->ReadOnly = true;
            this->SearchedUserRepoForkCountColumn->Width = 125;
            // 
            // SearchedUserRepoForkDescionColumn
            // 
            this->SearchedUserRepoForkDescionColumn->HeaderText = L"Decision";
            this->SearchedUserRepoForkDescionColumn->MinimumWidth = 6;
            this->SearchedUserRepoForkDescionColumn->Name = L"SearchedUserRepoForkDescionColumn";
            this->SearchedUserRepoForkDescionColumn->ReadOnly = true;
            this->SearchedUserRepoForkDescionColumn->Width = 125;
            // 
            // searchUserFollowbutton
            // 
            this->searchUserFollowbutton->Location = System::Drawing::Point(326, 41);
            this->searchUserFollowbutton->Name = L"searchUserFollowbutton";
            this->searchUserFollowbutton->Size = System::Drawing::Size(75, 23);
            this->searchUserFollowbutton->TabIndex = 1;
            this->searchUserFollowbutton->TabStop = false;
            this->searchUserFollowbutton->Text = L"Follow";
            this->searchUserFollowbutton->UseVisualStyleBackColor = true;
            this->searchUserFollowbutton->Click += gcnew System::EventHandler(this, &SearchedUser::searchUserFollowbutton_Click);
            // 
            // searchedUserUnfollowbutton
            // 
            this->searchedUserUnfollowbutton->Location = System::Drawing::Point(436, 41);
            this->searchedUserUnfollowbutton->Name = L"searchedUserUnfollowbutton";
            this->searchedUserUnfollowbutton->Size = System::Drawing::Size(75, 23);
            this->searchedUserUnfollowbutton->TabIndex = 2;
            this->searchedUserUnfollowbutton->TabStop = false;
            this->searchedUserUnfollowbutton->Text = L"Unfollow";
            this->searchedUserUnfollowbutton->UseVisualStyleBackColor = true;
            this->searchedUserUnfollowbutton->Click += gcnew System::EventHandler(this, &SearchedUser::searchedUserUnfollowbutton_Click);
            // 
            // searchedUSerNametextBox
            // 
            this->searchedUSerNametextBox->Location = System::Drawing::Point(86, 42);
            this->searchedUSerNametextBox->Name = L"searchedUSerNametextBox";
            this->searchedUSerNametextBox->Size = System::Drawing::Size(174, 22);
            this->searchedUSerNametextBox->TabIndex = 3;
            this->searchedUSerNametextBox->TabStop = false;
            // 
            // SearchedUser
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(602, 401);
            this->Controls->Add(this->searchedUSerNametextBox);
            this->Controls->Add(this->searchedUserUnfollowbutton);
            this->Controls->Add(this->searchUserFollowbutton);
            this->Controls->Add(this->searchedUserReposdataGridView);
            this->Name = L"SearchedUser";
            this->Text = L"SearchedUser";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedUserReposdataGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void searchUserFollowbutton_Click(System::Object^ sender, System::EventArgs^ e) {
        string searchedUsername = msclr::interop::marshal_as<std::string>(searchedUSerNametextBox->Text);
        userManager->getNetwork()->follow(userManager->getNetwork()->getFollowerIndex(userManager->getCurrentUser()->username), userManager->getNetwork()->getFollowedIndex(searchedUsername));
		// Enable the unfollow button and disable the follow button
		searchUserFollowbutton->Enabled = false;
		searchedUserUnfollowbutton->Enabled = true;
        OnUserFollowed(searchedUSerNametextBox->Text, true);
    }
    
    private: System::Void searchedUserUnfollowbutton_Click(System::Object^ sender, System::EventArgs^ e) {
        string searchedUsername = msclr::interop::marshal_as<std::string>(searchedUSerNametextBox->Text);
        userManager->getNetwork()->unfollow(userManager->getNetwork()->getFollowerIndex(userManager->getCurrentUser()->username), userManager->getNetwork()->getFollowedIndex(searchedUsername));
		// Enable the follow button and disable the unfollow button
		searchUserFollowbutton->Enabled = true;
		searchedUserUnfollowbutton->Enabled = false;
		OnUserUnfollowed(searchedUSerNametextBox->Text, false);
    }

    private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    }

    private:void LoadSearchedUserRepos() {
        string username = msclr::interop::marshal_as<std::string>(searchedUSerNametextBox->Text);

        //open the repo file of the searched user
        ifstream file(username + "'sRepos.csv");
        if (file.is_open()) {
            string repoName = "";
            int forkCount = -1;
            string visibility = "";
            while (file >> repoName >> forkCount >> visibility) {
                //Add the repository and its fork count to the grid if repoName is not empty and if its public
                if (repoName != "" && visibility == "Public") {
                    searchedUserReposdataGridView->Rows->Add(gcnew String(repoName.c_str()), forkCount, gcnew String(visibility.c_str()));
                    //add the text Fork to the decision column
                    searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->Rows->Count - 1]->Cells[2]->Value = "Fork";
                }
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file " << username << "'sRepos.txt" << endl;
        }
    }

    private: System::Void searchedUserForkButton_Click(System::Object^ sender, System::EventArgs^ e) {
        //Add the forked repository to the current user's repositories
        string repoName = msclr::interop::marshal_as<std::string>(searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[0]->Value->ToString());
        int forkCount = stoi(msclr::interop::marshal_as<std::string>(searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[1]->Value->ToString()));
        string visibility = "Public"; // Forked repositories are always public

        userManager->getCurrentUser()->repos.insert(Repository(repoName, forkCount, true));

        //Add the forked repository to the current user's repositories file
        ofstream file(userManager->getCurrentUser()->username + "'sRepos.csv", ios::app);
        if (file.is_open()) {
            file << repoName << " " << forkCount << " " << visibility << endl;
            file.close();
        }
        else {
            cerr << "Error: Unable to open file " << userManager->getCurrentUser()->username << "'sRepos.txt" << endl;
        }

        //Increment the fork count of the repository in the grid
        searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[1]->Value = forkCount + 1;

        //Change the text in the decision column to Forked
        searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[2]->Value = "Forked";

        //Disable the fork button
        searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[3]->Value = "Forked";

        // Update the file containing the searched user's repositories
        string searchedUsername = msclr::interop::marshal_as<std::string>(searchedUSerNametextBox->Text);
        ifstream infile(searchedUsername + "'sRepos.csv");
        if (infile.is_open()) {
            vector<string> lines;
            string line;
            while (getline(infile, line)) {
                // Parse the line into repo name, fork count, and visibility
                istringstream iss(line);
                string currentRepoName;
                int currentForkCount;
                string currentVisibility;
                if (iss >> currentRepoName >> currentForkCount >> currentVisibility) {
                    // Check if this is the repository to update
                    if (currentRepoName == repoName && currentVisibility == visibility) {
                        // Update the fork count in memory
                        currentForkCount++;
                        // Append the updated line to the vector of lines
                        lines.push_back(currentRepoName + " " + to_string(currentForkCount) + " " + currentVisibility);
                    }
                    else {
                        // Append the original line to the vector of lines
                        lines.push_back(line);
                    }
                }
            }
            infile.close();

            // Rewrite the file with updated fork count for the forked repository
            ofstream outfile(searchedUsername + "'sRepos.csv", ios::trunc);
            if (outfile.is_open()) {
                for (const string& updatedLine : lines) {
                    outfile << updatedLine << endl;
                }
                outfile.close();
            }
            else {
                cerr << "Error: Unable to open file " << searchedUsername << "'sRepos.csv" << endl;
            }
        }
        else {
            cerr << "Error: Unable to open file " << searchedUsername << "'sRepos.csv" << endl;
        }

        // Trigger the RepoForked event
        OnRepoForked(searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[0]->Value->ToString(),
            Convert::ToInt32(searchedUserReposdataGridView->Rows[searchedUserReposdataGridView->CurrentCell->RowIndex]->Cells[1]->Value));
    }

    };
}
