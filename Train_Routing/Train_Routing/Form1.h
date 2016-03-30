#pragma once
#include "GameObject.h"
#include "Login.h"
#include <cstdlib>
#include <ctime>

namespace Train_Routing {

	using namespace System::Runtime::InteropServices;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(Log * login,int diff)
		{
			InitializeComponent();
			//Login file
			log = login;
			UserID = Marshal::PtrToStringAnsi((IntPtr)(log->getUsername()));
			label2->Text = "Welcome! "+UserID;

			//Double buffering
			this->SetStyle(static_cast<ControlStyles>(
				ControlStyles::AllPaintingInWmPaint | 
				ControlStyles::DoubleBuffer | 
				ControlStyles::UserPaint), true);
			this->UpdateStyles();

			//Setup random seed.
			srand((unsigned int)time(NULL));

			//Settings
			//label1 : Welcome! UserID
			//label2 : Remain Time
			//label3 : Score

			//Setting the style of label
			label1->BackColor = Color::FromArgb(0,2,4,20);
			label1->ForeColor = Color::White;
			label2->BackColor = Color::FromArgb(0,2,4,20);
			label2->ForeColor = Color::White;
			label3->BackColor = Color::FromArgb(0,2,4,20);
			label3->ForeColor = Color::White;
			
			difficulty = diff; //Get difficulty setting from constructor parameter.
			switch(difficulty)
			{
			case 1:
				//Easy
				AvgSpeed = 10.0f;
				RandomSpeedRange = 2.0f;
				RespawnUnitTime = 4000;
				maxAllowedTrain = 3;
				ghostTrainColoredTime = 12000;
				break;
			case 2:
				//Hard
				AvgSpeed = 15.0f;
				RandomSpeedRange = 3.0f;
				RespawnUnitTime = 3000;
				maxAllowedTrain = 4;
				ghostTrainColoredTime = 15000;
				break;
			case 3:
				//Extreme
				AvgSpeed = 23.0f;
				RandomSpeedRange = 5.0f;
				RespawnUnitTime = 2000;
				maxAllowedTrain = 5;
				ghostTrainColoredTime = 15000;
				break;
			default:
				break;
			}
			counttime = -3;				//Set freezing time before game start
			gametime = 120;				//Set total game time
			score = 0;					//Initialize score to 0
			totalTrainCount = 0;		//Initialize total train count to 0
			collisionDistance = 10.0f;	//Set global collision trigger distance
			pause = true;				//Pause the game at beginning
			isMapped = false;			//Initially, the map and static image is not drew.
			isGhostTrain = false;

			j = new Joint[31];			//an array of pointer to joint objects
			t = new Track[34];			//an array of pointer to track objects
			
			//Setup the position and connect relation of joints
			*(j + 0) = Joint(j + 15, j + 15, Transform(1020.00f, 940.00f));
			*(j + 1) = Joint(j + 11, j + 11, Transform(100.00f, 620.00f));
			*(j + 2) = Joint(j + 10, j + 10, Transform(240.00f, 100.00f));
			*(j + 3) = Joint(j + 30, j + 30, Transform(1080.00f, 104.00f));
			*(j + 4) = Joint(j + 6, j + 20, j + 19, Transform(868.00f, 534.00f));
			*(j + 5) = Joint(j + 7, j + 20, j + 13, Transform(982.00f, 374.00f));
			*(j + 6) = Joint(j + 4, j + 23, j + 21, Transform(616.00f, 358.00f));
			*(j + 7) = Joint(j + 5, j + 29, j + 30, Transform(932.00f, 264.00f));
			*(j + 8) = Joint(j + 29, j + 22, j + 25, Transform(600.00f, 152.00f));
			*(j + 9) = Joint(j + 11, j + 24, j + 12, Transform(306.00f, 420.00f));
			*(j + 10) = Joint(j + 26, j + 2, j + 25, Transform(136.00f, 268.00f));
			*(j + 11) = Joint(j + 9, j + 1, j + 28, Transform(208.00f, 516.00f));
			*(j + 12) = Joint(j + 13, j + 14, j + 9, Transform(464.00f, 420.00f));
			*(j + 13) = Joint(j + 12, j + 5, j + 18, Transform(592.00f, 472.00f));
			*(j + 14) = Joint(j + 12, Transform(290.00f, 700.00f));
			*(j + 15) = Joint(j + 0, j + 16, j + 17, Transform(960.00f, 820.00f));
			*(j + 16) = Joint(j + 15, j + 18, j + 18, Transform(860.00f, 780.00f));
			*(j + 17) = Joint(j + 15, j + 19, j + 19, Transform(1056.00f, 780.00f));
			*(j + 18) = Joint(j + 16, j + 13, j + 13, Transform(772.00f, 636.00f));
			*(j + 19) = Joint(j + 17, j + 4, j + 4, Transform(951.20f, 592.00f));
			*(j + 20) = Joint(j + 5, j + 4, j + 4, Transform(964.00f, 496.00f));
			*(j + 21) = Joint(j + 6, j + 22, j + 22, Transform(568.00f, 266.00f));
			*(j + 22) = Joint(j + 8, j + 21, j + 21, Transform(560.00f, 224.00f));
			*(j + 23) = Joint(j + 6, j + 24, j + 24, Transform(526.00f, 328.00f));
			*(j + 24) = Joint(j + 23, j + 9, j + 9, Transform(424.00f, 328.00f));
			*(j + 25) = Joint(j + 8, j + 10, j + 10, Transform(212.00f, 240.00f));
			*(j + 26) = Joint(j + 10, j + 27, j + 27, Transform(72.00f, 328.00f));
			*(j + 27) = Joint(j + 26, j + 28, j + 28, Transform(60.00f, 420.00f));
			*(j + 28) = Joint(j + 27, j + 11, j + 11, Transform(134.00f, 508.00f));
			*(j + 29) = Joint(j + 7, j + 8, j + 8, Transform(796.00f, 188.00f));
			*(j + 30) = Joint(j + 3, j + 7, j + 7, Transform(970.00f, 168.00f));

			//Setup the track connections between joints
			*(t + 0) = Track(j + 0, j + 15);
			*(t + 1) = Track(j + 15, j + 16);
			*(t + 2) = Track(j + 17, j + 15);
			*(t + 3) = Track(j + 16, j + 18);
			*(t + 4) = Track(j + 17, j + 19);
			*(t + 5) = Track(j + 18, j + 13);
			*(t + 6) = Track(j + 4, j + 6);
			*(t + 7) = Track(j + 20, j + 4);
			*(t + 8) = Track(j + 5, j + 20);
			*(t + 9) = Track(j + 5, j + 7);
			*(t + 10) = Track(j + 7, j + 29);
			*(t + 11) = Track(j + 13, j + 12);
			*(t + 12) = Track(j + 5, j + 13);
			*(t + 13) = Track(j + 12, j + 9);
			*(t + 14) = Track(j + 6, j + 23);
			*(t + 15) = Track(j + 6, j + 21);
			*(t + 16) = Track(j + 23, j + 24);
			*(t + 17) = Track(j + 21, j + 22);
			*(t + 18) = Track(j + 29, j + 8);
			*(t + 19) = Track(j + 30, j + 7);
			*(t + 20) = Track(j + 3, j + 30);
			*(t + 21) = Track(j + 8, j + 22);
			*(t + 22) = Track(j + 11, j + 1);
			*(t + 23) = Track(j + 9, j + 11);
			*(t + 24) = Track(j + 24, j + 9);
			*(t + 25) = Track(j + 8, j + 25);
			*(t + 26) = Track(j + 11, j + 28);
			*(t + 27) = Track(j + 28, j + 27);
			*(t + 28) = Track(j + 26, j + 27);
			*(t + 29) = Track(j + 10, j + 26);
			*(t + 30) = Track(j + 2, j + 10);
			*(t + 31) = Track(j + 25, j + 10);
			*(t + 32) = Track(j + 19, j + 4);
			*(t + 33) = Track(j + 12, j + 14);

			//Update the pointer connection to make sure the pointer is pointed to correct object

			//j0 setup
			(j + 0)->setTrack0(nullptr);
			(j + 0)->setTrack1(t + 0);
			(j + 0)->setTrack2(t + 0);
			(j + 0)->setNode0(nullptr);
			(j + 0)->setNode1(j + 15);
			(j + 0)->setNode2(j + 15);

			//j1 setup
			(j + 1)->setTrack0(nullptr);
			(j + 1)->setTrack1(t + 22);
			(j + 1)->setTrack2(t + 22);
			(j + 1)->setNode0(nullptr);
			(j + 1)->setNode1(j + 11);
			(j + 1)->setNode2(j + 11);

			//j2 setup
			(j + 2)->setTrack0(nullptr);
			(j + 2)->setTrack1(t + 30);
			(j + 2)->setTrack2(t + 30);
			(j + 2)->setNode0(nullptr);
			(j + 2)->setNode1(j + 10);
			(j + 2)->setNode2(j + 10);

			//j3 setup
			(j + 3)->setTrack0(nullptr);
			(j + 3)->setTrack1(t + 20);
			(j + 3)->setTrack2(t + 20);
			(j + 3)->setNode0(nullptr);
			(j + 3)->setNode1(j + 30);
			(j + 3)->setNode2(j + 30);

			//j4 setup
			(j + 4)->setTrack0(t + 6);
			(j + 4)->setTrack1(t + 7);
			(j + 4)->setTrack2(t + 32);
			(j + 4)->setNode0(j + 6);
			(j + 4)->setNode1(j + 20);
			(j + 4)->setNode2(j + 19);

			//j5 setup
			(j + 5)->setTrack0(t + 9);
			(j + 5)->setTrack1(t + 8);
			(j + 5)->setTrack2(t + 12);
			(j + 5)->setNode0(j + 7);
			(j + 5)->setNode1(j + 20);
			(j + 5)->setNode2(j + 13);

			//j6 setup
			(j + 6)->setTrack0(t + 6);
			(j + 6)->setTrack1(t + 14);
			(j + 6)->setTrack2(t + 15);
			(j + 6)->setNode0(j + 4);
			(j + 6)->setNode1(j + 23);
			(j + 6)->setNode2(j + 21);

			//j7 setup
			(j + 7)->setTrack0(t + 9);
			(j + 7)->setTrack1(t + 10);
			(j + 7)->setTrack2(t + 19);
			(j + 7)->setNode0(j + 5);
			(j + 7)->setNode1(j + 29);
			(j + 7)->setNode2(j + 30);

			//j8 setup
			(j + 8)->setTrack0(t + 18);
			(j + 8)->setTrack1(t + 21);
			(j + 8)->setTrack2(t + 25);
			(j + 8)->setNode0(j + 29);
			(j + 8)->setNode1(j + 22);
			(j + 8)->setNode2(j + 25);

			//j9 setup
			(j + 9)->setTrack0(t + 23);
			(j + 9)->setTrack1(t + 24);
			(j + 9)->setTrack2(t + 13);
			(j + 9)->setNode0(j + 11);
			(j + 9)->setNode1(j + 24);
			(j + 9)->setNode2(j + 12);

			//j10 setup
			(j + 10)->setTrack0(t + 29);
			(j + 10)->setTrack1(t + 30);
			(j + 10)->setTrack2(t + 31);
			(j + 10)->setNode0(j + 26);
			(j + 10)->setNode1(j + 2);
			(j + 10)->setNode2(j + 25);

			//j11 setup
			(j + 11)->setTrack0(t + 23);
			(j + 11)->setTrack1(t + 22);
			(j + 11)->setTrack2(t + 26);
			(j + 11)->setNode0(j + 9);
			(j + 11)->setNode1(j + 1);
			(j + 11)->setNode2(j + 28);

			//j12 setup
			(j + 12)->setTrack0(t + 11);
			(j + 12)->setTrack1(t + 33);
			(j + 12)->setTrack2(t + 13);
			(j + 12)->setNode0(j + 13);
			(j + 12)->setNode1(j + 14);
			(j + 12)->setNode2(j + 9);

			//j13 setup
			(j + 13)->setTrack0(t + 11);
			(j + 13)->setTrack1(t + 12);
			(j + 13)->setTrack2(t + 5);
			(j + 13)->setNode0(j + 12);
			(j + 13)->setNode1(j + 5);
			(j + 13)->setNode2(j + 18);

			//j14 setup
			(j + 14)->setTrack0(t + 33);
			(j + 14)->setTrack1(nullptr);
			(j + 14)->setTrack2(nullptr);
			(j + 14)->setNode0(j + 12);
			(j + 14)->setNode1(nullptr);
			(j + 14)->setNode2(nullptr);

			//j15 setup
			(j + 15)->setTrack0(t + 0);
			(j + 15)->setTrack1(t + 1);
			(j + 15)->setTrack2(t + 2);
			(j + 15)->setNode0(j + 0);
			(j + 15)->setNode1(j + 16);
			(j + 15)->setNode2(j + 17);

			//j16 setup
			(j + 16)->setTrack0(t + 1);
			(j + 16)->setTrack1(t + 3);
			(j + 16)->setTrack2(t + 3);
			(j + 16)->setNode0(j + 15);
			(j + 16)->setNode1(j + 18);
			(j + 16)->setNode2(j + 18);

			//j17 setup
			(j + 17)->setTrack0(t + 2);
			(j + 17)->setTrack1(t + 4);
			(j + 17)->setTrack2(t + 4);
			(j + 17)->setNode0(j + 15);
			(j + 17)->setNode1(j + 19);
			(j + 17)->setNode2(j + 19);

			//j18 setup
			(j + 18)->setTrack0(t + 3);
			(j + 18)->setTrack1(t + 5);
			(j + 18)->setTrack2(t + 5);
			(j + 18)->setNode0(j + 16);
			(j + 18)->setNode1(j + 13);
			(j + 18)->setNode2(j + 13);

			//j19 setup
			(j + 19)->setTrack0(t + 4);
			(j + 19)->setTrack1(t + 32);
			(j + 19)->setTrack2(t + 32);
			(j + 19)->setNode0(j + 17);
			(j + 19)->setNode1(j + 4);
			(j + 19)->setNode2(j + 4);

			//j20 setup
			(j + 20)->setTrack0(t + 8);
			(j + 20)->setTrack1(t + 7);
			(j + 20)->setTrack2(t + 7);
			(j + 20)->setNode0(j + 5);
			(j + 20)->setNode1(j + 4);
			(j + 20)->setNode2(j + 4);

			//j21 setup
			(j + 21)->setTrack0(t + 15);
			(j + 21)->setTrack1(t + 17);
			(j + 21)->setTrack2(t + 17);
			(j + 21)->setNode0(j + 6);
			(j + 21)->setNode1(j + 22);
			(j + 21)->setNode2(j + 22);

			//j22 setup
			(j + 22)->setTrack0(t + 21);
			(j + 22)->setTrack1(t + 17);
			(j + 22)->setTrack2(t + 17);
			(j + 22)->setNode0(j + 8);
			(j + 22)->setNode1(j + 21);
			(j + 22)->setNode2(j + 21);

			//j23 setup
			(j + 23)->setTrack0(t + 14);
			(j + 23)->setTrack1(t + 16);
			(j + 23)->setTrack2(t + 16);
			(j + 23)->setNode0(j + 6);
			(j + 23)->setNode1(j + 24);
			(j + 23)->setNode2(j + 24);

			//j24 setup
			(j + 24)->setTrack0(t + 16);
			(j + 24)->setTrack1(t + 24);
			(j + 24)->setTrack2(t + 24);
			(j + 24)->setNode0(j + 23);
			(j + 24)->setNode1(j + 9);
			(j + 24)->setNode2(j + 9);

			//j25 setup
			(j + 25)->setTrack0(t + 25);
			(j + 25)->setTrack1(t + 31);
			(j + 25)->setTrack2(t + 31);
			(j + 25)->setNode0(j + 8);
			(j + 25)->setNode1(j + 10);
			(j + 25)->setNode2(j + 10);

			//j26 setup
			(j + 26)->setTrack0(t + 29);
			(j + 26)->setTrack1(t + 28);
			(j + 26)->setTrack2(t + 28);
			(j + 26)->setNode0(j + 10);
			(j + 26)->setNode1(j + 27);
			(j + 26)->setNode2(j + 27);

			//j27 setup
			(j + 27)->setTrack0(t + 28);
			(j + 27)->setTrack1(t + 27);
			(j + 27)->setTrack2(t + 27);
			(j + 27)->setNode0(j + 26);
			(j + 27)->setNode1(j + 28);
			(j + 27)->setNode2(j + 28);

			//j28 setup
			(j + 28)->setTrack0(t + 27);
			(j + 28)->setTrack1(t + 26);
			(j + 28)->setTrack2(t + 26);
			(j + 28)->setNode0(j + 27);
			(j + 28)->setNode1(j + 11);
			(j + 28)->setNode2(j + 11);

			//j29 setup
			(j + 29)->setTrack0(t + 10);
			(j + 29)->setTrack1(t + 18);
			(j + 29)->setTrack2(t + 18);
			(j + 29)->setNode0(j + 7);
			(j + 29)->setNode1(j + 8);
			(j + 29)->setNode2(j + 8);

			//j30 setup
			(j + 30)->setTrack0(t + 20);
			(j + 30)->setTrack1(t + 19);
			(j + 30)->setTrack2(t + 19);
			(j + 30)->setNode0(j + 3);
			(j + 30)->setNode1(j + 7);
			(j + 30)->setNode2(j + 7);

			//Setup tracks length
			for(int i = 0; i < 34; i++)
				(t+i)->setupTransform();

			//Train setup
			//Create a pointer to pointers to train objects
			//Two-level pointer structure can make the train management easier.
			//There are 'maxallowedTrain' train slots for holding trains.
			train = new Train*[maxAllowedTrain];
			int cabNum = rand()%2 + 2; //randomly set the number of cabs

			//Randomly set the left or right initial track by using a hidden joint which is not controlled by user.
			if(rand()%2 == 0)
				(j+15)->setTS(false);
			else
				(j+15)->setTS(true);

			//create a train at the first slot of train
			*train = RespawnTrain(*(train));

			//RoadBlock setup
			rb = new RoadBlock(t+33, 0.4f, 5.0f);		//use RoadBlock constructor to create roadblock.
			rb->SetupTransform();						//Calculate the absolute position
			(t+33)->setroadBlock(rb);					//Assign it to the track
			rb->setblockState(-1);						//rb is a turn-around roadblock, blockState is -1

			//3 Traffic lights setup
			light1 = new RoadBlock(t+6, 0.0f, 50.0f);
			light1->transform = light1->transform.Intersection((t+6)->getJoint0()->transform, (t+6)->getJoint1()->transform, (t+12)->getJoint0()->transform, (t+12)->getJoint1()->transform);
			(t+6)->setroadBlock(light1);
			light1->setblockState(1);

			light2 = new RoadBlock(t+12, 0.0f, 50.0f);
			light2->transform = light2->transform.Intersection((t+6)->getJoint0()->transform, (t+6)->getJoint1()->transform, (t+12)->getJoint0()->transform, (t+12)->getJoint1()->transform);
			(t+12)->setroadBlock(light2);
			light2->setblockState(0);

			light3 = new RoadBlock(t+5, 0.5f, 5.0f);
			light3->SetupTransform();
			(t+5)->setroadBlock(light3);
			light3->setblockState(0);

			//Create bonusTrack
			do 
			{
				bonusTrack = rand()%26 + 7;//Randomly generate a bonus item on one track, which worth 100 points.
			} while (bonusTrack == 12);//BonusTrack can not be 12
			bonusItem = new RoadBlock(t+bonusTrack, 0.5f, 10.0f);
			bonusItem->SetupTransform();
			(t+bonusTrack)->setroadBlock(bonusItem);
			bonusItem->setblockState(1);
			
		//Constructor end **********************************************************
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			//Release pointers
			delete[] j;
			delete[] t;
			delete[] train;
			delete rb;
			delete light1;
			delete light2;
			delete light3;
			delete log;
		}

