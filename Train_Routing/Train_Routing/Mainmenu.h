#pragma once
#include "Form1.h"
namespace Train_Routing {

	using namespace System::Runtime::InteropServices;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Mainmenu
	/// </summary>
	public ref class Mainmenu : public System::Windows::Forms::Form
	{
	public:
		//Constructor:
		Mainmenu()
		{
			InitializeComponent();

			//Drawing background
			this->BackColor = Color::FromArgb(255,2,4,28);

			//Initialize the button moving speed
			formSpeed = 10;

			//Login form 			
			login = new Log();
			loginform = gcnew Login(login);	

			/*
			This is to prevent the case that the user close the Login form.
			Player has to choose between using "player1" account for testing mode or input again.
			*/
			do
			{
				loginform -> ShowDialog();		//Show Login form
				UserID = Marshal::PtrToStringAnsi((IntPtr)(login->getUsername()));
				PassWord = Marshal::PtrToStringAnsi((IntPtr)(login->getPassword()));

				//Check if the information in "login" is the default information.
				if (UserID == "player1" && PassWord == "player1password")
					if (MessageBox::Show("You are attempting to close the login form.\r\nAre you sure to use the default username 'player1'?", "Error", MessageBoxButtons::OKCancel) == ::System::Windows::Forms::DialogResult::OK)
					{
						//If the player chooses to use "player1" for testing, "PassWord" is changed to 
						//break from while loop and build new account other than the default one.
						PassWord = "player1";
						login->setPassword((char*)"player1");
						if (login->existsUser() == -1)
							login->newUser();
					}
			} while (UserID == "player1" && PassWord == "player1password");	//Loop until the player do not close the form
			
			//Double buffering
			this->SetStyle(static_cast<ControlStyles>(
				ControlStyles::AllPaintingInWmPaint | 
				ControlStyles::DoubleBuffer | 
				ControlStyles::UserPaint), true);
			this->UpdateStyles();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Mainmenu()
		{
			if (components)
			{
				delete components;
				delete login;
			}
		}

	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;



	private:
		//Private:
		String^UserID, ^PassWord;//To store the input username and password
		Log*login;				//To create the object of "Log" class and store player information into file
		Login^loginform;		//The login form
		int formSpeed;			//Store the button moving speed;
		int destination;		//Store the destination of the button moving

	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  button9;

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panel4;


	private: System::ComponentModel::IContainer^  components;



		 /// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button2->FlatAppearance->BorderSize = 2;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(72, 38);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(146, 50);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Easy";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Mainmenu::button2_Click);
			// 
			// button3
			// 
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button3->FlatAppearance->BorderSize = 2;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(72, 92);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(146, 50);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Hard";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Mainmenu::button3_Click);
			// 
			// button4
			// 
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button4->FlatAppearance->BorderSize = 2;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(72, 146);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(146, 50);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Extreme";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Mainmenu::button4_Click);
			// 
			// button6
			// 
			this->button6->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button6->FlatAppearance->BorderSize = 2;
			this->button6->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button6->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button6->ForeColor = System::Drawing::Color::White;
			this->button6->Location = System::Drawing::Point(72, 355);
			this->button6->Margin = System::Windows::Forms::Padding(2);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(146, 50);
			this->button6->TabIndex = 7;
			this->button6->Text = L"Back";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Mainmenu::button6_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::LightGray;
			this->label3->Location = System::Drawing::Point(3, 26);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(377, 99);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Group 29: \r\n    ZHAO Tianyi, 13103359D\r\n    PENG Tao, 13104616D";
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(73, 101);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 1;
			this->button9->Text = L"button9";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Controls->Add(this->button12);
			this->panel1->Controls->Add(this->button11);
			this->panel1->Controls->Add(this->button10);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->button7);
			this->panel1->Controls->Add(this->button5);
			this->panel1->Location = System::Drawing::Point(1199, 0);
			this->panel1->Margin = System::Windows::Forms::Padding(2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(338, 450);
			this->panel1->TabIndex = 13;
			// 
			// button12
			// 
			this->button12->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button12->FlatAppearance->BorderSize = 2;
			this->button12->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button12->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button12->ForeColor = System::Drawing::Color::White;
			this->button12->Location = System::Drawing::Point(90, 92);
			this->button12->Margin = System::Windows::Forms::Padding(2);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(176, 50);
			this->button12->TabIndex = 13;
			this->button12->Text = L"Rules";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Mainmenu::button12_Click);
			// 
			// button11
			// 
			this->button11->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button11->FlatAppearance->BorderSize = 2;
			this->button11->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button11->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button11->ForeColor = System::Drawing::Color::White;
			this->button11->Location = System::Drawing::Point(90, 200);
			this->button11->Margin = System::Windows::Forms::Padding(2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(176, 50);
			this->button11->TabIndex = 12;
			this->button11->Text = L"Change Username";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Mainmenu::button11_Click);
			// 
			// button10
			// 
			this->button10->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button10->FlatAppearance->BorderSize = 2;
			this->button10->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button10->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button10->ForeColor = System::Drawing::Color::White;
			this->button10->Location = System::Drawing::Point(90, 146);
			this->button10->Margin = System::Windows::Forms::Padding(2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(176, 50);
			this->button10->TabIndex = 11;
			this->button10->Text = L"Highest Score";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Mainmenu::button10_Click);
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(90, 38);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(176, 50);
			this->button1->TabIndex = 0;
			this->button1->Text = L"New Game";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Mainmenu::button1_Click);
			// 
			// button7
			// 
			this->button7->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button7->FlatAppearance->BorderSize = 2;
			this->button7->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button7->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button7->ForeColor = System::Drawing::Color::White;
			this->button7->Location = System::Drawing::Point(90, 355);
			this->button7->Margin = System::Windows::Forms::Padding(2);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(176, 50);
			this->button7->TabIndex = 10;
			this->button7->Text = L"Exit";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Mainmenu::button7_Click);
			// 
			// button5
			// 
			this->button5->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button5->FlatAppearance->BorderSize = 2;
			this->button5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button5->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button5->ForeColor = System::Drawing::Color::White;
			this->button5->Location = System::Drawing::Point(90, 254);
			this->button5->Margin = System::Windows::Forms::Padding(2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(176, 50);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Developers";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Mainmenu::button5_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Transparent;
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->button6);
			this->panel2->Controls->Add(this->button3);
			this->panel2->Controls->Add(this->button4);
			this->panel2->Location = System::Drawing::Point(2509, 0);
			this->panel2->Margin = System::Windows::Forms::Padding(2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(293, 450);
			this->panel2->TabIndex = 14;
			// 
			// button8
			// 
			this->button8->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button8->FlatAppearance->BorderSize = 2;
			this->button8->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DeepSkyBlue;
			this->button8->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button8->ForeColor = System::Drawing::Color::White;
			this->button8->Location = System::Drawing::Point(36, 355);
			this->button8->Margin = System::Windows::Forms::Padding(2);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(181, 50);
			this->button8->TabIndex = 15;
			this->button8->Text = L"Back";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Mainmenu::button8_Click);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::Transparent;
			this->panel3->Controls->Add(this->label4);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Controls->Add(this->button8);
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Margin = System::Windows::Forms::Padding(2);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(346, 450);
			this->panel3->TabIndex = 16;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(110, 99);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 26);
			this->label4->TabIndex = 16;
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Mainmenu::timer1_Tick);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::Transparent;
			this->panel4->Controls->Add(this->panel3);
			this->panel4->Controls->Add(this->panel2);
			this->panel4->Controls->Add(this->panel1);
			this->panel4->Location = System::Drawing::Point(-743, 243);
			this->panel4->Margin = System::Windows::Forms::Padding(2);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(3000, 452);
			this->panel4->TabIndex = 17;
			// 
			// Mainmenu
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1274, 691);
			this->Controls->Add(this->panel4);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Mainmenu";
			this->Text = L"Mainmenu";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Mainmenu::Mainmenu_Paint);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		//Other components are listed behind the following part

		//*************************************************************//Animation effect starts
