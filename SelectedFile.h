#pragma once

#include "User.h"
#include "Repository.h"
#include "Commit.h"
#include "exception.h"
#include <string>
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <sstream>

namespace GithubSimulation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for SelectedFile
    /// </summary>
    public ref class SelectedFile : public System::Windows::Forms::Form
    {
    private:
        UserManager* userManager;
    private: System::Windows::Forms::RichTextBox^ fileDatarichTextBox;
    private: System::Windows::Forms::DataGridView^ commitsdataGridView;

    private: System::Windows::Forms::DataGridViewTextBoxColumn^ CommitColumn;
    private: System::Windows::Forms::Button^ commitAddbutton;
    private: System::Windows::Forms::Button^ fileDataSavebutton;

        std::string* selectedFileName;
    private: System::Windows::Forms::TextBox^ newCommittextBox;

           std::string* selectedRepoName;

    public:
        SelectedFile(UserManager* _userManager, std::string _selectedRepoName, std::string _selectedFileName)
        {
            userManager = _userManager;
            selectedFileName = new std::string(_selectedFileName);
            selectedRepoName = new std::string(_selectedRepoName);
            this->Text = gcnew String(selectedFileName->c_str());
            InitializeComponent();
            LoadSelectedFileData();
            LoadSelectedFileCommits();

        }
        void LoadSelectedFileData()
        {
            std::string selectedFileNameStr = *selectedRepoName + *selectedFileName + "Data.csv";
            std::ifstream datafile(selectedFileNameStr);
            std::string line;
            while (std::getline(datafile, line))
            {
                fileDatarichTextBox->Text += gcnew String(line.c_str());
            }
            datafile.close();
        }
        void LoadSelectedFileCommits()
        {
			std::string commitFileName = *selectedRepoName + *selectedFileName + "Commits.csv";
			std::ifstream commitFile(commitFileName);
			std::string line;
			while (std::getline(commitFile, line))
			{
				commitsdataGridView->Rows->Add(gcnew String(line.c_str()));
			}
			commitFile.close();
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~SelectedFile()
        {
            if (components)
            {
                delete components;
            }
            delete selectedFileName;
            delete selectedRepoName;
        }
    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container ^ components; 
#pragma region Windows Form Designer generated code
            /// <summary>
            /// Required method for Designer support - do not modify
            /// the contents of this method with the code editor.
            /// </summary>
            void InitializeComponent(void)
        {
                this->fileDatarichTextBox = (gcnew System::Windows::Forms::RichTextBox());
                this->commitsdataGridView = (gcnew System::Windows::Forms::DataGridView());
                this->CommitColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
                this->commitAddbutton = (gcnew System::Windows::Forms::Button());
                this->fileDataSavebutton = (gcnew System::Windows::Forms::Button());
                this->newCommittextBox = (gcnew System::Windows::Forms::TextBox());
                (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->commitsdataGridView))->BeginInit();
                this->SuspendLayout();
                // 
                // fileDatarichTextBox
                // 
                this->fileDatarichTextBox->Location = System::Drawing::Point(58, 57);
                this->fileDatarichTextBox->Name = L"fileDatarichTextBox";
                this->fileDatarichTextBox->Size = System::Drawing::Size(416, 153);
                this->fileDatarichTextBox->TabIndex = 0;
                this->fileDatarichTextBox->TabStop = false;
                this->fileDatarichTextBox->Text = L"";
                // 
                // commitsdataGridView
                // 
                this->commitsdataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
                this->commitsdataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->CommitColumn });
                this->commitsdataGridView->Location = System::Drawing::Point(58, 264);
                this->commitsdataGridView->Name = L"commitsdataGridView";
                this->commitsdataGridView->RowHeadersWidth = 51;
                this->commitsdataGridView->RowTemplate->Height = 24;
                this->commitsdataGridView->Size = System::Drawing::Size(416, 150);
                this->commitsdataGridView->TabIndex = 1;
                this->commitsdataGridView->TabStop = false;
                // 
                // CommitColumn
                // 
                this->CommitColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
                this->CommitColumn->HeaderText = L"Commits";
                this->CommitColumn->MinimumWidth = 6;
                this->CommitColumn->Name = L"CommitColumn";
                this->CommitColumn->ReadOnly = true;
                // 
                // commitAddbutton
                // 
                this->commitAddbutton->Location = System::Drawing::Point(399, 235);
                this->commitAddbutton->Name = L"commitAddbutton";
                this->commitAddbutton->Size = System::Drawing::Size(75, 23);
                this->commitAddbutton->TabIndex = 2;
                this->commitAddbutton->TabStop = false;
                this->commitAddbutton->Text = L"Add";
                this->commitAddbutton->UseVisualStyleBackColor = true;
                this->commitAddbutton->Click += gcnew System::EventHandler(this, &SelectedFile::commitAddbutton_Click);
                // 
                // fileDataSavebutton
                // 
                this->fileDataSavebutton->Location = System::Drawing::Point(399, 28);
                this->fileDataSavebutton->Name = L"fileDataSavebutton";
                this->fileDataSavebutton->Size = System::Drawing::Size(75, 23);
                this->fileDataSavebutton->TabIndex = 3;
                this->fileDataSavebutton->TabStop = false;
                this->fileDataSavebutton->Text = L"Save";
                this->fileDataSavebutton->UseVisualStyleBackColor = true;
                this->fileDataSavebutton->Click += gcnew System::EventHandler(this, &SelectedFile::fileDataSavebutton_Click);
                // 
                // newCommittextBox
                // 
                this->newCommittextBox->Location = System::Drawing::Point(58, 236);
                this->newCommittextBox->Name = L"newCommittextBox";
                this->newCommittextBox->Size = System::Drawing::Size(234, 22);
                this->newCommittextBox->TabIndex = 4;
                this->newCommittextBox->TabStop = false;
                this->newCommittextBox->Text = L"Enter your new commit";
                // 
                // SelectedFile
                // 
                this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
                this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                this->ClientSize = System::Drawing::Size(536, 439);
                this->Controls->Add(this->newCommittextBox);
                this->Controls->Add(this->fileDataSavebutton);
                this->Controls->Add(this->commitAddbutton);
                this->Controls->Add(this->commitsdataGridView);
                this->Controls->Add(this->fileDatarichTextBox);
                this->Name = L"SelectedFile";
                this->Text = L"SelectedFile";
                (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->commitsdataGridView))->EndInit();
                this->ResumeLayout(false);
                this->PerformLayout();

            }
#pragma endregion
    private: System::Void commitAddbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string commit = msclr::interop::marshal_as<std::string>(newCommittextBox->Text);
		std::string commitFileName = *selectedRepoName + *selectedFileName + "Commits.csv";
		std::ofstream commitFile(commitFileName, std::ios::app);
		commitFile << commit << std::endl;
		commitFile.close();
		//add the commit to current users selected repos commits
        
		userManager->getCurrentUser()->repos.search(*selectedRepoName)->files.search(*selectedFileName)->commits.addCommit(commit);
        
        commitsdataGridView->Rows->Add(newCommittextBox->Text);
    }
    private: System::Void fileDataSavebutton_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string selectedFileNameStr = *selectedRepoName + *selectedFileName + "Data.csv";
		//open the file in truncate mode to clear the file
		std::ofstream datafile(selectedFileNameStr, std::ios::trunc);
        datafile << msclr::interop::marshal_as<std::string>(fileDatarichTextBox->Text);
		datafile.close();
		//clear the rich text box
		fileDatarichTextBox->Text = "";
        LoadSelectedFileData();
    }
};
}