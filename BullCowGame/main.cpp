#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();

// entry point
int main() 
{
	bool bPlayAgain = false;

	PrintIntro();
	
	do
	{
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	
	return 0;
}

// introduce the game
void PrintIntro() 
{
	constexpr int WORD_LENGTH = 7;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

void PlayGame()
{
	// loop for the number of turns asking for guesses
	constexpr int NUM_TURNS = 5;
	for (int i = 0; i < NUM_TURNS; i++)
	{
		string Guess = GetGuess();
		cout << "Your guess: " << Guess << endl;
		cout << endl;
	}
}

// get a guess from the player
string GetGuess() 
{
	string Guess = "";
	cout << "Enter your guess: ";
	getline(cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again? ";
	string Response = "";
	getline(cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}