		//******************** Private Fields ********************//
private:
		//GUI fields
		Graphics^ g;
		bool isMapped;

		//Static images
		Bitmap ^ trackMap;
		Bitmap ^ stationCover;
		Bitmap ^ cabsBitMap1;
		Bitmap ^ cabsBitMap2;
		Bitmap ^ cabsBitMap3;
		Bitmap ^ trafficLightMap;
		Bitmap ^ trafficLightRedMap;
		Bitmap ^ trafficLightGreenMap;

		//GameObjects
		Joint *j;
		Track *t;
		Train **train;
		RoadBlock *rb;
		RoadBlock *light1;
		RoadBlock *light2;
		RoadBlock *light3;
		int bonusTrack;
		RoadBlock *bonusItem;
		bool isGhostTrain;
		int ghostTrainColoredTime;

		//Game setting fields
		int difficulty;
		Log * log;
		String^UserID;
		int score;
		bool pause;
		int counttime, gametime;
		int totalTrainCount;
		int currentTrainCount;
		int maxAllowedTrain;
		float collisionDistance;
		float AvgSpeed;
		float RandomSpeedRange;
		int RespawnUnitTime;

private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Timer^  timer2;
private: System::Windows::Forms::Button^  button2;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Timer^  timer3;
private: System::Windows::Forms::Timer^  timer4;

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
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer4 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Transparent;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Cyan;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(1086, 270);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(148, 60);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Pause";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24));
			this->label1->Location = System::Drawing::Point(446, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(388, 55);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Time";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button2->FlatAppearance->BorderSize = 2;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Cyan;
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(1086, 336);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(148, 60);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Restart";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Transparent;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::RoyalBlue;
			this->button3->FlatAppearance->BorderSize = 2;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Cyan;
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gray;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(1086, 402);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(148, 60);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Main Menu";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->label2->Location = System::Drawing::Point(27, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 33);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Welcome!";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->label3->Location = System::Drawing::Point(1080, 25);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 33);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Score";
			// 
			// timer3
			// 
			this->timer3->Interval = 5000;
			this->timer3->Tick += gcnew System::EventHandler(this, &Form1::timer3_Tick);
			// 
			// timer4
			// 
			this->timer4->Interval = 12000;
			this->timer4->Tick += gcnew System::EventHandler(this, &Form1::timer4_Tick);
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1274, 683);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"Form1";
			this->Text = L"Train Routing";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		/************************************************************************/
		/* Graphical part                                                       */
		/************************************************************************/

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 g = e->Graphics;												//Get Graphics from Form
				 g->Clear(Color::FromArgb(2,4,20));								//Clean the background to dark blue color
				 g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
				 Pen^ yellowPen = gcnew Pen(Color::Yellow,4);					//Define some Pen and PointF for painting
				 Pen^ grayPen = gcnew Pen(Color::FromArgb(255,110,110,110),4);	
				 Pen^ whitePen = gcnew Pen(Color::White,4);
				 PointF^ pt = gcnew PointF;
				 PointF^ pt2 = gcnew PointF;
				 PointF^ pt3 = gcnew PointF;
				 
				 if(!isMapped)						//If static components have not created, draw it on Bitmap
				 {
					DrawMap();
					DrawStationBitMap();
					DrawCabsBitMap();
					DrawTrafficLightBitMap();
					isMapped = true;				//Set flag to true
				 }
				 else
					 g->DrawImage(trackMap,0,0);	//if true, draw the bottom track layer first.

			//Drawing joint states
				for(int i = 4; i < 14; i++)//Controllable joints are j+4 to j+13
				{
					pt = PointF((j+i)->transform.getX(),(j+i)->transform.getY());
					if (!(j+i)->getTS())
					{
						pt2 = PointF(((j+i)->getNode1())->transform.getX(), ((j+i)->getNode1())->transform.getY());
						pt3 = PointF(((j+i)->getNode2())->transform.getX(), ((j+i)->getNode2())->transform.getY());
					}
					else
					{
						pt2 = PointF(((j+i)->getNode2())->transform.getX(), ((j+i)->getNode2())->transform.getY());
						pt3 = PointF(((j+i)->getNode1())->transform.getX(), ((j+i)->getNode1())->transform.getY());
					}
					//pt: the center point of the joint
					//pt2: the end point of the switch on the connected track
					//pt3: the end point of the switch on the disconnected track

					//Vector calculation to get a fix length track switch
					Transform normPos = Transform(pt2->X,pt2->Y,0);
					normPos.Move(-(j+i)->transform.getX(),-(j+i)->transform.getY());	//"Move" equals to Vector1 - Vector2
					normPos.Normalize();												//Normalize vector to length 1
					normPos.Scale(40.0f);												//Scale it to 40 in length
					normPos.Move((j+i)->transform.getX(),(j+i)->transform.getY());		//"Move" equals to Vector1 + Vector2
					pt2->X = normPos.getX();											//Set the result position to pt2
					pt2->Y = normPos.getY();

					normPos = Transform(pt3->X,pt3->Y,0);
					normPos.Move(-(j+i)->transform.getX(),-(j+i)->transform.getY());
					normPos.Normalize();
					normPos.Scale(40.0f);
					normPos.Move((j+i)->transform.getX(),(j+i)->transform.getY());
					pt3->X = normPos.getX();
					pt3->Y = normPos.getY();
					
					g->DrawLine(yellowPen,*pt,*pt2);			//Draw connected track in yellow
					g->DrawLine(grayPen,*pt,*pt3);				//Draw connected track in gray
				}

			//Drawing Cabs
				if(currentTrainCount!=0)							//Detect whether there is train on map or not.
				{													//If true, then draw trains, otherwise it will do nothing.
					for(int k = 0; k < currentTrainCount; k++)				//For each train in 'train' pointer
					{
						int currentCabsNumber;								
						if ( *(train+k) != nullptr)							//For safety issue, detect if it is a valid pointer 
							currentCabsNumber = (*(train + k))->getcabsNumber();
						else
							currentCabsNumber = 0;
						for (int i = 0; i < currentCabsNumber ; i++)		//For each cab in one train.
						{
							//Assign different color to train with different destination
							//Their desired destination can be retrieved by 'getdestination()', which is equals to one of the id of destination joints
							//Then draw the pre-rendered Bitmap on cabs location.
							if((*(train + k))->getdestination()==(j+1)->getjointID())
								g->DrawImage(cabsBitMap1, PointF(((*(train + k))->getcabs()+i)->transform.getX() - 20.0f,((*(train + k))->getcabs()+i)->transform.getY() - 20.0f));
							else if((*(train + k))->getdestination()==(j+2)->getjointID())
								g->DrawImage(cabsBitMap2, PointF(((*(train + k))->getcabs()+i)->transform.getX() - 20.0f,((*(train + k))->getcabs()+i)->transform.getY() - 20.0f));
							else if((*(train + k))->getdestination()==(j+3)->getjointID())
								g->DrawImage(cabsBitMap3, PointF(((*(train + k))->getcabs()+i)->transform.getX() - 20.0f,((*(train + k))->getcabs()+i)->transform.getY() - 20.0f));
							else
								DrawC(g, Color::White, gcnew PointF(((*(train + k))->getcabs()+i)->transform.getX(),((*(train + k))->getcabs()+i)->transform.getY()), 20.0f);
							/*This line is for Ghost train*/
						}
					}
				}
				
			//Drawing Stations layer
				//Draw pre-rendered Bitmap to cover on the train layer.
				g->DrawImage(stationCover,0,0);
				
			//Drawing RoadBlock layer
				Drawing::RectangleF roadBlockDraw;
				Drawing2D::Matrix ^ mx = gcnew Drawing2D::Matrix;
				//Rotation graphics to draw a Roadblock perpendicular to track
				mx->RotateAt(rb->getonTrack()->transform.getR(), PointF(rb->transform.getX(), rb->transform.getY()), Drawing2D::MatrixOrder::Append);
				g->Transform = mx;
				
				//Create some roadblock-like image.
				float rbRadius = rb->getradius();
				roadBlockDraw =Drawing::RectangleF(rb->transform.getX()- rbRadius, rb->transform.getY() - 3.5f * rbRadius, 2 * rbRadius, 7 * rbRadius);
				g->FillRectangle(Brushes::Yellow, roadBlockDraw);
				roadBlockDraw =Drawing::RectangleF(rb->transform.getX()- rbRadius, rb->transform.getY() - 2.5f * rbRadius, 2 * rbRadius, 5 * rbRadius);
				g->FillRectangle(Brushes::DimGray, roadBlockDraw);
				roadBlockDraw =Drawing::RectangleF(rb->transform.getX()- rbRadius, rb->transform.getY() - 1.5f * rbRadius, 2 * rbRadius, 3 * rbRadius);
				g->FillRectangle(Brushes::Yellow, roadBlockDraw);
				roadBlockDraw =Drawing::RectangleF(rb->transform.getX()- rbRadius, rb->transform.getY() - 0.5f * rbRadius, 2 * rbRadius, 1 * rbRadius);
				g->FillRectangle(Brushes::DimGray, roadBlockDraw);

				//Turn the graphics back to normal rotation
				mx->RotateAt(-rb->getonTrack()->transform.getR(), PointF(rb->transform.getX(), rb->transform.getY()), Drawing2D::MatrixOrder::Append);
				g->Transform = mx;

			//DrawTrafficLight layer
				//Draw pre-rendered trafficLight bitmap on the top.
				g->DrawImage(trafficLightMap,0,0);

			//DrawBonusItem
				RectangleF ^ BI = gcnew RectangleF(bonusItem->transform.getX() - 8.0f, bonusItem->transform.getY() - 8.0f, 16.0f, 16.0f);
				g->FillEllipse(Brushes::Gold, *BI);
		 }

			