/*
This part contains the functions for animation effect for menu.
There are 3 sub-menus:
	main part (New Game, Rules, Highest Score, Change Username, Developers, Exit)
	game part (Easy, Hard, Extreme, Back)
	text part ("Some texts", Back)
For each sub-menu, a panel is built to control their positions.
There is a overall moving panel to control the three panels.
*/
//These three functions are designed for moving the main panel
 private: System::Void showMain()
		  {
			  //Destination is main part
			  MovePanel(0);
		  }
 private: System::Void showGame()
		  {
			  //Destination is game part
			  MovePanel(1);
		  }
 private: System::Void showText()
		  {
			  //Destination is text part
			  MovePanel(2);
		  }

//This function detects different destination and enable the timer
private: System::Void MovePanel(int destinationIndex)
			{
				switch(destinationIndex)
				{
				case 0:
					destination = -743;
					timer1->Enabled = true;
					break;
				case 1:
					destination = -2018;
					timer1->Enabled = true;
					break;
				case 2:
					destination = 512;
					timer1->Enabled = true;
					break;
				default:
					break;
				}
			}

//When the timer is enabled, the moving panel will move to its destination at decelerating speed.
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //Justify the location if it is near the destination
			 if (-formSpeed < panel4->Left - destination && panel4->Left - destination < formSpeed)
				 panel4->Left = destination;

			 //Decelerating 
			 formSpeed = (int)Math::Abs(panel4->Left - destination);
			 formSpeed /= 8;
			 formSpeed += 2;

			 //Determining the direction of moving and move
			 if (panel4->Left != destination)
			 {
				if(panel4->Left < destination)
					panel4->Left += formSpeed;
				else
					panel4->Left -= formSpeed;
			  }
			 else //Finish moving, unable the timer
				 timer1->Enabled = false;
		 }
		 //*************************************************************//Animation effect ends

		 //*** Sub-menu: game ***//
