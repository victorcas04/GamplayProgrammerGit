// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMPLAYPROGRAMMER_API ABaseEnemy : public ACharacter, public IIHealth
{
	GENERATED_BODY()
	
};