private: System::Void DrawMap()
		 {
			 //Create a new bitmap to store the image
			 trackMap = gcnew Bitmap(1280,720);
			 //Draw on the bitmap
			 Graphics ^ gToPaint = Graphics::FromImage(trackMap);
			 
			 //Use an array of PointF to store the path point of a long track
			 array<PointF> ^ pts;
			 //Setup the track and draw it.
			 pts = gcnew array<PointF>{
				 PointF((j+0)->transform.getX(),(j+0)->transform.getY()),
					 PointF((j+15)->transform.getX(),(j+15)->transform.getY())
			 };
			 //Use DrawL function to create glowing effect.
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+15)->transform.getX(),(j+15)->transform.getY()),
					 PointF((j+16)->transform.getX(),(j+16)->transform.getY()),
					 PointF((j+18)->transform.getX(),(j+18)->transform.getY()),
					 PointF((j+13)->transform.getX(),(j+13)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+15)->transform.getX(),(j+15)->transform.getY()),
					 PointF((j+17)->transform.getX(),(j+17)->transform.getY()),
					 PointF((j+19)->transform.getX(),(j+19)->transform.getY()),
					 PointF((j+4)->transform.getX(),(j+4)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+13)->transform.getX(),(j+13)->transform.getY()),
					 PointF((j+12)->transform.getX(),(j+12)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+13)->transform.getX(),(j+13)->transform.getY()),
					 PointF((j+5)->transform.getX(),(j+5)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+4)->transform.getX(),(j+4)->transform.getY()),
					 PointF((j+6)->transform.getX(),(j+6)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+4)->transform.getX(),(j+4)->transform.getY()),
					 PointF((j+20)->transform.getX(),(j+20)->transform.getY()),
					 PointF((j+5)->transform.getX(), (j+5)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+12)->transform.getX(),(j+12)->transform.getY()),
					 PointF((j+9)->transform.getX(),(j+9)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+12)->transform.getX(),(j+12)->transform.getY()),
					 PointF((j+14)->transform.getX(),(j+14)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+5)->transform.getX(),(j+5)->transform.getY()),
					 PointF((j+7)->transform.getX(),(j+7)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+6)->transform.getX(),(j+6)->transform.getY()),
					 PointF((j+23)->transform.getX(),(j+23)->transform.getY()),
					 PointF((j+24)->transform.getX(),(j+24)->transform.getY()),
					 PointF((j+9)->transform.getX(),(j+9)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+6)->transform.getX(),(j+6)->transform.getY()),
					 PointF((j+21)->transform.getX(),(j+21)->transform.getY()),
					 PointF((j+22)->transform.getX(),(j+22)->transform.getY()),
					 PointF((j+8)->transform.getX(),(j+8)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+9)->transform.getX(),(j+9)->transform.getY()),
					 PointF((j+11)->transform.getX(),(j+11)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+7)->transform.getX(),(j+7)->transform.getY()),
					 PointF((j+29)->transform.getX(),(j+29)->transform.getY()),
					 PointF((j+8)->transform.getX(),(j+8)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+7)->transform.getX(),(j+7)->transform.getY()),
					 PointF((j+30)->transform.getX(),(j+30)->transform.getY()),
					 PointF((j+3)->transform.getX(),(j+3)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+8)->transform.getX(),(j+8)->transform.getY()),
					 PointF((j+25)->transform.getX(),(j+25)->transform.getY()),
					 PointF((j+10)->transform.getX(),(j+10)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+11)->transform.getX(),(j+11)->transform.getY()),
					 PointF((j+1)->transform.getX(),(j+1)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+10)->transform.getX(),(j+10)->transform.getY()),
					 PointF((j+2)->transform.getX(),(j+2)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);
			 pts = gcnew array<PointF>{
				 PointF((j+11)->transform.getX(),(j+11)->transform.getY()),
					 PointF((j+28)->transform.getX(),(j+28)->transform.getY()),
					 PointF((j+27)->transform.getX(),(j+27)->transform.getY()),
					 PointF((j+26)->transform.getX(),(j+26)->transform.getY()),
					 PointF((j+10)->transform.getX(),(j+10)->transform.getY())
			 };
			 DrawL(gToPaint, Color::White, Color::Cyan, pts);

			 //Drawing Joints
				//Color arrangement:
					//Red:Start; MediumPurple, DeepSkyBlue, Lime:Ends; Blue: Joints;
				//Use DrawC function to create glowing effect

			 //Start joint
			 DrawC(gToPaint, Color::Red, gcnew PointF((j+0)->transform.getX(),(j+0)->transform.getY()), 20.0f);
			 //End1 joint
			 DrawC(gToPaint, Color::MediumPurple, gcnew PointF((j+1)->transform.getX(),(j+1)->transform.getY()), 20.0f);
			 //End2 joint
			 DrawC(gToPaint, Color::DeepSkyBlue, gcnew PointF((j+2)->transform.getX(),(j+2)->transform.getY()), 20.0f);
			 //End3 joint
			 DrawC(gToPaint, Color::Lime, gcnew PointF((j+3)->transform.getX(),(j+3)->transform.getY()), 20.0f);
			 //Normal joints
			 for(int i = 4; i<15;i++)
				 DrawC(gToPaint, Color::Blue, gcnew PointF((j+i)->transform.getX(),(j+i)->transform.getY()), 20.0f);

			 //End of game map drawing
		 }
