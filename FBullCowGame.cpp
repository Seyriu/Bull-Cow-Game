#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map //to make syntax Unreal friendly

FBullCowGame::FBullCowGame() { reset(); myHiddenWord = ""; }
int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getWordLength() const{ return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const{ return bGameWon; }
int32 FBullCowGame::strToInt(FString numString) const { return atoi(numString.c_str()); }

//returns maximum number of tries based on the length of the word
int32 FBullCowGame::getMaxTries() const 
{
	TMap <int32, int32> wordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} }; //word length and max tries. (Difficulty)
	return wordLengthToMaxTries[myHiddenWord.length()];
}

//checks if string inserted is a number
bool FBullCowGame::isNumber(FString wordLength)const
{
	FString::const_iterator it;
	for (it = wordLength.begin(); it != wordLength.end() && isdigit(*it);it++);
	return !wordLength.empty() && it == wordLength.end();
}

EGuessStatus FBullCowGame::checkGuessValidity (FString guess) const
{
	if (!isIsogram(guess)) //not an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!isLowerCase(guess))//not lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length()!=getWordLength())//wrong length
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//sets hidden word based on the length selected
void FBullCowGame::setHiddenWord(int32 wordLength)
{
	TMap <int32, FString> wordLengthToHiddenWord{ { 3,"try" },{ 4,"many" },{ 5,"print" },{ 6,"planet" },{ 7,"planets" } }; //length of the word, word associated
	if ((wordLength > 2) && (wordLength < 8))
	{
		myHiddenWord = wordLengthToHiddenWord[wordLength];
	}
}

//checks if the word length inserted is an acceptable one
bool FBullCowGame::isStringValidNumber(FString inputLength)
{
	if (!(isNumber(inputLength)))
	{
		return false;
	}
	int32 inpLen = 0;
	inpLen = strToInt(inputLength);
	if ((inpLen < 3) || (inpLen > 7))
	{
		return false;
	}
	return true;
}

void FBullCowGame::reset()
{
	//const FString HIDDEN_WORD = "planet";
	//myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bGameWon = false;
	return;
}

void FBullCowGame::increaseCurrentTry()
{
	myCurrentTry++;
	return;
}

/*Receives a valid guess and increments current try. 
Increments number of bulls (right letters in the right spot) and cows (right letters in the wrong spot)*/
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
	FBullCowCount bullCowCount;
	int32 wordLength = myHiddenWord.length();//assuming same length as guess

	for (int32 i = 0; i < wordLength; i++)
	{
		for (int32 j = 0; j < wordLength; j++)
		{
			if ((guess[i] == myHiddenWord[j])&& (i==j))
			{
				bullCowCount.bulls++;
			}
			else if ((guess[i] == myHiddenWord[j]) && (i != j))
			{
				bullCowCount.cows++;
			}
		}
	}
	if (bullCowCount.bulls>=getWordLength())
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	increaseCurrentTry();
	return bullCowCount;
}


bool FBullCowGame::isIsogram(FString word) const
{
	//treat 0 and 1 letter words as isograms 
	if (word.length() <= 1) { return true; }
	TMap <char,bool> seenLetters;
	for (auto letter : word) //For all the letters of the word
	{
		letter = tolower(letter);//Handle mixed case
		if (seenLetters[letter] == true)
		{
			return false;
		}
		else
		{
			seenLetters[letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
	for (auto letter : word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}
