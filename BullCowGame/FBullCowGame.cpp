#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32,int32> WordLengthToMaxTries { { 3, 4 }, { 4, 7 }, { 5, 10 }, { 6, 16 }, { 7, 20 } };

	return WordLengthToMaxTries[HiddenWord.length()];
}

void FBullCowGame::Reset()
{	
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";

	HiddenWord = HIDDEN_WORD;	
	CurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}

	if (!IsLowercase(Guess))
	{
		return EGuessStatus::NotLowercase;
	}

	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}

	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = HiddenWord.length();
	for (int32 I = 0; I < WordLength; I++)
	{
		for (int32 J = 0; J < WordLength; J++)
		{
			if (Guess[J] == HiddenWord[I])
			{
				if (I == J)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
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