private: System::Void DrawL(Graphics ^ gToPaint, Color ^ LineColor, Color ^ GlowColor, array<PointF> ^ pts)
			{
				//This function is to create lines defined by 'pts' with 'LineColor' and 'GlowColor' on 'gToPaint'
				//General idea is that the glow around the lines are some color in low opacity
				//Repeatedly draw a wider and lower opacity line to create the effect of light attenuation.

				Drawing2D::GraphicsPath ^ path = gcnew Drawing2D::GraphicsPath();
				gToPaint->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias; // Make the graphic smoother
				//Draw glowing outside
				int alpha = 3;
				for (int path_width = 32; path_width >= 3; path_width--)
				{
					path->Reset();
					path->AddLines(pts);
					gToPaint->DrawPath(gcnew Pen(Color::FromArgb(alpha++, *GlowColor), (float)path_width), path);
					if(path_width>16)
						alpha--;
				}
				//Draw a highlighted center line.
				gToPaint->DrawPath(gcnew Pen(Color::FromArgb(255, *LineColor), 3), path);
			}

private: System::Void DrawC(Graphics ^ gToPaint, Color ^ CircleColor, PointF ^ pt, float radius)
		 {
			 //This function is to create circle defined by 'radius' with 'CircleColor' on 'gToPaint'
			 //General idea is that the glow around the circles are some color in low opacity
			 //Repeatedly draw a smaller and lower opacity circle to create the effect of light attenuation.

			 Drawing2D::GraphicsPath ^ path = gcnew Drawing2D::GraphicsPath();
			 float innerRadius = radius - 11; //Highlight radius
			 gToPaint->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;

			 //Draw glowing
			 int alpha = 1;
			 for (; radius >= 4; radius--)
			 {
				 RectangleF C = RectangleF(pt->X - radius, pt->Y - radius, 2 * radius, 2 * radius);
				 gToPaint->FillEllipse(gcnew SolidBrush(Color::FromArgb(alpha++, *CircleColor)), C);
			 }

			 //RGB to HLS color system convert, increase the brightness of center color
			 float Ch, Cl, Cs;
			 Ch = (float)CircleColor->GetHue();
			 Cl = (float)CircleColor->GetBrightness();
			 Cs = (float)CircleColor->GetSaturation();
			 Cl = (float)Math::Sqrt(Cl);
			 float* Crgb = HLStoRGB(Ch, Cl, Cs);

			 //Draw a highlighted center circle
			 RectangleF C = RectangleF(pt->X - innerRadius, pt->Y - innerRadius, 2 * innerRadius, 2 * innerRadius);
			 gToPaint->FillEllipse(gcnew SolidBrush(Color::FromArgb(200, (int)Crgb[0], (int)Crgb[1], (int)Crgb[2])), C);
		 }
