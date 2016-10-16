/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal-friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void GetHiddenWord();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game which we re-use across plays
FBullCowGame BCGame; 

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
	
	return 0; // exit app
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	// get word based on player selection
	GetHiddenWord();

	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game is not won and are there still tries remaining
	while (!BCGame.HasWonGame() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	// print game summary
	PrintGameSummary();
	return;
}

// as the player to select a difficulty level and get the hidden word
void GetHiddenWord()
{
	int32 Length;
	FString derp;

	std::cout << "Select a word length to play [3-7]: ";
	std::getline(std::cin, derp);
	std::cout << std::endl;

	Length = std::stoi(derp);

	BCGame.SetHiddenWord(Length);
}

// loop conitunously until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// get guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// validate guess
		Status = BCGame.IsGuessValid(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Alpha_Char:
			std::cout << "Please enter only a-z.\n\n";
			break;
		case EGuessStatus::OK:
		default:
			// assume code is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.HasWonGame()) {
		std::cout << "You won!\n\n";
	}
	else
	{
		std::cout << "Bad luck!\n\n";
	}
	
}
