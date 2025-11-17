#pragma once

#include "User.h"
#include "Repository.h"
#include "SocialNetwork.h"
#include "SearchedUser.h"
#include "SelectedRepo.h"
#include "exception.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <string>

namespace GithubSimulation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for Home
    /// </summary>
    public ref class Home : public System::Windows::Forms::Form
    {
    private:
        UserManager* userManager;
    public:
        Home(UserManager* _userManager)
        {
            InitializeComponent();
            userManager = _userManager;
            Logoutbutton->Click += gcnew EventHandler(this, &Home::Logoutbutton_Click);
            RepoAddbutton->Click += gcnew EventHandler(this, &Home::RepoAddbutton_Click);
            UserReposGridView->CellContentClick += gcnew DataGridViewCellEventHandler(this, &Home::DeleteButton_Click);
            FollowsGridView->CellContentClick += gcnew DataGridViewCellEventHandler(this, &Home::UnfollowButton_Click);
            RepoNameColumn->SortMode = DataGridViewColumnSortMode::Automatic;
            NewRepotextBox->Enter += gcnew System::EventHandler(this, &Home::NewRepotextBox_Enter);
            NewRepotextBox->Leave += gcnew System::EventHandler(this, &Home::NewRepotextBox_Leave);
            LoadRepositories();
            LoadFollowers();
            LoadFollows();
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Home()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ Logoutbutton;
    private: System::Windows::Forms::TextBox^ NewRepotextBox;
    private: System::Windows::Forms::RadioButton^ RepoVisiblityradioButton;
    private: System::Windows::Forms::Button^ RepoAddbutton;
    private: System::Windows::Forms::DataGridView^ UserReposGridView;


    private: System::Windows::Forms::DataGridViewTextBoxColumn^ RepoNameColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ RepoForkCountColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ VisibilityColumn;
    private: System::Windows::Forms::DataGridViewButtonColumn^ DeleteButtonColumn;
    private: System::Windows::Forms::DataGridView^ FollowsGridView;

    private: System::Windows::Forms::DataGridViewTextBoxColumn^ FollowsNameColumn;
    private: System::Windows::Forms::DataGridViewButtonColumn^ FollowerUnfollowColumn;
    private: System::Windows::Forms::DataGridView^ FollowersGridView;

    private: System::Windows::Forms::DataGridViewTextBoxColumn^ FollowerColumn;
    private: System::Windows::Forms::ComboBox^ SearchComboBox;


    protected:

    protected:

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
            this->Logoutbutton = (gcnew System::Windows::Forms::Button());
            this->NewRepotextBox = (gcnew System::Windows::Forms::TextBox());
            this->RepoVisiblityradioButton = (gcnew System::Windows::Forms::RadioButton());
            this->RepoAddbutton = (gcnew System::Windows::Forms::Button());
            this->UserReposGridView = (gcnew System::Windows::Forms::DataGridView());
            this->RepoNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->RepoForkCountColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->VisibilityColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->DeleteButtonColumn = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->FollowsGridView = (gcnew System::Windows::Forms::DataGridView());
            this->FollowsNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->FollowerUnfollowColumn = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->FollowersGridView = (gcnew System::Windows::Forms::DataGridView());
            this->FollowerColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->SearchComboBox = (gcnew System::Windows::Forms::ComboBox());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UserReposGridView))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FollowsGridView))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FollowersGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // Logoutbutton
            // 
            this->Logoutbutton->Location = System::Drawing::Point(353, 41);
            this->Logoutbutton->Name = L"Logoutbutton";
            this->Logoutbutton->Size = System::Drawing::Size(75, 23);
            this->Logoutbutton->TabIndex = 0;
            this->Logoutbutton->TabStop = false;
            this->Logoutbutton->Text = L"Logout";
            this->Logoutbutton->UseVisualStyleBackColor = true;
            // 
            // NewRepotextBox
            // 
            this->NewRepotextBox->Location = System::Drawing::Point(12, 42);
            this->NewRepotextBox->Name = L"NewRepotextBox";
            this->NewRepotextBox->Size = System::Drawing::Size(110, 20);
            this->NewRepotextBox->TabIndex = 1;
            this->NewRepotextBox->TabStop = false;
            this->NewRepotextBox->Text = L"name your new repo";
            // 
            // RepoVisiblityradioButton
            // 
            this->RepoVisiblityradioButton->AutoSize = true;
            this->RepoVisiblityradioButton->Location = System::Drawing::Point(129, 44);
            this->RepoVisiblityradioButton->Name = L"RepoVisiblityradioButton";
            this->RepoVisiblityradioButton->Size = System::Drawing::Size(58, 17);
            this->RepoVisiblityradioButton->TabIndex = 2;
            this->RepoVisiblityradioButton->Text = L"Private";
            this->RepoVisiblityradioButton->UseVisualStyleBackColor = true;
            // 
            // RepoAddbutton
            // 
            this->RepoAddbutton->Location = System::Drawing::Point(193, 41);
            this->RepoAddbutton->Name = L"RepoAddbutton";
            this->RepoAddbutton->Size = System::Drawing::Size(75, 23);
            this->RepoAddbutton->TabIndex = 3;
            this->RepoAddbutton->TabStop = false;
            this->RepoAddbutton->Text = L"Create";
            this->RepoAddbutton->UseVisualStyleBackColor = true;
            // 
            // UserReposGridView
            // 
            this->UserReposGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->UserReposGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
                this->RepoNameColumn,
                    this->RepoForkCountColumn, this->VisibilityColumn, this->DeleteButtonColumn
            });
            this->UserReposGridView->Location = System::Drawing::Point(13, 79);
            this->UserReposGridView->Name = L"UserReposGridView";
            this->UserReposGridView->ReadOnly = true;
            this->UserReposGridView->RowHeadersWidth = 51;
            this->UserReposGridView->Size = System::Drawing::Size(416, 210);
            this->UserReposGridView->TabIndex = 4;
            this->UserReposGridView->TabStop = false;
            this->UserReposGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Home::UserReposGridView_CellContentClick);
            // 
            // RepoNameColumn
            // 
            this->RepoNameColumn->HeaderText = L"Name";
            this->RepoNameColumn->MinimumWidth = 6;
            this->RepoNameColumn->Name = L"RepoNameColumn";
            this->RepoNameColumn->ReadOnly = true;
            this->RepoNameColumn->Width = 125;
            // 
            // RepoForkCountColumn
            // 
            this->RepoForkCountColumn->HeaderText = L"Forks";
            this->RepoForkCountColumn->MinimumWidth = 6;
            this->RepoForkCountColumn->Name = L"RepoForkCountColumn";
            this->RepoForkCountColumn->ReadOnly = true;
            this->RepoForkCountColumn->Width = 125;
            // 
            // VisibilityColumn
            // 
            this->VisibilityColumn->HeaderText = L"Visibility";
            this->VisibilityColumn->MinimumWidth = 6;
            this->VisibilityColumn->Name = L"VisibilityColumn";
            this->VisibilityColumn->ReadOnly = true;
            this->VisibilityColumn->Width = 125;
            // 
            // DeleteButtonColumn
            // 
            this->DeleteButtonColumn->HeaderText = L"Delete";
            this->DeleteButtonColumn->MinimumWidth = 6;
            this->DeleteButtonColumn->Name = L"DeleteButtonColumn";
            this->DeleteButtonColumn->ReadOnly = true;
            this->DeleteButtonColumn->Text = L"Delete";
            this->DeleteButtonColumn->Width = 125;
            // 
            // FollowsGridView
            // 
            this->FollowsGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->FollowsGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->FollowsNameColumn,
                    this->FollowerUnfollowColumn
            });
            this->FollowsGridView->Location = System::Drawing::Point(13, 310);
            this->FollowsGridView->Margin = System::Windows::Forms::Padding(2);
            this->FollowsGridView->Name = L"FollowsGridView";
            this->FollowsGridView->ReadOnly = true;
            this->FollowsGridView->RowHeadersWidth = 51;
            this->FollowsGridView->RowTemplate->Height = 24;
            this->FollowsGridView->Size = System::Drawing::Size(228, 122);
            this->FollowsGridView->TabIndex = 6;
            this->FollowsGridView->TabStop = false;
            // 
            // FollowsNameColumn
            // 
            this->FollowsNameColumn->HeaderText = L"Name";
            this->FollowsNameColumn->MinimumWidth = 6;
            this->FollowsNameColumn->Name = L"FollowsNameColumn";
            this->FollowsNameColumn->ReadOnly = true;
            this->FollowsNameColumn->Width = 125;
            // 
            // FollowerUnfollowColumn
            // 
            this->FollowerUnfollowColumn->HeaderText = L"Unfollow";
            this->FollowerUnfollowColumn->MinimumWidth = 6;
            this->FollowerUnfollowColumn->Name = L"FollowerUnfollowColumn";
            this->FollowerUnfollowColumn->ReadOnly = true;
            this->FollowerUnfollowColumn->Text = L"Unfollow";
            this->FollowerUnfollowColumn->Width = 125;
            // 
            // FollowersGridView
            // 
            this->FollowersGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->FollowersGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->FollowerColumn });
            this->FollowersGridView->Location = System::Drawing::Point(249, 310);
            this->FollowersGridView->Margin = System::Windows::Forms::Padding(2);
            this->FollowersGridView->Name = L"FollowersGridView";
            this->FollowersGridView->ReadOnly = true;
            this->FollowersGridView->RowHeadersWidth = 51;
            this->FollowersGridView->RowTemplate->Height = 24;
            this->FollowersGridView->Size = System::Drawing::Size(180, 122);
            this->FollowersGridView->TabIndex = 7;
            this->FollowersGridView->TabStop = false;
            // 
            // FollowerColumn
            // 
            this->FollowerColumn->HeaderText = L"Followers";
            this->FollowerColumn->MinimumWidth = 6;
            this->FollowerColumn->Name = L"FollowerColumn";
            this->FollowerColumn->ReadOnly = true;
            this->FollowerColumn->Width = 125;
            // 
            // SearchComboBox
            // 
            this->SearchComboBox->FormattingEnabled = true;
            this->SearchComboBox->Location = System::Drawing::Point(13, 13);
            this->SearchComboBox->Name = L"SearchComboBox";
            this->SearchComboBox->Size = System::Drawing::Size(255, 21);
            this->SearchComboBox->TabIndex = 8;
            this->SearchComboBox->TabStop = false;
			this->SearchComboBox->TextChanged += gcnew System::EventHandler(this, &Home::SearchComboBox_TextChanged);
			this->SearchComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Home::SearchComboBox_SelectedIndexChanged);

            // 
            // Home
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(438, 450);
            this->Controls->Add(this->SearchComboBox);
            this->Controls->Add(this->FollowersGridView);
            this->Controls->Add(this->FollowsGridView);
            this->Controls->Add(this->UserReposGridView);
            this->Controls->Add(this->RepoAddbutton);
            this->Controls->Add(this->RepoVisiblityradioButton);
            this->Controls->Add(this->NewRepotextBox);
            this->Controls->Add(this->Logoutbutton);
            this->Name = L"Home";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UserReposGridView))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FollowsGridView))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FollowersGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void NewRepotextBox_Enter(System::Object^ sender, EventArgs^ e) {
        // Clear the text when the textbox gets focus
        if (NewRepotextBox->Text == "name your new repo") {
            NewRepotextBox->Text = "";
        }
    }

    private: System::Void NewRepotextBox_Leave(System::Object^ sender, EventArgs^ e) {
        // Restore the placeholder text if the textbox is left empty
        if (String::IsNullOrEmpty(NewRepotextBox->Text)) {
            NewRepotextBox->Text = "name your new repo";
        }
    }
    private: System::Void DeleteButton_Click(System::Object^ sender, DataGridViewCellEventArgs^ e) {
        
		if (e->ColumnIndex == 3 && UserReposGridView->Rows->Count > 0) {
            // Get the name of the repository to be deleted
            string repoName = msclr::interop::marshal_as<std::string>(UserReposGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString());

            // Find and delete the repository from the user's list of repositories
            User* currentUser = userManager->getCurrentUser();
            currentUser->repos.remove(repoName);
            // Remove the row from the DataGridView
            UserReposGridView->Rows->RemoveAt(e->RowIndex);


            // Update the file containing the user's repositories
			ofstream file(currentUser->username + "'sRepos.csv");
			if (file.is_open()) {
				for (int i = 0; i < UserReposGridView->Rows->Count - 1; i++) {
					file << msclr::interop::marshal_as<std::string>(UserReposGridView->Rows[i]->Cells[0]->Value->ToString()) << " " << msclr::interop::marshal_as<std::string>(UserReposGridView->Rows[i]->Cells[1]->Value->ToString()) << " " << msclr::interop::marshal_as<std::string>(UserReposGridView->Rows[i]->Cells[2]->Value->ToString()) << endl;
				}
				file.close();
			}
			else {
				cerr << "Error: Unable to open file " << currentUser->username << "'sRepos.csv" << endl;
			}

			// Delete the file containing the repository's files
			string repoFileName = repoName + "Files.csv";
			if (remove(repoFileName.c_str()) != 0) {
				cerr << "Error: Unable to delete file " << repoFileName << endl;
			}
        }
    }

    private: System::Void UserReposGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
        //open SelectedRepo form with the selected repository name

        SelectedRepo^ selectedRepoForm = gcnew SelectedRepo(userManager, msclr::interop::marshal_as<std::string>(UserReposGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString()));
        try {
            selectedRepoForm->ShowDialog();
        }
        catch (Exception^ ex) {
            // Handle any exceptions that might occur
            MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void Logoutbutton_Click(System::Object^ sender, System::EventArgs^ e) {
        userManager->logout();

        this->Close();
    }
    private: System::Void RepoAddbutton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        string repoName = msclr::interop::marshal_as<std::string>(NewRepotextBox->Text);
        string visibility = RepoVisiblityradioButton->Checked ? "Private" : "Public";
        User* currentUser = userManager->getCurrentUser();
        
        Repository* newRepo = new Repository(repoName, 0, visibility == "Public" ? true : false);
         currentUser->repos.insert(*newRepo);
        UserReposGridView->Rows->Add(gcnew String(repoName.c_str()), "0", gcnew String(visibility.c_str()));
		RepoVisiblityradioButton->Checked = false;
        NewRepotextBox->Text = "name your new repo";
		// Update the file containing the user's repositories
		ofstream file(currentUser->username + "'sRepos.csv", ios::app);
        if (file.is_open()) {
			file << repoName << " 0 " << visibility << endl;
			file.close();
		}
        else {
            cerr << "Error: Unable to open file " << currentUser->username << "'sRepos.csv" << endl;
        }

        //create Repo file
		ofstream repoFile(repoName + "Files.csv");
        if (repoFile.is_open()) {
			repoFile.close();
		}
        else {
            cerr << "Error: Unable to open file " << repoName << ".csv" << endl;
        }
    }



    private:void LoadRepositories()
    {
        // Fetch all repositories of the current user from file
        User* currentUser = userManager->getCurrentUser();
        string username = currentUser->username;
        ifstream file(username + "'sRepos.csv");
        if (file.is_open()) {
            string repoName = "";
            int forkCount = -1;
            string visibility = "";
            while (file >> repoName >> forkCount >> visibility) {
				//Add the repository to the tree if repoName is not empty
                if (repoName != "" && forkCount != -1 && visibility != "") {
                    Repository* newRepo = new Repository(repoName, 0, visibility == "Public" ? true : false);
                    // Add the repository to the DataGridView
                    UserReposGridView->Rows->Add(gcnew String(repoName.c_str()), gcnew String(std::to_string(forkCount).c_str()), gcnew String(visibility.c_str()));
                }
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file " << username << "'sRepos.txt" << endl;
        }
    }

    private:void LoadFollowers()
    {
        // Fetch all followers of the current user from FollowRelationships.csv file
        string username = userManager->getCurrentUser()->username;
        ifstream file("FollowRelationships.csv");
        if (file.is_open()) {
            string follower, followed;
            while (file >> follower >> followed) {
                if (followed == username) {
                    // Add the follower to the DataGridView
                    FollowersGridView->Rows->Add(gcnew String(follower.c_str()));
                }
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file FollowRelationships.csv" << endl;
        }
    }

    private:void LoadFollows()
    {
        // Fetch all users the current user follows from FollowRelationships.csv file
        User* currentUser = userManager->getCurrentUser();
        string username = currentUser->username;
        ifstream file("FollowRelationships.csv");
        if (file.is_open()) {
            string follower, followed;
            while (file >> follower >> followed) {
                if (follower == username) {
                    // Add the user followed to the DataGridView
                    FollowsGridView->Rows->Add(gcnew String(followed.c_str()));
					FollowsGridView->Rows[FollowsGridView->Rows->Count - 1]->Cells[1]->Value = "Unfollow";
                }
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file FollowRelationships.csv" << endl;
        }
    }



    private: System::Void UnfollowButton_Click(System::Object^ sender, DataGridViewCellEventArgs^ e) {
		// Check if the Unfollow button was clicked

        if (e->ColumnIndex == 1 && FollowsGridView->Rows->Count > 1) {
            // Get the name of the user to be unfollowed
            string followed = msclr::interop::marshal_as<std::string>(FollowsGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString());
            string follower = userManager->getCurrentUser()->username;

            userManager->getNetwork()->unfollow(userManager->getNetwork()->getFollowerIndex(follower), userManager->getNetwork()->getFollowedIndex(followed));

            // Remove the row from the DataGridView
            FollowsGridView->Rows->RemoveAt(e->RowIndex);
        }
    }

    private: System::Void SearchComboBox_TextChanged(System::Object^ sender, EventArgs^ e) {
		//Don't do anyting if the combo box is empty and backspace is pressed
		if (SearchComboBox->Text->Length == 0) {
			SearchComboBox->DroppedDown = false;
			SearchComboBox->Items->Clear();
			return;
		}
        // Get the current cursor position
        int cursorPosition = SearchComboBox->SelectionStart;
        // Clear the existing items in the ComboBox
        SearchComboBox->Items->Clear();
        // Get the search query from the ComboBox
        String^ searchQuery = SearchComboBox->Text->Trim()->ToLower();
        // Ensure the current user is not null before accessing its username
        if (userManager->getCurrentUser() != nullptr) {
            string currentUsername = userManager->getCurrentUser()->username;

            // Check if the search query has at least one character before searching
            if (searchQuery->Length > 0) {
                for (int i = 0; i < userManager->getNetwork()->numUsers; ++i) {
                    String^ username = gcnew String(userManager->getNetwork()->users[i].c_str());

					// Check if the username starts with the search query and is not the current user
					if (username->StartsWith(searchQuery, StringComparison::OrdinalIgnoreCase) && username != gcnew String(currentUsername.c_str())) {
						SearchComboBox->Items->Add(username);
					}
                }
            }
        }
        // Display the ComboBox if there are search results and the query has at least one character
		SearchComboBox->DroppedDown = SearchComboBox->Items->Count > 0 && searchQuery->Length > 0;
        // Set the cursor position to the end of the text
        SearchComboBox->SelectionStart = cursorPosition;
    }

    private: System::Void SearchComboBox_SelectedIndexChanged(System::Object^ sender, EventArgs^ e) {
		//Open SearchedUser form
		SearchedUser^ searchedUserForm = gcnew SearchedUser(userManager, msclr::interop::marshal_as<std::string>(SearchComboBox->Text));
		
        // Subscribe to events from the searchedUserForm
		//searchedUserForm->UserFollowed += gcnew SearchedUser::UserActionEventHandler(this, &Home::OnUserFollowed);
		//searchedUserForm->UserUnfollowed += gcnew SearchedUser::UserActionEventHandler(this, &Home::OnUserUnfollowed);
        // Subscribe to similar events for forking repositories
		//searchedUserForm->RepoForked += gcnew SearchedUser::RepoActionEventHandler(this, &Home::OnRepoForked);
       try {
            searchedUserForm->ShowDialog();
        }
        catch (Exception^ ex) {
            // Handle any exceptions that might occur
            MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void OnUserFollowed(System::String^ username, bool isFollowed) {
        try {
            // Add the user to the DataGridView
            FollowsGridView->Rows->Add(username);
            FollowsGridView->Rows[FollowsGridView->Rows->Count - 1]->Cells[1]->Value = "Unfollow";
            // Refresh the DataGridView to update the UI
            FollowsGridView->Refresh();
        }
        catch (Exception^ ex) {
            // Handle any exceptions that might occur
            MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void OnUserUnfollowed(System::String^ username, bool isFollowed) {
        try {
            // Remove the user from the DataGridView
            for (int i = 0; i < FollowsGridView->Rows->Count; i++) {
                if (FollowsGridView->Rows[i]->Cells[0]->Value->ToString() == username) {
                    FollowsGridView->Rows->RemoveAt(i);
                    break;
                }
            }
            // Refresh the DataGridView to update the UI
            FollowsGridView->Refresh();
        }
        catch (Exception^ ex) {
            // Handle any exceptions that might occur
            MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void OnRepoForked(System::String^ repoName, int forkCount) {
		try {
			// Add the repository to the DataGridView
			UserReposGridView->Rows->Add(repoName, forkCount, "Public");
			// Refresh the DataGridView to update the UI
			UserReposGridView->Refresh();
		}
        catch (Exception^ ex) {
            // Handle any exceptions that might occur
            MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
};
}
