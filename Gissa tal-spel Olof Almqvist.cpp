#include "stdafx.h"
#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream> //för high score
#include <iomanip> //För setprecision på doubles

using namespace std::this_thread;
using namespace std;

void Menu();
void ClearScreen();
void RulePage();
void StatisticsPage();
void PlayGame();
void HighScore(); 

int Randomize50();
int GamePointCalc(int x);

bool DoubleorNothing(int x);
bool PlayerGuess(int x, int y);

string PlayerName;

int GameRounds = 0;
int LeastNumberGuesses = 10;
int LeastNumberGuessesPoints = 0;
double AveragePoints = 0;
double TotalGamePoints = 0;

int main()
{
	ClearScreen();
	cout << setw(55) << "THE AMAZING GUESS THE NUMBERS GAME" << endl;
	sleep_for(2s);
	cout << endl << setw(47) << "By Olof Almqvist" << endl;
	sleep_for(4s);
	
	ClearScreen();
	srand(time(0));
	cout << "-------------------------------------------------" << endl;
	cout << endl << "Welcome to our guess the number game!" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Please write your name: "; getline(cin, PlayerName);

	ClearScreen();
	cout << "Welcome to the game " << PlayerName << endl;
	cout << endl << "Initializing..." << endl;

	for (int i = 0; i < 4; i++)
	{
		sleep_for(0.2s);
		cout << i << "..." << endl;
	}

	Menu();


	return 0;
}

void ClearScreen()
{
	system("cls");
}

//Huvudmenyn
void Menu()
{
	ClearScreen();
	char MenuInput;

	cout << "------------------------" << endl;
	cout << "         Game Menu" << endl;
	cout << "------------------------" << endl;
	cout << endl << "Play the Game - (P)" << endl;
	cout << endl << "Statistics Page - (S)" << endl;
	cout << endl << "High Score - (H)" << endl;
	cout << endl << "Rules - (R)" << endl;
	cout << endl << "Exit the Program - (E)" << endl << endl;
	cout << "Choose where to go: "; cin >> MenuInput;

	if ((MenuInput == 'p') || (MenuInput == 'P')) {
		PlayGame();
	}

	else if ((MenuInput == 's') || (MenuInput == 'S')) {
		StatisticsPage();
	}

	else if ((MenuInput == 'h') || (MenuInput == 'H')) {
		HighScore();
	}

	else if ((MenuInput == 'r') || (MenuInput == 'R')) {
		RulePage();
	}

	else if ((MenuInput == 'e') || (MenuInput == 'E')) {
		ClearScreen();
		cout << endl << "You acquired a total of " << TotalGamePoints << " number of points." << endl;
		cout << "With an average score of " << AveragePoints << " points per game. ";
		cout << endl << endl << "Thank you for playing. :)" << endl << endl;
		system("pause");
		exit(0);
	}
	
	else {

		ClearScreen();
		cout << "You inserted an invalid option. Please try again." << endl;
		sleep_for(1s);
		Menu();
	}
}

