#include "FBullCowGame.h"
#include <iostream>
#include <map>
#include <locale>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::HasWonGame() const { return bWonGame; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthMaxTries{{3,5}, {4,8}, {5,12}, {6,15}, {7,20}};
	return WordLengthMaxTries[MyHiddenWord.length()];
}

//FString FBullCowGame::GetHiddenWord() const
//{
//	TMap<int32, FString> Words{
//		{ 3, "nut" },
//		{ 4, "cone" },
//		{ 5, "house" },
//		{ 6, "planet" },
//		{ 7, "anymore" }
//	};
//	return Words[HiddenWordLength];
//}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bWonGame = false;

	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match
			if (Guess[HWChar] == MyHiddenWord[GChar])
			{
				if (HWChar == GChar) // if they're in the same place
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bWonGame = true;
	}
	else
	{
		bWonGame = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word)
{
	// Treat 0 and 1 letter as isogram
	if (Word.length() <= 1) { return true;  }

	TMap<char, bool> LetterSeen; // set up map
	for (auto Letter : Word) // loop through letters of word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;
		}
		else
		{
			// store this letter
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word)
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