private: System::Void DrawStationBitMap()
			{
				//Create a bitmap to store the stations image
				stationCover = gcnew Bitmap(1280,720);
				Graphics ^ gToPaint = Graphics::FromImage(stationCover);

				//Use path to create station shape
				Drawing2D::GraphicsPath ^ StationPath = gcnew Drawing2D::GraphicsPath();
				float stationRadius = 25.0f;
				float stationOffset = 65.0f;
				Drawing::RectangleF ^ stationCurve;
				Color ^ LineColor;
				for(int i = 1; i < 4; i++)
				{
					//To make the station is parallel to the connected track
					float stationRotation = (j+i)->getTrack1()->transform.getR();
					int alpha = 1;
					stationCurve = gcnew Drawing::RectangleF((j+i)->transform.getX()-stationRadius,(j+i)->transform.getY()-stationRadius,2*stationRadius, 2*stationRadius);
					StationPath->Reset();	//Clean the previous path
					if(i == 1)			//Station 1 is at bottom, the rotation should be different
						stationRotation += 180.0f;
					StationPath->AddArc(*stationCurve, stationRotation - 120.0f, -120.0f);
					stationCurve->X += (float)Math::Cos(stationRotation / 180.0f * Math::PI) * stationOffset; 
					stationCurve->Y += (float)Math::Sin(stationRotation / 180.0f * Math::PI) * stationOffset; 
					StationPath->AddArc(*stationCurve, stationRotation + 120.0f, 120.0f);
					StationPath->CloseFigure();

					//Assign different color to different station
					if(i == 1)
						LineColor = Color::MediumPurple;
					if(i == 2)
						LineColor = Color::DeepSkyBlue;
					if(i == 3)
						LineColor = Color::Lime;

					//Draw glowing
					for (int path_width = 16; path_width >= 3; path_width--)
					{
						gToPaint->DrawPath(gcnew Pen(Color::FromArgb(alpha++, *LineColor), (float)path_width), StationPath);
					}
					//RGB to HLS Convert to increase the brightness
					float Ch, Cl, Cs;
					Ch = (float)LineColor->GetHue();
					Cl = (float)LineColor->GetBrightness();
					Cs = (float)LineColor->GetSaturation();
					Cl = (float)Math::Sqrt(Cl);
					float* Crgb = HLStoRGB(Ch, Cl, Cs);

					//Fill the path to fill a transparent color on station
					gToPaint->FillPath(gcnew SolidBrush(Color::FromArgb(100, (int)Crgb[0], (int)Crgb[1], (int)Crgb[2])), StationPath);
				}

				//Draw start station
				float xOffset = 10.0f;
				float yOffset = 18.0f;
				array<PointF> ^ pts = gcnew array<PointF>{
					PointF((j+16)->transform.getX() + 50.0f + xOffset,(j+16)->transform.getY() + yOffset),
						PointF((j+17)->transform.getX() - 50.0f + xOffset,(j+17)->transform.getY() + yOffset),
						PointF((j+19)->transform.getX() - 50.0f + xOffset,(j+19)->transform.getY() + yOffset),
						PointF((j+18)->transform.getX() + 50.0f + xOffset,(j+18)->transform.getY() + yOffset)
				};
				StationPath->Reset();
				StationPath->AddLines(pts);
				StationPath->CloseFigure();
				LineColor = Color::White;
				//Draw glowing
				int alpha = 1;
				for (int path_width = 24; path_width >= 3; path_width--)
				{
					gToPaint->DrawPath(gcnew Pen(Color::FromArgb(alpha++, *LineColor), (float)path_width), StationPath);
				}
				//Fill the path to fill a transparent color on station
				gToPaint->FillPath(gcnew SolidBrush(Color::FromArgb(240, 220, 220, 220)), StationPath);
			}