//Funktion som innehåller hela spelsidan
void PlayGame()
{
	bool TrueOrFalse = false;
	int NumberPick = 0;
	int NumberGuesses = 0;
	int GamePoints = 0;
	int RandomNumber50 = Randomize50();
	int GuessedNumbers[11], DoubleorNothingArray[4];
	int i = 0;

	GameRounds++;

	for (int i = 0; i < 3; i++)
	{
		ClearScreen();
		cout << "----------------------------" << endl;
		cout << "         Play the Game" << endl;
		cout << "----------------------------" << endl;
		cout << "      Generating numbers" << endl;
		cout << "          [- * -] " << endl;
		sleep_for(0.1s);
		ClearScreen();
		cout << "----------------------------" << endl;
		cout << "         Play the Game" << endl;
		cout << "----------------------------" << endl;
		cout << "      Generating numbers" << endl;
		cout << "          [- ** -] " << endl;
		sleep_for(0.1s);
		ClearScreen();
		cout << "----------------------------" << endl;
		cout << "         Play the Game" << endl;
		cout << "----------------------------" << endl;
		cout << "      Generating numbers" << endl;
		cout << "          [- *** -] " << endl;
		sleep_for(0.1s);
		ClearScreen();
	}

	do
	{
		cout << "-----------------------------" << endl;
		cout << "         LETS START!" << endl;
		cout << "-----------------------------" << endl;
		cout << endl << "Make your first choice. Pick a number between 1-50." << endl << endl;
		
		//Här skrivs tidigare gjorda gissningar ut
		cout << "Previous guesses: " << endl;

		for (int i = 0; i < NumberGuesses; i++)
		{
			cout << "Guess number " << i + 1 << ": " << GuessedNumbers[i] << endl;
		}

		cout << endl << "I choose: ";
		bool valid = false;

		while (!valid) //Defensiv programmering för att rensa bort felaktiga inmatningar
		{
			valid = true;
			cin >> NumberPick;

			if (cin.fail() || NumberPick < 1 || NumberPick > 50)
			{
				cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //förhindrar att ett felmeddelande skrivs ut för varje felaktigt tecken
				cout << "Enter a correct value." << endl;
				valid = false;
			}

		} 

		GuessedNumbers[i] = NumberPick;
		i++;
		cout << "You guessed: " << NumberPick << endl;
		NumberGuesses++;
		
		//Funktion som jämför det gissade talet mot det framslumpade vinnartalet
		TrueOrFalse = PlayerGuess(NumberPick, RandomNumber50);

		//loopen fortsätter sålänge antalet gissningar är lägre än 10 samt rätt tal ej hittats
	} while ((TrueOrFalse == false) && (NumberGuesses <= 10));
	
	//Funktion för beräkning av antalet vunna poäng (baserat på antalet gissningar)
	GamePoints = GamePointCalc(NumberGuesses);

	cout << "------------------------" << endl;
	cout << "        AFTERMATH" << endl;
	cout << "------------------------" << endl << endl;
	cout << "You made " << NumberGuesses << " number of guesses to find the right number." << endl;
	cout << "For that performance, you recieve [ " << GamePoints << " ] number of points." << endl << endl;
	TotalGamePoints += GamePoints;
	
	//För statistiksidan. Förmedlar den rond som haft minst antal gissningsförsök.
	if (NumberGuesses < LeastNumberGuesses)
	{
		LeastNumberGuesses = NumberGuesses;
		LeastNumberGuessesPoints = GamePoints;
	}

	cout << "The numbers you guessed are: ";

	for (int i = 0; i < NumberGuesses; i++)
	{
		cout << GuessedNumbers[i] << ", ";
	}
	cout << endl << "______________________________________________________________________________" << endl << endl;

		bool DoN = DoubleorNothing(GamePoints);

	if (DoN == true) {
		if (NumberGuesses < 5) //Om spelaren gissar färre än 5 gånger fylls arrayen upp med fler randomiserade tal. 
		{
			do
			{
				GuessedNumbers[NumberGuesses] = rand() % 50 + 1;
				NumberGuesses++;

			} while (NumberGuesses < 5);
		}

		for (int i = 0; i < NumberGuesses; i++) //Kasta om innehållet i arrayen
		{
			int index = rand() % NumberGuesses;
			int temp = GuessedNumbers[i];
			GuessedNumbers[i] = GuessedNumbers[index];
			GuessedNumbers[index] = temp;
		}

		for (int i = 0; i < 5; i++) //kopiera över till en andra array
		{
				DoubleorNothingArray[i] = GuessedNumbers[i];
		}

		//Vinnartalet för kvitt eller dubbelt väljs.
		int WinningNumber = DoubleorNothingArray[rand() % 4];
	
		int DoubleorNothingPick;

		ClearScreen();
		cout << "------------------------" << endl;
		cout << "    DOUBLE OR NOTHING" << endl;
		cout << "------------------------" << endl << endl;
		cout << "The number has been drawn." << endl;
		cout << "Choose from: ";
		for (i = 0; i < 5; i++)
		{
			cout << DoubleorNothingArray[i];
			if (i < 4)
				cout << ", ";
			else
				cout << ".";
		}
			
		cout << endl << endl << "Pick your number: "; cin >> DoubleorNothingPick;

		//Selektion som validerar om spelaren vann kvitt eller dubbelt eller ej
		if (DoubleorNothingPick == WinningNumber)
		{
			cout << endl << "You WON! CONGRATULATIONS! :-D" << endl << endl;
			TotalGamePoints += GamePoints;
			GamePoints = GamePoints*2;

			cout << endl << "You doubled your points from the guessing round from " << GamePoints / 2 << " to " << GamePoints << " number of points." << endl;
			cout << "Your total score is now: " << TotalGamePoints << "." << endl;
			system("pause");
			Menu();
		}

		else
		{
			TotalGamePoints -= GamePoints;
			cout << endl << "Sorry you lost. :-(" << endl << endl;
			cout << endl << "The winning number was: " << WinningNumber << ".";
			cout << endl << "You lost all your points, from " << GamePoints << " to 0 number of points." << endl << endl;
			cout << "Your total game score is now: " << TotalGamePoints << "." << endl << endl;
			system("pause");
			Menu();
		}
	}

	else {
		Menu();
	}

}

