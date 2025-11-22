#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice{ Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner{ Player1  = 1 , Computer = 2 , Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinsTimes = 0;
	short ComputerWinsTimes = 0;
	short DrawsTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};  

void PrintGameInstructions()
{
	cout << "=====================================================\n";
	cout << "          WELCOME TO ROCK - PAPER - SCISSORS         \n";
	cout << "=====================================================\n";
	cout << "Rules of the Game:\n";
	cout << "1. You will play against the computer.\n";
	cout << "2. Choices are:\n";
	cout << "   [1] Rock\n";
	cout << "   [2] Paper\n";
	cout << "   [3] Scissors\n";
	cout << "3. Rock beats Scissors, Paper beats Rock, Scissors beat Paper.\n";
	cout << "4. You can choose to play between 1 and 10 rounds.\n";
	cout << "5. The winner will be decided based on who wins more rounds.\n";
	cout << "=====================================================\n\n";
}

int RandomNumber(int From, int To)
{
	int Random = rand() % (To - From + 1) + From;
	return Random;
}
int ReadHowManyRounds()
{
	int GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ?" << endl;
		cin >> GameRounds;
	
	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "Your Choice : [1] Rock , [2] Paper , [3] Scissors ?\t";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	int Choice = RandomNumber(1, 3);
	return (enGameChoice)Choice;
}
string ChoiceName(enGameChoice Choice)
{
	string arrChoiceNames[] = { "Rock" , "Paper" , "Scissors" };
	return arrChoiceNames[Choice - 1];
}


void SetWinnerScreenColor(enWinner GameWinner)
{
	switch (GameWinner)
	{
	case enWinner::Player1:
		system("Color 2F"); // Green
		break;

	case enWinner::Computer:
		system("Color 4F"); // Red
		cout << "\a";
		break;

	default :
		system("Color 6F"); //Yellow
		break;
	}

}


enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Rock:
		if(RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;

	case enGameChoice::Paper:
		if(RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;

	case enGameChoice::Scissors:
		if(RoundInfo.ComputerChoice == enGameChoice::Rock)
			return enWinner::Computer;
		break;
	}

		return enWinner::Player1;

}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n------------ Round [" << RoundInfo.RoundNumber << "] ------------\n" << endl;
	cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;	
	cout << "Round Winner : " << RoundInfo.WinnerName << endl;
	cout << "-------------------------------------\n" << endl;

}

enWinner WhoWonTheGame(short Player1WinsTimes ,short ComputerWinsTimes)
{
	if(Player1WinsTimes > ComputerWinsTimes)
		return enWinner::Player1;
	else if(ComputerWinsTimes > Player1WinsTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
string WinnerName(enWinner Winner)
{
	string arrWinnerNames[] = { "Player1" , "Computer" , "No Winner" };
	return arrWinnerNames[Winner - 1];
}
stGameResults FillGameResults(int GameRounds, int Player1WinsTimes, int ComputerWinsTimes, int DrawsTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinsTimes = Player1WinsTimes;
	GameResults.ComputerWinsTimes = ComputerWinsTimes;
	GameResults.DrawsTimes = DrawsTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinsTimes, ComputerWinsTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;

}
stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinsTimes = 0;
	short ComputerWinsTimes = 0;
	short DrawsTimes = 0;

	for(short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins :" << endl;
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinsTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinsTimes++;
		else
			DrawsTimes++;

		SetWinnerScreenColor(RoundInfo.Winner);
		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinsTimes, ComputerWinsTimes, DrawsTimes);
	
}


void ResetScreen()
{
	system("cls");
	system("Color 0F");
}
string Tabs(short NumberOfTabs)
{
	string Tabs = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		Tabs = Tabs + "\t";
		cout << Tabs;
	}

	return Tabs;
}

/*  better طريقة تانية

	string Tabs(short NumberOfTabs) 
	{
	  if (NumberOfTabs <= 0) return "";
	  return string(NumberOfTabs, '\t'); // يبقى عدد تابز مضبوط
	}
*/



void ShowGameOverScreen()
{
	cout << Tabs(3) << "---------------------------------------------------------" << endl;
	cout << Tabs(3) << "                 +++ G a m e   O v e r +++               " << endl;
	cout << Tabs(3) << "---------------------------------------------------------" << endl;
}
void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(3) << "------------------- Final Game Results ------------------" << endl;
	cout << Tabs(3) << "Game Rounds   : " << GameResults.GameRounds << endl;
	cout << Tabs(3) << "Player1 Wins  : " << GameResults.Player1WinsTimes << endl;
	cout << Tabs(3) << "Computer Wins : " << GameResults.ComputerWinsTimes << endl;
	cout << Tabs(3) << "Draws         : " << GameResults.DrawsTimes << endl;
	cout << Tabs(3) << "Game Winner   : " << GameResults.WinnerName << endl;
	cout << Tabs(3) << "---------------------------------------------------------" << endl;

	SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PrintGameInstructions();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "\nDo you want to play again ? (Y/N) ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}