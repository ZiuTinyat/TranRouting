#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Log
{
	/*
		This class is used to establish a file for user accounts, user identification, scores storing.
		A file named "UserInfo.txt" stores username, password and highest score of a user. 
	If the input username is not find in the existing file, a new account is established.
	If the input username exists and the password is correct,the highest score will be updated.
	Each account contains 4 lines: 
		a line with "p" standing for a existing account, a username line, a password line and a score line
	like this: 
				* * * * * * * * * * * * *
				*	p					*
				*	player1				*
				*	player1password		*
				*	00200				*
				*	p					*
				*	player2				*
				*	player2password		*
				*	00000				*
				* * * * * * * * * * * * *
	*/
public:
	//Constructor
	Log();

	//Destructor
	~Log();

	/*
	When user finishes the input, exam the user information:
	return -1 if not existing
	return 0 if existing but password is wrong
	return 1 if existing and password is correct, then put the cursor position in frount of the score.
	*/
	int existsUser();

	//When the input username not exists, establish a new account to the file.
	void newUser();

	//When the user finish a game, write the higher score.
	void wirteHiScore();

	//Return the score stored in the file.
	int readHiScore();

	//set;get;]
	void setPos(long);
	long getPos();

	void setFilename(char*);
	char* getFilename();

	void setUsername(char*);
	char* getUsername();

	void setPassword(char*);
	char* getPassword();

	void setScore(int);//This function also write scores into "score5" as char[].
	int getScore();

private:
	long pos;//Stores the cursor position at the beginning of the score.
	char *filename;//Stores the current filename.//*****Usually not changed*****//
	char *username;//Stores the input username.
	char *password;//Stores the input password.
	int score;//Stores the game score as int.
	char score5[6];//Stores the game score as char[] of 5 charactors.
};