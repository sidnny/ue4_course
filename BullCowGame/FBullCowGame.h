/*
 * The game logic (no view code or direct user interaction).
 * The game is a simple guess the word game based on Mastermind.
 */
#pragma once

#include <string>

// To make syntax Unreal-friendly
using FString = std::string;
using int32 = int;

// initializes bulls and cows to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus // class scoped; otherwise global
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Alpha_Char
};

class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	void SetHiddenWord(int32);
	int32 GetHiddenWordLength() const;
	bool HasWonGame() const;
	EGuessStatus IsGuessValid(FString) const;

	void Reset();

	FBullCowCount SubmitValidGuess(FString);

// compile-time values
private:
	// see constructor for initialization values
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWonGame;

	static bool IsIsogram(FString);
	static bool IsLowercase(FString);
};