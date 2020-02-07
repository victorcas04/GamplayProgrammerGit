// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHealth.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHealth : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class GAMPLAYPROGRAMMER_API IIHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// To use those interface functions:
	// 1.- Create CustomLoseHealth, CustomGainHEalth or CustomDie in the class that wants to implement them
	// 2.- On the blueprint of that class call those custom methods from this interface generic events
	// 3.- To access its implementations from other blueprints call the generic interface events

	//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ILoseHealth(int ammount);

	//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void IGainHealth(int ammount);

	//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void IDie();
};
