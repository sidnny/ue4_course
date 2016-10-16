#pragma once
#include <string>

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
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWonGame;

	static bool IsIsogram(FString);
	static bool IsLowercase(FString);
};