private: System::Void DrawCabsBitMap()
		 {
			 /*
				Because the glowing effect requires repeating drawing every frame of the game. To reduce the
			 redundant drawing code, the program will create the bitmap at first and then directly use the 
			 rendered bitmap to reduce repeated CPU calculation.
			 */

			 //Create the bitmap to store the cabs image, which is a basic element of train
			 cabsBitMap1 = gcnew Bitmap(40,40);
			 cabsBitMap2 = gcnew Bitmap(40,40);
			 cabsBitMap3 = gcnew Bitmap(40,40);
			 Graphics ^ gToPaint = Graphics::FromImage(cabsBitMap1);

			 //Draw glowing circle to represent cabs, different destination will be assign with different color
			 DrawC(gToPaint, Color::MediumPurple, gcnew PointF(20.0f, 20.0f), 20.0f);
			 gToPaint = Graphics::FromImage(cabsBitMap2);
			 DrawC(gToPaint, Color::DeepSkyBlue, gcnew PointF(20.0f, 20.0f), 20.0f);
			 gToPaint = Graphics::FromImage(cabsBitMap3);
			 DrawC(gToPaint, Color::Lime, gcnew PointF(20.0f, 20.0f), 20.0f);
		 }
private: System::Void DrawTrafficLightBitMap()
		{
			//Create red light and green light element first and then create the whole traffic light image to allocate light precisely.
			float radius = 16;
			trafficLightRedMap = gcnew Bitmap((int)radius * 2, (int)radius * 2);
			trafficLightGreenMap = gcnew Bitmap((int)radius * 2, (int)radius * 2);
			trafficLightMap = gcnew Bitmap(1280,720);

			//Draw red light and green light elements
			Graphics ^ gToPaint = Graphics::FromImage(trafficLightRedMap);
			DrawC(gToPaint, Color::Red, gcnew PointF(radius, radius), radius);
			gToPaint = Graphics::FromImage(trafficLightGreenMap);
			DrawC(gToPaint, Color::Green, gcnew PointF(radius, radius), radius);

			gToPaint = Graphics::FromImage(trafficLightMap);
			//Vector calculation to draw the light 50 pixel away from the intersection, and slightly away from the track
			Transform lightTransform1, lightTransform2, lightTransform3, lightTransform4;
			lightTransform1 = light1->getonTrack()->getJoint0()->transform;
			lightTransform1.Move(-light1->transform.getX(), -light1->transform.getY());
			lightTransform1.Normalize();
			lightTransform1.Scale(50.0f);
			lightTransform1.Move(5.0f, -8.0f);
			lightTransform2 = lightTransform1;
			lightTransform2.Scale(-1);	//Another traffic light is the same but in another direction, just scale it to -1.
			lightTransform1.Move(light1->transform.getX(), light1->transform.getY());	//Add the offset to the intersection position
			lightTransform2.Move(light1->transform.getX(), light1->transform.getY());

			lightTransform3 = light2->getonTrack()->getJoint0()->transform;
			lightTransform3.Move(-light2->transform.getX(), -light2->transform.getY());
			lightTransform3.Normalize();
			lightTransform3.Scale(50.0f);
			lightTransform3.Move(-5.0f, -8.0f);
			lightTransform4 = lightTransform3;
			lightTransform4.Scale(-1);
			lightTransform3.Move(light2->transform.getX(), light2->transform.getY());
			lightTransform4.Move(light2->transform.getX(), light2->transform.getY());

			//Draw different color according to the state of traffic light
			if(light1->getblockState() == 0)
			{
				gToPaint->DrawImage(trafficLightRedMap, lightTransform1.getX() - radius, lightTransform1.getY() - radius);
				gToPaint->DrawImage(trafficLightRedMap, lightTransform2.getX() - radius, lightTransform2.getY() - radius);
				gToPaint->DrawImage(trafficLightGreenMap, lightTransform3.getX() - radius, lightTransform3.getY() - radius);
				gToPaint->DrawImage(trafficLightGreenMap, lightTransform4.getX() - radius, lightTransform4.getY() - radius);
			}
			else
			{
				gToPaint->DrawImage(trafficLightGreenMap, lightTransform1.getX() - radius, lightTransform1.getY() - radius);
				gToPaint->DrawImage(trafficLightGreenMap, lightTransform2.getX() - radius, lightTransform2.getY() - radius);
				gToPaint->DrawImage(trafficLightRedMap, lightTransform3.getX() - radius, lightTransform3.getY() - radius);
				gToPaint->DrawImage(trafficLightRedMap, lightTransform4.getX() - radius, lightTransform4.getY() - radius);
			}
			if(light3->getblockState() == 0)
				gToPaint->DrawImage(trafficLightRedMap, light3->transform.getX() - radius + 8.0f, light3->transform.getY() - radius - 6.0f);
			else
				gToPaint->DrawImage(trafficLightGreenMap, light3->transform.getX() - radius + 8.0f, light3->transform.getY() - radius - 6.0f);
		}

		 //Following are RGB to HLS convert, just a tool.
private: float RGB(float q1, float q2, float  hue) {
				if (hue > 360) hue = hue - 360;
				if (hue < 0) hue = hue + 360;
				if (hue < 60) return (q1 + (q2 - q1) * hue / 60);
				else if (hue<180) return(q2);
				else if (hue<240) return(q1 + (q2 - q1) * (240 - hue) / 60);
				else return q1;
			}
private: float* RGBtoHLS(float R, float G, float B) {
				R /= 255;
				G /= 255;
				B /= 255;
				float max, min, diff, r_dist, g_dist, b_dist;
				float* hls = new float[3];

				max = Math::Max(Math::Max(R, G), B);
				min = Math::Min(Math::Min(R, G), B);
				diff = max - min;
				hls[1] = (max + min) / 2;
				if (diff == 0) {
					hls[0] = 0;
					hls[2] = 0;
				}
				else {
					if (hls[1]<0.5) { hls[2] = diff / (max + min); }
					else hls[2] = diff / (2 - max - min);
					r_dist = (max - R) / diff;
					g_dist = (max - G) / diff;
					b_dist = (max - B) / diff;
					if (R == max) { hls[0] = b_dist - g_dist; }
					else if (G == max) { hls[0] = 2 + r_dist - b_dist; }
					else if (B == max) { hls[0] = 4 + g_dist - r_dist; }
					hls[0] *= 60;
					if (hls[0] < 0) hls[0] += 360;
					if (hls[0] >= 360) hls[0] -= 360;
				}
				return hls;
			}

