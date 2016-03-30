//Login.cpp
#include"Loginlib.h"

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
//Constructor
Log::Log()
{
	//Initialize the member variable
	pos = 0; 
	filename = "UserInfo.txt";//Usually not changed
	username = "player1";//Default username
	password = "player1password";//Default password
	setScore(0);//Initialize "score" and "score5"
}

//Destructor
Log::~Log()
{

}

	//When user finishes the input, exam the user information:
	/*
	return -1 if not existing
	return 0 if existing but password is wrong
	return 1 if existing and password is correct, then put the cursor position in frount of the score.
	*/

int Log::existsUser()
{
	//Initialize return value
	int exists = -1;
	char exam[10], un[20], pw[20], sc[6];

	ifstream fin(filename,ios::in);

	//Examine every user in the file and compare them with the inputs
	while (fin.getline(exam,10))
	{
		fin.getline(un,20);//read username
		fin.getline(pw,20);//read password
		pos = (long)fin.tellg();
		fin.getline(sc,6);//read score
		if (strcmp(un,username) == 0)//comparing
		{
			exists = 0;
			if (strcmp(pw,password) == 0)
				exists = 1;
			break;
		}
	}
	fin.close();
	return exists;
}

//When the input username not exists, establish a new account to the file.
void Log::newUser()
{
	ofstream fout(filename,ios::app);

	fout<<"p"<<endl;			//The first line is to detect if there is a user.

	fout<<username<<endl;		//The second line stores new Username

	fout<<password<<endl;		//The third line stores new Password

	pos = (long)fout.tellp();

	fout<<score5<<endl;			//The forth line stores new score, initially 00000
	fout.close();
}

//When the user finish a game, write the higher score.
void Log::wirteHiScore()
{
	char pscstr[6];		//previous score as string
	int psc;			//previous score

	//get the previous score from file.
	ifstream fin(filename);
	fin.seekg(pos);
	fin.getline(pscstr,6);
	psc = atoi(pscstr);
	fin.close();

	//Write the higher score into the file.
	if (score > psc)
	{
		ofstream fout(filename, ios::in);
		fout.seekp(pos);
		fout<<score5<<endl;
		fout.close();
	}
}

//Return the score stored in the file.
int Log::readHiScore()
{
	char pscstr[6];
	int psc;
	ifstream fin(filename);
	fin.seekg(pos);
	fin.getline(pscstr,6);
	psc = atoi(pscstr);
	fin.close();
	return psc;
}

//set;get;
void Log::setPos(long p)
{
	pos = p;
}
long Log::getPos()
{
	return pos;
}

void Log::setFilename(char*f)
{
	filename = f;
}
char* Log::getFilename()
{
	return filename;
}
void Log::setUsername(char*u)
{
	username = u;
}
char* Log::getUsername()
{
	return username;
}
void Log::setPassword(char*p)
{
	password = p;
}
char* Log::getPassword()
{
	return password;
}

//This function also write scores into "score5" as char[].
void Log::setScore(int s)
{
	score = s;

	/*
	The functions below is to write the score into "score5" as char[], which contains 5 charactors.
	If the number of score digits are not enough, there will be "0"s paded in front of the "score5".
	This design is to avoid faults when reading score from file. 
	*/
	char sctmp[6] = "", sc[10];
	int highestsc = 99999;//Scores over 99999 will be record as 99999
	itoa(score,sc,10);

	//Pad zeros in front of the char[] according to the number of digits
	if (score<100000)
	{
		if (score<10000)
		{
			sctmp[0] = '0';
			if (score<1000)
			{
				sctmp[1] = '0';
				if (score<100)
				{
					sctmp[2] = '0';
					if (score<10)
					{
						sctmp[3] = '0';
					}
				}
			}
		}
		strcat(sctmp, sc);
	}
	else
	{
		//Highest score is 99999
		itoa(highestsc,sctmp,10);
	}

	for (int i=0; i < 6; i++)
		score5[i] = sctmp[i];
}
int Log::getScore()
{
	return score;
}