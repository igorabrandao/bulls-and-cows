// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Setting up the game initial state
    this->SetupGame();

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), this->HiddenWord.Len());
    PrintLine(TEXT("Type in your guess and press enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();

    if (Input == this->HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
    }
    else
    {
        if (Input.Len() != this->HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), this->HiddenWord.Len());
        }

        PrintLine(TEXT("You have Lost!"));
    }
}

/**
 * Method to handle the game initialization
 */
void UBullCowCartridge::SetupGame()
{
    this->HiddenWord = TEXT("cakes");
    this->Lives = 4;
}