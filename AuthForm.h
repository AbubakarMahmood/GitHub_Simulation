#pragma once
#include "User.h"
#include "Home.h"
#include "Validation.h"
#include "exception.h"
#include <msclr/marshal_cppstd.h>


namespace GithubSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AuthForm
	/// </summary>
	public ref class AuthForm : public System::Windows::Forms::Form
	{
	public:
		AuthForm(void)
		{
			InitializeComponent();
			userManager = new UserManager();
			tries = 0;
			//
			//TODO: Add the constructor code here
			//

			// Initialize the user manager

			this->UsernametextBox->Enter += gcnew System::EventHandler(this, &AuthForm::UsernametextBox_Enter);
			this->UsernametextBox->Leave += gcnew System::EventHandler(this, &AuthForm::UsernametextBox_Leave);
			this->PasswordtextBox->Enter += gcnew System::EventHandler(this, &AuthForm::PasswordtextBox_Enter);
			this->PasswordtextBox->Leave += gcnew System::EventHandler(this, &AuthForm::PasswordtextBox_Leave);
			this->UsernametextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AuthForm::UsernametextBox_KeyPress);
			this->PasswordtextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AuthForm::PasswordtextBox_KeyPress);
			this->Loginbutton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AuthForm::Loginbutton_KeyPress);
			this->Signupbutton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AuthForm::Signupbutton_KeyPress);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AuthForm()
		{
			delete userManager;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ WelcometextBox;
	private: System::Windows::Forms::TextBox^ UsernametextBox;
	private: System::Windows::Forms::TextBox^ PasswordtextBox;
	private: System::Windows::Forms::Button^ Loginbutton;
	private: System::Windows::Forms::Button^ Signupbutton;
	protected:

	protected:

	protected:




	protected:

	private:
		UserManager* userManager;
		int tries;
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
			   this->WelcometextBox = (gcnew System::Windows::Forms::TextBox());
			   this->UsernametextBox = (gcnew System::Windows::Forms::TextBox());
			   this->PasswordtextBox = (gcnew System::Windows::Forms::TextBox());
			   this->Loginbutton = (gcnew System::Windows::Forms::Button());
			   this->Signupbutton = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // WelcometextBox
			   // 
			   this->WelcometextBox->Location = System::Drawing::Point(65, 42);
			   this->WelcometextBox->Multiline = true;
			   this->WelcometextBox->Name = L"WelcometextBox";
			   this->WelcometextBox->ReadOnly = true;
			   this->WelcometextBox->Size = System::Drawing::Size(149, 36);
			   this->WelcometextBox->TabIndex = 0;
			   this->WelcometextBox->TabStop = false;
			   this->WelcometextBox->Text = L"Welcome To Github Simulation";
			   this->WelcometextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			   this->WelcometextBox->TextChanged += gcnew System::EventHandler(this, &AuthForm::textBox1_TextChanged);
			   // 
			   // UsernametextBox
			   // 
			   this->UsernametextBox->Location = System::Drawing::Point(91, 99);
			   this->UsernametextBox->Name = L"UsernametextBox";
			   this->UsernametextBox->Size = System::Drawing::Size(100, 20);
			   this->UsernametextBox->TabIndex = 2;
			   this->UsernametextBox->TabStop = false;
			   this->UsernametextBox->Text = L"Username";
			   // 
			   // PasswordtextBox
			   // 
			   this->PasswordtextBox->Location = System::Drawing::Point(91, 125);
			   this->PasswordtextBox->Name = L"PasswordtextBox";
			   this->PasswordtextBox->Size = System::Drawing::Size(100, 20);
			   this->PasswordtextBox->TabIndex = 3;
			   this->PasswordtextBox->TabStop = false;
			   this->PasswordtextBox->Text = L"Password";
			   // 
			   // Loginbutton
			   // 
			   this->Loginbutton->Location = System::Drawing::Point(65, 160);
			   this->Loginbutton->Name = L"Loginbutton";
			   this->Loginbutton->Size = System::Drawing::Size(75, 23);
			   this->Loginbutton->TabIndex = 1;
			   this->Loginbutton->TabStop = false;
			   this->Loginbutton->Text = L"Login";
			   this->Loginbutton->UseVisualStyleBackColor = true;
			   this->Loginbutton->Click += gcnew System::EventHandler(this, &AuthForm::Loginbutton_Click);
			   // 
			   // Signupbutton
			   // 
			   this->Signupbutton->Location = System::Drawing::Point(146, 160);
			   this->Signupbutton->Name = L"Signupbutton";
			   this->Signupbutton->Size = System::Drawing::Size(75, 23);
			   this->Signupbutton->TabIndex = 4;
			   this->Signupbutton->TabStop = false;
			   this->Signupbutton->Text = L"Signup";
			   this->Signupbutton->UseVisualStyleBackColor = true;
			   this->Signupbutton->Click += gcnew System::EventHandler(this, &AuthForm::Signupbutton_Click);
			   // 
			   // AuthForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(284, 261);
			   this->Controls->Add(this->PasswordtextBox);
			   this->Controls->Add(this->UsernametextBox);
			   this->Controls->Add(this->Loginbutton);
			   this->Controls->Add(this->Signupbutton);
			   this->Controls->Add(this->WelcometextBox);
			   this->Name = L"AuthForm";
			   this->Text = L"Login";
			   this->Load += gcnew System::EventHandler(this, &AuthForm::AuthForm_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void UsernametextBox_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (UsernametextBox->Text == "Username") {
			UsernametextBox->Text = "";
		}
	}
	private: System::Void UsernametextBox_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (UsernametextBox->Text == "") {
			UsernametextBox->Text = "Username";
		}
	}
	private: System::Void PasswordtextBox_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (PasswordtextBox->Text == "Password") {
			PasswordtextBox->Text = "";
		}
	}
	private: System::Void PasswordtextBox_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (PasswordtextBox->Text == "") {
			PasswordtextBox->Text = "Password";
		}
	}

	private: System::Void UsernametextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter || e->KeyChar == (char)Keys::Tab) {
			// Move focus to the password textbox
			PasswordtextBox->Focus();
		}
	}

	private: System::Void PasswordtextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			// Trigger the Click event of the login button
			Loginbutton_Click(sender, e);
		}
		else if (e->KeyChar == (char)Keys::Tab) {
			// Move focus back to the username textbox
			Loginbutton->Focus();
		}
	}

	private: System::Void Loginbutton_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			// Trigger the Click event of the login button
			Loginbutton_Click(sender, e);
		}
		else if (e->KeyChar == (char)Keys::Tab) {
			// Move focus back to the username textbox
			Signupbutton->Focus();
		}
	}

	private: System::Void Signupbutton_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			// Trigger the Click event of the login button
			Signupbutton_Click(sender, e);
		}
		else if (e->KeyChar == (char)Keys::Tab) {
			// Move focus back to the username textbox
			UsernametextBox->Focus();
		}
	}

	private: System::Void Loginbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Get the username and password from the text boxes
		String^ username = UsernametextBox->Text;
		String^ password = PasswordtextBox->Text;

		// Convert the strings to std::string
		std::string usernameStr = msclr::interop::marshal_as<std::string>(username);
		std::string passwordStr = msclr::interop::marshal_as<std::string>(password);

		bool result = userManager->login(usernameStr, passwordStr);
		if (result)
		{


			MessageBox::Show("Loggin In!");
			Home^ home = gcnew Home(userManager);
			home->ShowDialog();
			this->Close();

		}
		else
		{
			MessageBox::Show("Login Failed!");
			tries++;
			if (tries == 3)
			{
				MessageBox::Show("You have exceeded the number of tries!");
				System::Threading::Thread::Sleep(3000);
				this->Close();
			}
		}
	}

	private: System::Void Signupbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ username = UsernametextBox->Text;
		String^ password = PasswordtextBox->Text;

		std::string usernameStr = msclr::interop::marshal_as<std::string>(username);
		std::string passwordStr = msclr::interop::marshal_as<std::string>(password);

		// Validate username
		std::string errorMessage;
		if (!Validation::isValidUsername(usernameStr, errorMessage)) {
			MessageBox::Show(gcnew String(errorMessage.c_str()), "Invalid Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Validate password
		if (!Validation::isValidPassword(passwordStr, errorMessage)) {
			MessageBox::Show(gcnew String(errorMessage.c_str()), "Invalid Password", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Check if username already exists
		if (userManager->usernameExists(usernameStr)) {
			MessageBox::Show("Username already exists! Please choose a different username.", "Registration Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Register the user
		if (userManager->registerUser(usernameStr, passwordStr)) {
			MessageBox::Show("User registered successfully! You can now login.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			MessageBox::Show("Registration failed! Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void AuthForm_Load(System::Object^ sender, System::EventArgs^ e) {
		UsernametextBox->Focus();
	}
};
}






