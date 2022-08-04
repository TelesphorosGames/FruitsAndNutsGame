// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()
 
	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUpGame();
	void EndGame();
	void CheckGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& PassedWordList) const;
	void GetFruitNuts(const FString& Guess, int32& FruitCount, int32& NutCount) const;

	
	// Your declarations go below!
	private:
	FString HiddenWord; // DECLARES A STRING VARIABLE (FString for UNREAL) called HiddenWord
	int32 Lives; // declares an INTEGER VARIABLE called Lives 
	bool bGameOver;
	TArray<FString> Isograms;


	
};