private: float* HLStoRGB(float H, float L, float S) {
				float p1, p2;
				float* rgb = new float[3];
				if (L <= 0.5) p2 = L * (1 + S);
				else { p2 = L + S - (L * S); }
				p1 = 2 * L - p2;
				if (S == 0) {
					rgb[0] = L;
					rgb[1] = L;
					rgb[2] = L;
				}
				else {
					rgb[0] = RGB(p1, p2, H + 120);
					rgb[1] = RGB(p1, p2, H);
					rgb[2] = RGB(p1, p2, H - 120);
				}
				rgb[0] *= 255;
				rgb[1] *= 255;
				rgb[2] *= 255;
				return rgb;
			}
		//End of RGB to HLS convert.


		/************************************************************************/
		/* Game Running Part                                                    */
		/************************************************************************/

private: System::Void RemoveTrain(Train* FinTrain) {
					//Find the position in pointer of the train to be removed
					int trainIndex = 0;
					for( ;trainIndex < maxAllowedTrain;trainIndex++)
					{
						if(*(train + trainIndex) == FinTrain)
							break;
					}

					//Delete the train and assign the nullptr to it to mark it as empty
					if(trainIndex != maxAllowedTrain)		//If trainIndex == maxAllowedTrain, that means the train is not found in train array
					{
						delete (*(train + trainIndex));
						*(train+trainIndex) = nullptr;		//This nullptr will be used when trying to access each of the train pointer in 'train' pointer
						currentTrainCount--;				//Reduce the train count by 1
					}

					//Move the remaining train pointers up to fill the empty slot, which is better for the "For loop" operation in other place
					for(int i = trainIndex;i < maxAllowedTrain - 1 ;i++)
					{
						*(train + i) = *(train + i + 1);
					}
					*(train + maxAllowedTrain - 1) = nullptr;
				}
private: Train* RespawnTrain(Train* newTrain) {
					 //Randomly set the number of cabs in train
				     int Cabs = rand()%2 + 2;
					 //Create a new train object pointer and set its position to the start track
					 newTrain = new Train(Cabs, t->transform);
					 totalTrainCount++;				//Increase the total train count by 1
					 currentTrainCount++;			//Increase the current train count by 1

					 //Setup each cabs to place it one by one with certain interval.
					 for (int i = 0; i < Cabs; i++)
					 {
						 (newTrain->getcabs() + i)->setonTrack(t);				//Set it on the start track
						 (newTrain->getcabs() + i)->setlastJoint(j);			//Set its initial direction
						 (newTrain->getcabs() + i)->setcabLength(30.0f);		//Set the train length

						 //Vector calculation to place it one by one with certain interval
						 Transform shiftPosition = (newTrain->getcabs() + i - 1)->transform;
						 shiftPosition.SetXY((j+0)->transform.getX()-shiftPosition.getX(),(j+0)->transform.getY()-shiftPosition.getY());
						 shiftPosition = shiftPosition.Normalize();
						 shiftPosition.Scale(newTrain->getcabs()->getcabLength() * i);
						 (newTrain->getcabs() + i)->transform.Move(shiftPosition);
					 }

					 //Randomly set the destination and store the destination joint id to train
					 int des = rand()%3;
					 switch(des)
					 {
					 case 0:
						 newTrain->setdestination((j+1)->getjointID());
						 break;
					 case 1:
						 newTrain->setdestination((j+2)->getjointID());
						 break;
					 case 2: 
						 if(!isGhostTrain)
						 {
							 int ghost = rand()%3;//Reduce the possibility of ghost train
							 if(ghost == 0)
							 {
								newTrain->setdestination(14);
								timer4->Interval = ghostTrainColoredTime;	//Set the time before displaying the color
								timer4->Enabled = true;	//Enable timer to show the color
								isGhostTrain = true;	//Ghost train will only generate once
							 }
							 else
								 newTrain->setdestination((j+3)->getjointID());
						 }
						 else
							newTrain->setdestination((j+3)->getjointID());
						 break;
					 default:
						 break;;
					 }

					 //Randomly set the speed of the train. The range of speed is determined by game difficulty setting
					 int randBase = rand()%21 - 10;	//21 levels of random speed
					 newTrain->setSpeed(AvgSpeed + (float)randBase * RandomSpeedRange / 10.0f);

					 //Return the pointer to the new train
					 return newTrain;
				 }
private: bool CollisionDetect()
			 {
				 //This function will calculate the distance between every cabs and detect whether they have collision or not.

				 if(currentTrainCount!=0) //To reduce the CPU workload, if there is not any train, it will skip calculation.
				 {
					 for(int k = 0; k < currentTrainCount; k++)						//For each existing train
					 {
						 if ( *(train + k) != nullptr)										//Detect whether it is valid
						 {
							 int currentCabsNumber = (*(train + k))->getcabsNumber();			//Get the number of cabs


							 //Because the train may run inversely we need to calculate two distance
							 float d1, d2;
							 //Bonus Item
							 //d1: The distance between the head and Bonus Item
							 d1 = ((*(train + k))->getcabs())->transform.DistanceTo(bonusItem->transform);
							 //d2: The distance between the tail and Bonus Item
							 d2 = ((*(train + k))->getcabs() + currentCabsNumber - 1)->transform.DistanceTo(bonusItem->transform);

							 //If distance smaller than 'collisionDistance' it will add scores
							 if(d1 < collisionDistance || d2 < collisionDistance)					
							 {
								 score += 100;
								 (t+bonusTrack)->setroadBlock(nullptr);
								 (t+bonusTrack)->sethasRb(false);
								 delete bonusItem;
								 do 
								 {
									 bonusTrack = rand()%26 + 7;
								 } while (bonusTrack == 12);//BonusTrack can not be 12
								 bonusItem = new RoadBlock(t + bonusTrack, 0.5f, 10.0f);
								 bonusItem->SetupTransform();
								 (t+bonusTrack)->setroadBlock(bonusItem);
								 bonusItem->setblockState(1);
							 }


							 //To reduce the calculation, we only calculate the distance from a front train to a behind train
							 //The 'front' and 'behind' is according to the order in 'train' pointer,

							 for(int j = k + 1; j < currentTrainCount; j++)					//For each following train
							 {
								 int anotherCabsNumber;
								 if ( *(train+j) != nullptr)										//Detect whether it is valid
									 anotherCabsNumber = (*(train + j))->getcabsNumber();			//Get the number of cabs
								 else
									 anotherCabsNumber = 0;
								 for (int i = 0; i < anotherCabsNumber ; i++)						//For each cab in other trains
								 {
									//Use 'DistanceTo()' function provided by our Transform class
									//To detect whether there is a collision or not
									
									//d1: The distance between the head of base train and another calculating cab
									d1 = ((*(train + k))->getcabs())->transform.DistanceTo(((*(train + j))->getcabs()+i)->transform);
									//d2: The distance between the tail of base train and another calculating cab
									d2 = ((*(train + k))->getcabs() + currentCabsNumber - 1)->transform.DistanceTo(((*(train + j))->getcabs()+i)->transform);

									//If distance smaller than 'collisionDistance' it will return true to tell the caller there is a collision
									if(d1 < collisionDistance || d2 < collisionDistance)					
									 	return true;
								 }
							 }


						 }
					 }
				 }
				 return false;
			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 /*
				This timer is used to drive the train. For every tick, it will call 
			 the 'Move()' function of each train. The 'Move()' function of Train
			 object will retrieve the environment information, such as roadblock and
			 traffic light. Then it will call 'Move()' function of Cabs object. The 
			 'Move()' function will do the physical movement and return the state of
			 moving, if it encounter disconnected joint switch or End joint, it will
			 return the id of last passing joint. 'trainState' will receive it and
			 be used for following judgment.
			 */
			 for(int i = 0; i < currentTrainCount; i++)
			 {
				 int trainState = -1;						//Default normal state is -1
				 if(*(train+i) != nullptr)					//Detect if it is valid
					trainState = (*(train + i))->Move(0.1f);//Move the train
				 if(trainState != -1)						//Train arrives at some special position
				 {
					 if(trainState!=(*(train + i))->getdestination())	//If the train does not arrive at its desired destination
					 {
						 Pause();							//Pause the game immediately

						 if(trainState!=(j+1)->getjointID() && trainState!=(j+2)->getjointID() && trainState!=(j+3)->getjointID())
						 {												//If the special position is not destination
																		//That means the train crashed at some disconnected joint switch
							 label1->Text = "Game Over!";
							 button1->Enabled = false;
							 score -= 200;								//Deduct 200 points
							 if (score<0)								//Process minus score
								 score = 0;
							 label3->Text="Score: " + score;			//Update score display
							 log->setScore(score);						//Log score to file
							 log->wirteHiScore();

							 //Show a MessageBox to player to tell them the result.
							 MessageBox::Show("Crash!! 200 points deducted.","Result",MessageBoxButtons::OK);
							 MessageBox::Show("Your score is " + score, "Result", MessageBoxButtons::OK);
						 }
						 else //The train arrives at wrong destination
						 {
							 MessageBox::Show("Wrong Destination!\n200 points deducted.\nGame is paused","Result",MessageBoxButtons::OK);
							 button1->Text = "Resume";
							 label1->Text = "Game paused!";
							 RemoveTrain(*(train + i));
							 score -= 200;
						 }
					 }
					 else	//The train arrives at correct destination
					 {
						 score+=100;					//Add score to user
						 RemoveTrain(*(train + i));		//Remove the finished train
					 }
				 }
			 }
			 label3->Text="Score: " + score;			//Update the score
			 if(CollisionDetect())						//If any collision is detected
			 {
				 Pause();										//Pause the game immediately
				 label1->Text = "Game Over!";					//Tell the player result
				 button1->Enabled = false;
				 score -= 500;									//Deduct 500 points for crash the train
				 if (score<0)
					 score = 0;									//Process minus score
				 label3->Text="Score: " + score;				//Update the score
				 log->setScore(score);							//Log score to file
				 log->wirteHiScore();
				 MessageBox::Show("Crash!!  500 points deducted.","Result",MessageBoxButtons::OK);
				 MessageBox::Show("Your score is " + score, "Result", MessageBoxButtons::OK);
			 }
			 //Physical calculation, including all the movements and collision detect, are done.
			 //Update the current state of game by 'Invalidate()' to call the paint function
			 this->Invalidate();
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //Timer2 is responsible for game timing, 
			 if (counttime < 0)		//Player will have some time before the start
			 {
				 label1->Text = "Start at: "+(-counttime);
			 }
			 if (counttime == 0)	//Start the game and change GUI state
			 {
				 timer1->Enabled = true;	//Move trains
				 timer3->Enabled = true;	//Generate trains
				 pause = false;
				 label1->Text = "Remaining: "+gametime+"s";
				 button1->Visible = true;	//Pause
				 button2->Visible = true;	//Restart
				 button3->Visible = true;	//Main menu
			 }
			 if (counttime > 0)		//Counting down the remaining time
			 {
				 label1->Text = "Remaining: "+(gametime - counttime)+"s";
			 }
			 if (counttime == gametime)		//Run out of time, change GUI state
			 {
				 Pause();
				 label1->Text = "Time up!";
				 button1->Enabled = false;
				 MessageBox::Show("Your score is " + score, "Result", MessageBoxButtons::OK);
				 if (score<0)
					 score = 0;				//Process minus score
				 log->setScore(score);		//Log score to file
				 log->wirteHiScore();
			 }
			 counttime++;					//Tick the count timer
		 }


