/*
This is the console executable that makes use of the BullCowGame Class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

void printIntro();
FText getValidGuess();
void playGame(); 
bool askToPlayAgain();
void printGameSummary();

FBullCowGame BCGame;

//The entry point for our application
int main()
{
	do 
	{
		printIntro();
		playGame();
	} 
	while (askToPlayAgain()==1);

	return (0); //exit the application
}

//plays a single game to completion
void playGame()
{
	BCGame.reset();
	int32 maxTries=BCGame.getMaxTries();
	FText attempt = "";
	FBullCowCount bullCowCount;
	//Loop asking for guesses while the game is not won
	//and there are still tries remaining
	while (!BCGame.isGameWon() && (BCGame.getCurrentTry() <= BCGame.getMaxTries()))
	{
		attempt = getValidGuess(); 		
		bullCowCount = BCGame.submitValidGuess(attempt);
		std::cout << "Bulls: " << bullCowCount.bulls;
		std::cout << ". Cows: " << bullCowCount.cows << "." << std::endl;
		std::cout << std::endl;
	} 
	printGameSummary();
	return;
}

//Introduce the game
void printIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	FText wordLength;
	do
	{
		std::cout << "insert a word length between 3 and 7: ";
		getline(std::cin, wordLength);
	}
	while (!BCGame.isStringValidNumber(wordLength));
	BCGame.setHiddenWord(BCGame.strToInt(wordLength));
	std::cout << "\nCan you guess the " << BCGame.getWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


//loop continually until the user gives a valid guess
FText getValidGuess()
{
	EGuessStatus status=EGuessStatus::Invalid_Status;
	FText guess = "";
	do {
		std::cout << (BCGame.getMaxTries() - (BCGame.getCurrentTry()-1)) <<" tries left. What's your guess?: ";
		getline(std::cin, guess);
		status = BCGame.checkGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "The word entered must be an isogram. (No character can be a duplicate)\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "The word entered cannot contain uppercase characters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.getWordLength() << " character word.\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (status!=EGuessStatus::OK); //keep looping until we get no errors
	return guess;
}

bool askToPlayAgain()
{
	FText response = "";
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	getline(std::cin,response);
	return (response[0] == 'y') || (response[0] == 'Y');
}

void printGameSummary()
{
	if (BCGame.isGameWon() == true)
	{
		std::cout << "Congratulations, you found the hidden word!";
	}
	else
	{
		std::cout << "Too bad, better luck next time!";
	}
	std::cout << std::endl << std::endl;
	return;
}
