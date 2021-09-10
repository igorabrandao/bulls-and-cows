// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Load the isogram word list from the file
    TArray<FString> Words;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

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
        this->ProcessGuess(Input);
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
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
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
    PrintLine(TEXT("\nPress enter to play again."));
}

/**
 * Method to handle the end game
 */
void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    if (Guess == this->HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        this->EndGame();
        return;
    }

    if (Guess.Len() != this->HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), this->HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), this->Lives);
        return;
    }

    // Check if isogram
    if (!this->IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
    }

    // Remove life
    PrintLine(TEXT("Lost a life!"));
    --this->Lives;

    if (this->Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *this->HiddenWord);
        this->EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left"), this->Lives);
}

/**
 * Function to check whether or not a word is an isogram
 */
bool UBullCowCartridge::IsIsogram(const FString Word) const
{
    int32 WordLength = Word.Len();

    for (size_t i = 0; i < (WordLength - 1); i++)
    {
        for (size_t j = (i + 1); j < WordLength; j++)
        {
            // Check if the current word repeat with any from the entire word
            if (Word[i] == Word[j])
            {
                // The word is not a Isogram
                return false;
            }
        }
    }

    // The word is a Isogram
    return true;
}