//Funktion som tar fram det framslumpade vinnartalet
int Randomize50()
{
	srand(time(NULL));
	int RandomNumber50 = rand() % 50 + 1;

	return RandomNumber50;
}

//Funktion som testar om spelaren kan & vill spela kvitt eller dubbelt
bool DoubleorNothing(int x)
{
	char choice;

	if (x == 0) {
		return false;
	}
	
	else {
		cout << "Would you like a chance to double the points you earned?" << endl << endl;
		cout << "By choosing to play **|--Double or Nothing--|** you can do just that." << endl << endl;
		cout << "However, if you lose, you will lose all your points." << endl << endl;
		cout << "You will be presented with 5 of your previous tries and pick one." << endl;
		cout << "If you pick the right one, you win, otherwise you lose." << endl << endl;
		cout << "Type [Y] to play Double or Nothing." << endl << endl;
		cout << "Type [N] to go back to the menu." << endl << endl;
		cout << "My choice is: "; cin >> choice;
		
		if ((choice == 'Y') || choice == 'y')
			return true;

		else {
			return false;
		}
	}
		
}

//Beräkning av antalet vunna poäng samt vinst- eller förlusmeddelanden
int GamePointCalc(int x)
{
	if (x == 1) {
		for (int i = 0; i < 2; i++)
		{
			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "****-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "********-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "*************-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "************************-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "****************************************-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);

			cout << "-----------------------------------------------" << endl;
			cout << "                GREAT SUCCESS" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			cout << "   YOU WON THE MAXIMUM NUMBER OF POINTS!!!" << endl;
			cout << endl << "        d|^_^|b /" << endl;
			cout << endl << "************************************************************-->MONEY";
			sleep_for(0.5s);
			ClearScreen();
			sleep_for(0.1s);
		}
		ClearScreen();
		return 10;
	}

	//Om spelaren har mer än 1 men lika med eller mindre än 3 gissningar
	else if ((x > 1) && (x <= 3)) {
		for (int i = 0; i < 5; i++)
		{
			cout << "------------------------------" << endl;
			cout << "         GOOD JOB" << endl;
			cout << "------------------------------" << endl << endl;
			cout << "   YOU WON 5 POINTS!!!" << endl;
			cout << endl << "       d|o-o|b /" << endl;
			sleep_for(0.2s);
			ClearScreen();
			sleep_for(0.2s);
		}
		ClearScreen();
		return 5;
	}
		
	//Om spelaren gissar fler än 3 men lika med eller mindre än 10 gånger
	else if ((x > 3) && (x <= 10)) {
		
	cout << "--------------------------------" << endl;
	cout << "         YOU ARE OK" << endl;
	cout << "--------------------------------" << endl << endl;
	cout << "   YOU WON 1 POINT. KEEP TRYING." << endl;
	cout << endl << "       d|O_O|b /" << endl << endl;
	system("pause");
	ClearScreen();

	return 1;
	}
		
	else {
		cout << "------------------------" << endl;
		cout << "         FAILURE" << endl;
		cout << "------------------------" << endl << endl;
		cout << "You made too many attempts." << endl;
		cout << "More than 10 attempts rewards 0 points and no more tries." << endl << endl;
		system("pause");
		Menu();
	}
}