private: System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //Generate new train at a random interval
			 int cabNum = rand()%2 + 2;
			 
			 //Randomly choose left or right entrance at rightmost bottom
			 if(rand()%2 == 0)
				 (j+15)->setTS(false);
			 else
				 (j+15)->setTS(true);

			 //If the number of train does not reaches maximum
			 if(currentTrainCount < maxAllowedTrain)
				*(train + currentTrainCount) = RespawnTrain(*(train + currentTrainCount));

			 //Randomly set the time that next train will be generated.
			 //This will be affected by current train cout, the more existing train, the slower the train will be generated.
			 timer3->Interval = rand()%4001 + RespawnUnitTime * currentTrainCount;
		 }
private: System::Void timer4_Tick(System::Object^  sender, System::EventArgs^  e) {
			if(currentTrainCount!=0) //To reduce the CPU workload, if there is not any train, it will skip calculation.
			{
				for(int k = 0; k < currentTrainCount; k++)						//For each existing train
				{
					if ( (*(train + k))->getdestination() == 14)									//Detect whether it is valid
					{
						int des = rand()%3;
						switch(des)
						{
						case 0:
							(*(train + k))->setdestination((j+1)->getjointID());
							break;
						case 1:
							(*(train + k))->setdestination((j+2)->getjointID());
							break;
						case 2:
							(*(train + k))->setdestination((j+3)->getjointID());
							break;
						default:
							break;;
						}

					}
				}
			}
			timer4->Enabled = false;
		}
 private: System::Void Pause()
		  {
			 timer1->Enabled = false;
			 timer2->Enabled = false;
			 timer3->Enabled = false;
			 pause = true;
		  }
 private: System::Void Resume()
		  {
			 timer1->Enabled = true;
			 timer2->Enabled = true;
			 timer3->Enabled = true;
			 pause = false;
		  }



private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //Retrieve player clicks
			 //Use the 'DistanceTo()' function to easily calculate distance between two things.
			 //In this case, passing the mouse position to 'DistanceTo()' to determine which object the player is clicking
			 if (!pause)	//Prevent player change switch when the game is paused
			 {
				 //Joints switch
				 for(int i = 4; i<=13; i++)
					 if ((j+i)->transform.DistanceTo((float)(e->X),(float)(e->Y))<=30)
						 (j+i)->inverseSwitch();

				 //Traffic light of cross
				 if (light1->transform.DistanceTo((float)(e->X),(float)(e->Y))<=60)
				 {
					 light1->setblockState(1 - light1->getblockState());
					 light2->setblockState(1 - light2->getblockState());
					 DrawTrafficLightBitMap();
				 }

				 //Traffic light of left entrance
				 if (light3->transform.DistanceTo((float)(e->X),(float)(e->Y))<=30)
				 {
					 light3->setblockState(1 - light3->getblockState());
					 DrawTrafficLightBitMap();
				 }
			 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Pause button
			 if (pause)
			 {
				 Resume();
				 button1->Text = "Pause";
				 label1->Text = "Remaining: "+(gametime - counttime+1);
			 }
			 else
			 {
				 Pause();
				 button1->Text = "Resume";
				 label1->Text = "Game paused!";
			 }

		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Restart button
			 if (!pause)					//Pause the game if the game is running
			 {
				 Pause();
				 button1->Text = "Resume";
				 label1->Text = "Game paused!";
			 }
			 if (MessageBox::Show("Are you sure to restart the game?", "Restart", MessageBoxButtons::OKCancel) == ::System::Windows::Forms::DialogResult::OK)
			 {
				 this->Hide();								//Remove previous game
				 Form1^Game1 = gcnew Form1(log,difficulty);	//Use current setting and file log information to create a new game
				 Game1 -> ShowDialog();						//Display it

			 }

		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Main menu
			 if (!pause)					//Pause the game if the game is running
			 {
				 Pause();
				 button1->Text = "Resume";
				 label1->Text = "Game paused!";
			 }
			 if (MessageBox::Show("Are you sure to quit the game?", "Main Menu", MessageBoxButtons::OKCancel) == ::System::Windows::Forms::DialogResult::OK)
			 {
				 this->Close();								//Close this game
			 }
		 }
protected: virtual System::Void OnClosing(System::ComponentModel::CancelEventArgs ^e) override
		 {
			 /*
			 When the window is closed by red cross, it will call this function to stop all the timer
			 Prevent some unexpected MessageBox after closing the game
			 Nothing related to game
			 */
			 timer1->Enabled = false;
			 timer2->Enabled = false;
			 timer3->Enabled = false;
		 }

};
}
