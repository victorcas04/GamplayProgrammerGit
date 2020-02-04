// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

USTRUCT(Blueprintable)
struct FCharacterProperties
{
	GENERATED_BODY()
	//
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "10"), Category = "Health")
		int mMaxHealth = 1;
	//
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int mCurrHealth;
	//
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		bool bIsRunning = false;
	//
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		bool bIsCrouching = false;
	//
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		bool bIsSliding = false;
	//
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "60"), Category = "Movement")
		float mSlidingTime = 2.0f;
	//
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1000"), Category = "Movement | MovementSpeed")
		float mDefaultSpeed = 600.0f;
	//
	UPROPERTY(VisibleAnywhere, Category = "Movement | MovementSpeed")
		float mCurrSpeed;
	// > number = > speed when sprinting
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "10"), Category = "Movement | MovementSpeed | Multipliers")
		float mRunSpeedMux = 2.0f;
	// > number = > slow when crouching
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1"), Category = "Movement | MovementSpeed | Multipliers")
		float mCrouchSpeedMux = 0.7f;
	// > number = > slow when zooming in
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1"), Category = "Movement | MovementSpeed | Multipliers")
		float mZoomInSpeedMux = 0.1f;
	//
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool bIsZoomingIn = false;
	//
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool bIsReloading = false;
	//
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "10"), Category = "Weapon")
		float mReloadTime = 2.0f;
	// > number = > zoom
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "0.9"), Category = "Weapon | Multipliers")
		float mZoomInMux = 0.4f;
};

UCLASS()
class GAMPLAYPROGRAMMER_API ABaseCharacter : public ACharacter, public IIHealth
{
	GENERATED_BODY()

private:
	//
	UFUNCTION()
		void SetupChProperties();

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// CHARACTER PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		int GetMaxHealth();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		int GetCurrHealth();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetCurrHealth(int newCurrHealth);
	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void ChLoseHealth(int ammount = 1);
	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void ChGainHealth(int ammount = 1);
	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void ChDie();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetIsRunning(bool newIsRunning = true);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsRunning();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetIsCrouching(bool newIsCrouching = true);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsCrouching();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetIsSliding(bool newIsSliding = true);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsSliding();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetSlidingTime();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetSlidingTime(float newSlidingTime);
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetDefaultSpeed(float newDefaultSpeed);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetDefaultSpeed();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetCurrentSpeed();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetCurrentSpeed(float newSpeed);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetRunSpeedMux();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetCrouchSpeedMux();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetZoomInSpeedMux();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetIsReloading(bool newIsReloading);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsReloading();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetIsZoomingIn(bool newIsZoomingIn);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsZoomingIn();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetReloadTime();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetReloadTime(float newReloadTime);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		float GetZoomInMux();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetZoomInMux(float newZoomInMux);
	//////////////////////////////////////////////////////////////////////////

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Character Properties"))
		FCharacterProperties ChProperties;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
