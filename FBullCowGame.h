#pragma once
#include <iostream>
#include <string.h>

//to make syntax Unreal friendly
using int32 = int;
using FString = std::string;

//All values initialized to 0
struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};

class FBullCowGame 
{
public:
	FBullCowGame(); //Constructor
	void reset(); 
	int32 getMaxTries()const;
	int32 getCurrentTry()const;
	int32 getWordLength()const;
	bool isGameWon()const;
	EGuessStatus checkGuessValidity(FString)const;
	int32 strToInt(FString) const;
	void increaseCurrentTry();
	FBullCowCount submitValidGuess(FString);
	void setHiddenWord(int32);
	bool isStringValidNumber(FString);

private:
	//see constructor for initialization
	int32 myCurrentTry;
	FString myHiddenWord;
	bool bGameWon;

	bool isIsogram(FString) const;
	bool isLowerCase(FString)const;
	bool isNumber(FString)const;
};