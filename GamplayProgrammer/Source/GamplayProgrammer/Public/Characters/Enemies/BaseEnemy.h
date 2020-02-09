// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UStaticMeshComponent;

USTRUCT()
struct FEnemyProperties
{
	GENERATED_BODY()

public:

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Dying")
		bool bIsDying = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Health", meta = (ClampMin = "0", ClampMax = "10"))
		int mMaxHealth = 5;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Health")
		int mCurrentHealth;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Damage", meta = (ClampMin = "0", ClampMax = "10"))
		int mDamage = 1;
};

UCLASS(Blueprintable, config = Game)
class GAMPLAYPROGRAMMER_API ABaseEnemy : public ACharacter, public IIHealth
{
	GENERATED_BODY()
	
public:

	// Sets default values for this enemy's properties
	ABaseEnemy();

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UStaticMeshComponent* MeshEn;

	// CHARACTER PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsDying();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsAlive();

	//
	UFUNCTION(BlueprintCallable)
		int GetMaxHealth();

	//
	UFUNCTION(BlueprintCallable)
		int GetCurrentHealth();

	//
	UFUNCTION(BlueprintCallable)
		int GetDamage();

	//
	UFUNCTION(BlueprintSetter)
		void SetDamage(int newDamage);

	//////////////////////////////////////////////////////////////////////////

	// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomEnemyLoseHealth(int ammount = 1);

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomEnemyGainHealth(int ammount = 1);

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomEnemyDie();

	//////////////////////////////////////////////////////////////////////////

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Enemy Properties"))
		FEnemyProperties EnProperties;

private:
	//
	UFUNCTION()
		void SetupEnProperties();

	// SETS //////////////////////////////////////////////////////////////////////////
	// we set this private to avoid problems

	//
	UFUNCTION()
		void SetIsDying(bool newIsDying = true);

	// 
	UFUNCTION()
		void SetCurrentHealth(int newCurrentHealth);

	//////////////////////////////////////////////////////////////////////////

};
