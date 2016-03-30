#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Log
{
	/*
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
				*	200					*
				*	p					*
				*	player2				*
				*	player2password		*
				*	0					*
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
	return 1 if existing and password is correct
	*/
	int existsUser();

	//When the input username not exists, establish a new account to the file.
	void newUser();

	//When the user login successfully, change the score after game.
	void wirteHiScore();

	//To show the high score stored in the file
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

	void setScore(int);//This function changes score5 directly.
	int getScore();

private:
	long pos;//Stores the cursor position of the score to be changed.
	char *filename;//Stores the current filename
	char *username;//Stores the input username
	char *password;//Stores the input password
	int score;//Stores the game score as int
	char score5[6];//Stores the game score as string
};