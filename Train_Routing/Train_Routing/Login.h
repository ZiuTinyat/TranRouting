#pragma once
#include "Loginlib.h"
namespace Train_Routing {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::IO;

	/// <summary>
	/// Summary for Login
	/// </summary>
	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		//Constructor: receive the pointer of login from Mainmenu
		Login(Log * login)
		{
			InitializeComponent();
			log = login;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;

	private:
		//Private 
		String^Username, ^Password;//Store the input Username and Password in String
		Log*log;//Store the pointer of login in Mainmenu
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(232, 92);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(149, 23);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"‘v‘Ì", 12));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(109, 91);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 22);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Username";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"‘v‘Ì", 12));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(109, 149);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 22);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password";
			// 
			// textBox2
			// 
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Location = System::Drawing::Point(232, 149);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(149, 23);
			this->textBox2->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Cyan;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(181, 221);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(114, 43);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Log in";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Login::button1_Click);
			// 
			// Login
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(4)), 
				static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->ClientSize = System::Drawing::Size(494, 338);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"Login";
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Check the state of Username
				 Username = textBox1->Text;
				 Password = textBox2->Text;
				 bool loginagain = true;	//If true, the form still exists; if false, the form is hidden and the Mainmenu appears
				 if (Username == "")
				 {
					 MessageBox::Show("Username cannot be blank!", "", MessageBoxButtons::OK);
				 }
				 else if (Username == "player1")	//"Player1" is the default username and should not be used. This is to avoid some errors in terms of writing score.
				 {
					 MessageBox::Show("This username is not allowed!", "", MessageBoxButtons::OK);
				 }
				 else if (Password == "")
				 {
					 MessageBox::Show("Password cannot be blank!", "", MessageBoxButtons::OK);
				 }
				 else
				 {
					 //If the input is valid, write in "login"
					 log->setUsername((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Username).ToPointer());
					 log->setPassword((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Password).ToPointer());
					 log->setScore(0);

					 //Examine the state of username
					 int x = log->existsUser();
					 switch (x)
					 {
					 case -1:	//Username does not exist
						 if (MessageBox::Show("The Username does not exist. \nDo you want to register a new account?", "New account", MessageBoxButtons::YesNo)
							 == ::System::Windows::Forms::DialogResult::Yes)
						 {
							 //Create a new account
							 log->newUser();
							 loginagain = false;
						 }
						 else
						 {
							 loginagain = true;//input again
						 }
						 break;

					 case 0:	//Password is wrong
						 MessageBox::Show("Wrong password. Input again!", "Failed", MessageBoxButtons::OK);
						 loginagain = true;//input again
						 break;

					 case 1:	//Username exists and password is correct
						 loginagain = false;
						 break;
					 }

					 if (loginagain)
					 {
	
					 }
					 else
					 {
						 this->Close();
					 }
				 }
			 }
};
}