//Easy button
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 Form1^GameEasy = gcnew Form1(login,1);
				 GameEasy -> ShowDialog();
			 }

//Hard button
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 Form1^GameHard = gcnew Form1(login,2);
				 GameHard -> ShowDialog();
		 }

//Extreme button
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 Form1^GameExtreme = gcnew Form1(login,3);
				 GameExtreme -> ShowDialog();
		 }

//Back button for game panel
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 showMain();
		 }

		 //*** Sub-menu: main ***//
//New Game button
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 showGame();
		 }

//Developer button
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 label3->Text = "Group 29: \r\n    ZHAO Tianyi, 13103359D\r\n    PENG Tao, 13104616D";
			 label4->Text = "";
			 showText();
		 }

//Highest score button
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
			 label3->Text = "Your Highest Score is:";
			 label4->Text = ""+login->readHiScore();
			 showText();
		 }

//Change Account button
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
			 loginform -> ShowDialog();
			 UserID = Marshal::PtrToStringAnsi((IntPtr)(login->getUsername()));
			 this->Invalidate();
		 }

//Rules button
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
			 label3->Text = "Rules: \r\n     Don't crash your train!";
			 label4->Text = "";
			 showText();
		 }

//Exit button
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (MessageBox::Show("Are you sure to exit the game?", "Exit", MessageBoxButtons::OKCancel) == ::System::Windows::Forms::DialogResult::OK)
			 {
				 Application::Exit();
			 }
		 }

		 //*** Sub-menu: text ***//
//Back button for Text panel
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			 showMain();
		 }

//Drawing the background and texts
private: System::Void Mainmenu_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics ^ g = e->Graphics;
				 g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
				 
				 FontFamily ^ fontFamily = gcnew FontFamily("Arial");
				 StringFormat ^ strformat = gcnew StringFormat();
				 String ^ sTitle = "Train Routing";
				 String ^ sUserID = "Welcome " + UserID;


				 //Draw title and welcome text
				 Drawing2D::GraphicsPath ^ path = gcnew Drawing2D::GraphicsPath();
				 path->Reset();
				 path->AddString(sTitle, fontFamily, (int)FontStyle::Regular, 60.0f, PointF(460, 50), strformat);
				 path->AddString(sUserID, fontFamily, (int)FontStyle::Regular, 32.0f, PointF(500, 160), strformat);
				 path->CloseAllFigures();
				 for(int i=1; i<8; ++i)
				 {
					 Pen ^ pen = gcnew Pen(Color::FromArgb(20, 0, 128, 192), (float)i);
					 pen->LineJoin = Drawing2D::LineJoin::Round;
					 g->DrawPath(pen, path);
				 }

				 SolidBrush ^ brush = gcnew SolidBrush(Color::FromArgb(255, 200, 200, 228));
				 g->FillPath(brush, path);
		 }
};
}
