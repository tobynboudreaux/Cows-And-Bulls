// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    InitGame();

    // PrintLine(TEXT("The number of hidden words is %i"), GetValidWords(Words).Num());
    // Actual Format
    // PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); 
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    // if game is over ClearScreen() and SetupGame() the game
    // else checking PlayerGuess

    if (bGameOver) 
    {
        ClearScreen();
        InitGame();
        return;
    }
    else 
    {
        ProcessGuess(PlayerInput); 
    }
    
}

void UBullCowCartridge::InitGame()
{
    // Welcoming the Player
    PrintLine(TEXT("Welcome to BullCows!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();    
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \nPress enter to continue...")); // Prompt Player to to guess
    // Works because of the Cartridge.h file
    // PrintLine(TEXT("The HiddenWord is: %s. \nIt is %i characters long"), *HiddenWord, HiddenWord.Len()); // Debug Line
    

    // const TCHAR HW[] = TEXT("cakes");
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    // PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]);

    // int32 i = 0;
    // while (i < 10)
    // {
    //     PrintLine(TEXT("%i"), i);
    //     i++;
    // }

    // for (int32 a = 0; a < 10; a++)
    // {
    //     PrintLine(TEXT("%i"), a);
    // }

    // int32 j = 0;
    // do 
    // {
    //     PrintLine(TEXT("%i"), j);
    //     j++;
    // } while (j < 2);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (HiddenWord == Guess) 
    {
        ClearScreen();
        PrintLine(TEXT("Correct! Next Word!"));
        EndGame();
        return;
    } 

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i Characters Long. Try guessing again!"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters. Try guessing again!"));
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You ran out of Lives!")); 
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i Bulls and %i Cows!"), Bulls, Cows);
    PrintLine(TEXT("Try guessing again! \nYou have %i lives remaining."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}
\
void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount ++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount ++;
                break;
            }
        }
    }
    
}