//Sidan som visar statistik under spelets gång
void StatisticsPage()
{
	ClearScreen();
cout << "--------------------------------------" << endl;
cout << "         Statistics Page" << endl;
cout << "--------------------------------------" << endl;

cout << endl << "On this page, you can track your game performance throughout a session." << endl;

cout << endl << "Game name: " << PlayerName << endl;

cout << endl << "Thus far, you have recieved: " << TotalGamePoints << " number of points." << endl;
cout << "From " << GameRounds << " number of games." << endl << endl;

//Beräkning görs enbart om minst ett spel har spelats.
if (GameRounds > 0)
{
	AveragePoints = TotalGamePoints / GameRounds;
	cout << "That is an average of: " << setprecision(2) << AveragePoints << " points per game round." << endl;

	cout << endl << "Your best round was " << LeastNumberGuesses << " number of guesses" << endl;
	cout << "Which awarded " << LeastNumberGuessesPoints << " number of points." << endl << endl;
}

system("pause");

Menu();
}

//Regelsidan
void RulePage()
{
	ClearScreen();
	cout << "------------------------" << endl;
	cout << "         Rules Page" << endl;
	cout << "------------------------" << endl;

	cout << endl << "Welcome to the rule page!" << endl;
	cout << endl << "Here, you will find everything you need to know to play the game efficiently." << endl;
	sleep_for(2s);

	cout << endl << "*** RULE 1 ***" << endl;
	cout << endl << "You must use this software in a gentlemanly manner." << endl;
	sleep_for(2s);

	cout << endl << "*** RULE 2 ***" << endl;
	cout << endl << "You play this game by finding a randomized number between 1-50." << endl;
	cout << "You have a maximum of 10 attempts. If you exceed this amount of tries," << endl << "you will recieve 0 points." << endl;
	sleep_for(2s);

	cout << endl << "*** RULE 3 ***" << endl;
	cout << endl << "Finding the correct number with one guess awards 10 points." << endl;
	cout << "Finding the correct number with up to three guesses awards 5 points." << endl;
	cout << "Finding the correct number with more than three but less than eleven guesses," << endl << "awards 1 point." << endl;
	sleep_for(3s);

	cout << endl << "*** RULE 4 ***" << endl;
	cout << endl << "If you win one or more points while playing the game," << endl << "you are eligible to continue playing Double or Nothing." << endl << endl;
	sleep_for(2s);

	cout << endl << "*** RULE 5 ***" << endl;
	cout << endl << "Choosing to play Double or Nothing means you will get to" << endl << "choose from five numbers." << endl << endl;
	cout << "One of them is going to be the winning number." << endl;
	cout << "If you pick the correct choice, your points will double. " << endl;
	cout << "If you pick the wrong number, you will loose all points." << endl << endl;
	sleep_for(2s);

	cout << endl << "*** RULE 6 ***" << endl;
	cout << endl << "The High Score list measures average points and not absolute points." << endl << endl;

	//Regelmenyn
	cout << "------------------------------------------" << endl;
	cout << "         How would you like to continue?" << endl;
	cout << "------------------------------------------" << endl;

	cout << endl << "Read the Rules again - (R)" << endl;
	cout << endl << "Play the game - (P)" << endl;
	cout << endl << "Go back to Menu - (M)" << endl;
	char RuleMenu;
	cout << endl << "My choice is: "; cin >> RuleMenu;

	if (RuleMenu == 'R' || RuleMenu == 'r')
	{
		RulePage();
	}

	else if (RuleMenu == 'P' || RuleMenu == 'p')
	{
		PlayGame();
	}

	else
	{
		Menu();
	}
}

