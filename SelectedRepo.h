#pragma once

#include "User.h"
#include "Repository.h"
#include "exception.h"
#include <string>
#include "File.h"
#include "SelectedFile.h"
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
	/// Summary for SelectedRepo
	/// </summary>
	public ref class SelectedRepo : public System::Windows::Forms::Form
	{
	private:
		UserManager* userManager;
	private: System::Windows::Forms::DataGridView^ SelectedRepoFilesdataGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ SelectedRepoFileNameColumn;
	private: System::Windows::Forms::TextBox^ newFileNametextBox;

	private: System::Windows::Forms::Button^ fileAddbutton;



		std::string* selectedRepoName;
	public:
		
		SelectedRepo(UserManager* _userManager, std::string _selectedRepoName)
		{
			userManager = _userManager;
			selectedRepoName = new std::string(_selectedRepoName);
			this->Text = gcnew String(selectedRepoName->c_str());
			InitializeComponent();
			LoadSelectedRepoContent();

			newFileNametextBox->Enter += gcnew System::EventHandler(this, &SelectedRepo::newFileNametextBox_Enter);
			newFileNametextBox->Leave += gcnew System::EventHandler(this, &SelectedRepo::newFileNametextBox_Leave);
		}

		void LoadSelectedRepoContent()
		{
			//open the selected reponamefile.csv file and insert the file names and add them to the dataGridView
			std::string repoName = *selectedRepoName;
			std::string repoFileName = repoName + "Files.csv";
			std::ifstream file(repoFileName);
			std::string line;
			while (std::getline(file, line))
			{
				SelectedRepoFilesdataGridView->Rows->Add(gcnew String(line.c_str()));
				userManager->getCurrentUser()->repos.search(*selectedRepoName)->files.addFile(line);
			}
			file.close();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectedRepo()
		{
			if (components)
			{
				delete components;
			}
			delete selectedRepoName;
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SelectedRepoFilesdataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->SelectedRepoFileNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->newFileNametextBox = (gcnew System::Windows::Forms::TextBox());
			this->fileAddbutton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SelectedRepoFilesdataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// SelectedRepoFilesdataGridView
			// 
			this->SelectedRepoFilesdataGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->SelectedRepoFilesdataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->SelectedRepoFilesdataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->SelectedRepoFileNameColumn });
			this->SelectedRepoFilesdataGridView->Location = System::Drawing::Point(33, 57);
			this->SelectedRepoFilesdataGridView->Name = L"SelectedRepoFilesdataGridView";
			this->SelectedRepoFilesdataGridView->ReadOnly = true;
			this->SelectedRepoFilesdataGridView->RowHeadersWidth = 51;
			this->SelectedRepoFilesdataGridView->RowTemplate->Height = 24;
			this->SelectedRepoFilesdataGridView->Size = System::Drawing::Size(348, 212);
			this->SelectedRepoFilesdataGridView->TabIndex = 0;
			this->SelectedRepoFilesdataGridView->TabStop = false;
			this->SelectedRepoFilesdataGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &SelectedRepo::SelectedRepoFilesdataGridView_CellContentClick);
			// 
			// SelectedRepoFileNameColumn
			// 
			this->SelectedRepoFileNameColumn->HeaderText = L"Files";
			this->SelectedRepoFileNameColumn->MinimumWidth = 6;
			this->SelectedRepoFileNameColumn->Name = L"SelectedRepoFileNameColumn";
			this->SelectedRepoFileNameColumn->ReadOnly = true;
			// 
			// newFileNametextBox
			// 
			this->newFileNametextBox->Location = System::Drawing::Point(33, 29);
			this->newFileNametextBox->Name = L"newFileNametextBox";
			this->newFileNametextBox->Size = System::Drawing::Size(193, 22);
			this->newFileNametextBox->TabIndex = 1;
			this->newFileNametextBox->TabStop = false;
			this->newFileNametextBox->Text = L"Name your new file";
			// 
			// fileAddbutton
			// 
			this->fileAddbutton->Location = System::Drawing::Point(306, 29);
			this->fileAddbutton->Name = L"fileAddbutton";
			this->fileAddbutton->Size = System::Drawing::Size(75, 23);
			this->fileAddbutton->TabIndex = 2;
			this->fileAddbutton->TabStop = false;
			this->fileAddbutton->Text = L"Add";
			this->fileAddbutton->UseVisualStyleBackColor = true;
			this->fileAddbutton->Click += gcnew System::EventHandler(this, &SelectedRepo::fileAddbutton_Click);
			// 
			// SelectedRepo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(418, 323);
			this->Controls->Add(this->fileAddbutton);
			this->Controls->Add(this->newFileNametextBox);
			this->Controls->Add(this->SelectedRepoFilesdataGridView);
			this->Name = L"SelectedRepo";
			this->Text = L"SelectedRepo";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SelectedRepoFilesdataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		
#pragma endregion
	
	private: System::Void newFileNametextBox_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (newFileNametextBox->Text == "name you new file ")
		{
			newFileNametextBox->Text = "";
		}
	}
	
	private: System::Void newFileNametextBox_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (newFileNametextBox->Text == "")
		{
			newFileNametextBox->Text = "name you new file ";
		}
	}

	private: System::Void SelectedRepoFilesdataGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		//open the selected file form and pass the selected file name
		std::string selectedFileName = msclr::interop::marshal_as<std::string>(SelectedRepoFilesdataGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString());
		SelectedFile^ selectedFileForm = gcnew SelectedFile(userManager, *selectedRepoName, selectedFileName);
		try {
			selectedFileForm->ShowDialog();
		}
		catch (Exception^ e) {
			MessageBox::Show("Error: " + e->Message);
		}
	}
	private: System::Void fileAddbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string newFileName = msclr::interop::marshal_as<std::string>(newFileNametextBox->Text);
		std::string repoName = *selectedRepoName;
		std::string repoFileName = repoName + "Files.csv";
		std::ofstream file(repoFileName, std::ios::app);
		file << newFileName << std::endl;
		file.close();
		SelectedRepoFilesdataGridView->Rows->Add(gcnew String(newFileName.c_str()));
		userManager->getCurrentUser()->repos.search(*selectedRepoName)->files.addFile(newFileName);
		newFileNametextBox->Text = "name you new file ";

		//create a new .csv file with the repoFileName
		std::string newFileDataFileName = repoName + newFileName + "Data.csv";
		std::ofstream newFileDataFile(newFileDataFileName);
		newFileDataFile.close();

		//create a new .csv file with the repoFileName
		std::string newFileCommitFileName = repoName + newFileName + "Commits.csv";
		std::ofstream newFileCommitFile(newFileCommitFileName);
		newFileCommitFile.close();
	}
};
}
