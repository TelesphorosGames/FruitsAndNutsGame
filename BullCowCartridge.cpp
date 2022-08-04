// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" // include everything from this "header file" in the code
#include "HiddenWordList.h"
#include "Math/UnrealMathUtility.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{                                   // execute this stuff
    Super::BeginPlay();               //call the function BeginPlay with this funkydunk Super::
    

    Isograms = GetValidWords(Words);

    PrintLine(TEXT(" Let's play FRUITS AND NUTS! " )); // Print this line, a line of text, with a TEXT("MACRO") 




    // PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    // PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());

    
    
    SetUpGame();   // Calling for the function SetUpGame, declared in the header file, and set below
}    

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) // if bGameOver is over is true, do this stuff
    {
        ClearScreen(); // CLEARS THE SCREEN --> CALLS FUNCTION ClearScreen() 
        
        SetUpGame(); // call the SetUpGame() function
    }  

    else           // else check player guess and keep running game
    {
        CheckGuess(PlayerInput);
    }
}



void UBullCowCartridge::SetUpGame()
{
    bGameOver = false;
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1 )]; 
    Lives = HiddenWord.Len()*2;


    PrintLine(TEXT("I'm thinking of an isogram. You guess a \n word, and I'll tell you how many FRUITS \n and NUTS you have! A FRUIT is a correct \n letter in the right spot. A NUT is a \n correct letter in the wrong spot.")); // change this later in the course <--- Magic number 
    PrintLine(TEXT("The word is %i letters long, which \n means you have %i guesses. Take a guess!"), HiddenWord.Len(), Lives);
    // PrintLine(TEXT("The word is %s."), *HiddenWord); // DEBUG

    // const TCHAR HW[] = TEXT("super");
    // PrintLine(TEXT("Character 1 of the word is : %c"), HiddenWord[0]);
    // PrintLine(TEXT("Character 3 of HW is %c "), HW[2]);
  

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("GAME OVER."));
    PrintLine(TEXT("The word was %s."), *HiddenWord);
    PrintLine(TEXT("PLAY AGAIN? \n(Press Enter)\n"));
}

void UBullCowCartridge::CheckGuess(const FString& Guess)
{
    if (HiddenWord == Guess)
        {
            PrintLine(TEXT("YOU WIN!! \n GREAT JOB!\n"));
            EndGame();
            return;
        }
    if (Lives < 1)
        {
            EndGame();
            return;
        }

    if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letters, remember? \n Guess again!"));
            return;
        }
   
    if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(FString::Printf(TEXT("The word has %i letters, remember? \n Try again!"), HiddenWord.Len())); 
            PrintLine(FString::Printf(TEXT("Take another guess- \n You have %i more."), Lives));

            return;
        }
    else 
        {

            PrintLine(TEXT("\nWrong!"));

            int32 Fruits, Nuts;
            GetFruitNuts(Guess, Fruits, Nuts);            
            PrintLine(TEXT("You have %i Fruits and %i Nuts."), Fruits, Nuts);
            PrintLine(FString::Printf(TEXT("That'll cost you a guess- \n You have %i more. \n Take another guess!"), --Lives));
            return;   
                      
        }
       
    

             
        
}


bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index +1; Comparison< Word.Len(); Comparison++) 
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
    
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& PassedWordList) const
{
    
    TArray<FString> ValidWords;
    
    for (FString Word : PassedWordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {          
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetFruitNuts(const FString& Guess, int32&FruitCount, int32&NutCount) const
{
    FruitCount = 0 ;
    NutCount = 0 ;

    // if the index of Guess is the same as the index of the Hidden Word, increment FruitCount
    // for every true, add one to FruitCount , aka FruitCount ++
    //  if not Fruit, was it a Nut? NutCount++ , etc

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            FruitCount++;
            continue;
        }
    
        
    for (int32 HiddenIndex = 0;  HiddenIndex < HiddenWord.Len(); HiddenIndex++)
    {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                NutCount ++;
                continue;
            }
    }
    }
        
}
    





//  PSUEDOCODE mikey is a TRASHTRASHTRASH instructor 
// Check if Isogram
// Prompt to guess again
// check number of correct characters
// prompt to guess again

//  remove life
// check if lives > 0
// if yes GuessAgain
// show lives left
// if no show GameOver and HiddenWord
// Prompt to Play again, Press enter to play
// check user input
// play again or quit