//High Score-listan
void HighScore()
{
	ClearScreen();

	if (GameRounds > 0 && TotalGamePoints > 0)
	{
		AveragePoints = TotalGamePoints / GameRounds;
	}
	
	//Spelarnas info lagras i form av namn och genomsnittligt spelpoäng
	struct spelare
	{
		string Name;
		double AverageGamePoints;
	};

	//Förinlagda datorspelare Peter Pan och Kapten Krok samt den aktuella spelaren
	spelare HighScore[3] = {{"Peter Pan", 5}, {"Kapten Krok", 2}, {PlayerName, AveragePoints}};

	for (int i = 0; i < 2; i++) //Här är bubbelsorteringen
	{
		for (int j = i + 1; j < 3; j++)
		{
			int TempNum; //Håller AverageGamePoint temporärt
			string TempName; //Håller namnet temporärt

			if (HighScore[i].AverageGamePoints < HighScore[j].AverageGamePoints) //Om numret i är mindre än j gör...
			{
				//Hur sorteringen funkar
				TempNum = HighScore[i].AverageGamePoints;
				TempName = HighScore[i].Name;
				HighScore[i].AverageGamePoints = HighScore[j].AverageGamePoints;
				HighScore[i].Name = HighScore[j].Name;
				HighScore[j].AverageGamePoints = TempNum;
				HighScore[j].Name = TempName;
			}
		}
	}

	ifstream my_file("HighScore.txt"); //Kollar om HighScore.txt redan har sparats på disken.
	if (!my_file)
	{
		cout << "You have not played any previous games yet." << endl;
		cout << "You can therefor not compare your current progress to your previous." << endl << endl; 
		

		//Här skrivs High Score-listan ner i en textfil som sparas på spelarens hårddisk
		ofstream writer("HighScore.txt");
		writer << "*** -- HIGH SCORE LIST --- ***" << endl << endl;
		for (int i = 0; i < 3; i++)
		{
			writer << i + 1 << ". ";
			writer << HighScore[i].Name << " with ";
			writer << HighScore[i].AverageGamePoints << " number of points." << endl << endl;

		} 
		writer.close();
	}

	
	//Selektion som läser in high score-listan om textfilen existerar sedan tidigare & datorspelarna har högre poäng än användaren
	else if (my_file && HighScore[2].AverageGamePoints > AveragePoints)
	{
		std::string line_;
		ifstream file_("HighScore.txt");
		if (file_.is_open())
		{
			while (getline(file_, line_))
			{
				cout << line_ << '\n';
			}
			file_.close();
		}
		std::cin.get();
	}

	//Om spelarens AveragePoints är högre än den lägsta datorspelaren skrivs en ny high score lista ut och läses följdaktligen in
	else if (HighScore[2].AverageGamePoints < AveragePoints)
	{
		ofstream writer("HighScore.txt");
		writer << "*** -- HIGH SCORE LIST --- ***" << endl << endl;
		for (int i = 0; i < 3; i++)
		{
			writer << i + 1 << ". ";
			writer << HighScore[i].Name << " with ";
			writer << HighScore[i].AverageGamePoints << " number of points." << endl << endl;

		}
		writer.close();

		std::string line_;
		ifstream file_("HighScore.txt");
		if (file_.is_open())
		{
			while (getline(file_, line_))
			{
				cout << line_ << '\n';
			}
			file_.close();
		}
		std::cin.get();

	}

	system("pause");

	Menu(); 
}

//Funktion som testar spelarens gissning i det första gissningsspelet och jämför den mot det framslumpade vinnartalet
bool PlayerGuess(int x, int y)
{
	if (x > y) {
		cout << "The number you guessed is too high. Try again.";
		sleep_for(2s);
		ClearScreen();
		return false;
	}

	else if (x < y) {
		cout << "The number you guessed is too low. Try again.";
		sleep_for(2s);
		ClearScreen();
		return false;
	}

	else {
		cout << "You guessed the correct number!";
		sleep_for(2s);
		ClearScreen();
		return true;
	}
}