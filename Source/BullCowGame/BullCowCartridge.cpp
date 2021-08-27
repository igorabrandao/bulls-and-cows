// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Setting up the game initial state
    this->SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (this->bGameOver)
    {
        ClearScreen();
        this->SetupGame(); // Setting up the new game
    }
    else
    {
        if (Input == this->HiddenWord)
        {
            PrintLine(TEXT("You have Won!"));
            this->EndGame();
        }
        else
        {
            PrintLine(TEXT("You lost a life, now you have %i lives"), --this->Lives);

            if (Input.Len() != this->HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long"), this->HiddenWord.Len());
            }
            
            if (this->Lives == 0)
            {
                PrintLine(TEXT("You have Lost!"));
                this->EndGame();
            }
        }
    }
}

/**
 * Method to display the welcome message
 */
void UBullCowCartridge::DisplayWelcomeMessage() const
{
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), this->HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), this->Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));
}

/**
 * Method to handle the game initialization
 */
void UBullCowCartridge::SetupGame()
{
    this->HiddenWord = TEXT("cakes");
    this->Lives = this->HiddenWord.Len();
    this->bGameOver = false;

    this->DisplayWelcomeMessage();
}

/**
 * Method to handle the end game
 */
void UBullCowCartridge::EndGame()
{
    this->bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}