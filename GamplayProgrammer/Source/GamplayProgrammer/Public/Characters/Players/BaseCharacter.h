// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterMovementComponent;

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
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"), Category = "Weapon")
		int mMaxAmmo = 10;
	//
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		int mCurrAmmo;
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
		void SetIsZoomingIn(bool newIsZoomingIn = true);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		bool CheckIsZoomingIn();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		int GetMaxAmmo();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		int GetCurrAmmo();
	// TODO: remove bpcall
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetCurrAmmo(int newCurrAmmo);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void ChDecreaseAmmo(int ammount);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void ChIncreaseAmmo(int ammount);
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void ChEmptyAmmo();
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

	// SPEED RELATED FUNCTIONS //////////////////////////////////////////////////////////////////////////
	// need to reset the walk speed before start to multiplying it on the different states of the character
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetWalkSpeedOnZoomIn();
	// this function equals the crouched with the walk speed because we need to use it after setting the correct walk speed
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetWalkSpeedOnCrouched();
	// to increase or decrease walk speed with a %
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetWalkSpeedOnMux(float mux);
	// to restore the walk speed with a %, previously increased or decreased by SetWalkSpeedOnMux
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetWalkSpeedOnDiv(float div);
	// to increase or decrease crouch speed with a %
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetCrouchSpeedOnMux(float mux);
	// to restore the crouch speed (no need to specify a % since it's gonna be the same al the time)
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void ResetCrouchSpeed();
	//////////////////////////////////////////////////////////////////////////

	// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////
	//
	UFUNCTION(BlueprintCallable)
		void StartRunning();
	//
	UFUNCTION(BlueprintCallable)
		void StopRunning();
	//
	UFUNCTION(BlueprintCallable)
		void StartCrouching();
	//
	UFUNCTION(BlueprintCallable)
		void StopCrouching();
	//
	UFUNCTION(BlueprintCallable)
		void StartSliding();
	//
	UFUNCTION(BlueprintCallable)
		void StopSliding(bool bKeepCrouched = false);
	//
	UFUNCTION(BlueprintCallable)
		void ZoomIn();
	//
	UFUNCTION(BlueprintCallable)
		void ZoomOut();
	//////////////////////////////////////////////////////////////////////////

	// BOOLEAN CHECKERS //////////////////////////////////////////////////////////////////////////
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStartRunning();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStopRunning();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStartCrouching();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStopCrouching();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStartSliding();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStopSliding();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanZoomIn();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanZoomOut();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsAmmoFull();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStartReloading();
	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStopReloading();
	//////////////////////////////////////////////////////////////////////////

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Character Properties"))
		FCharacterProperties ChProperties;

private:
	//
	UFUNCTION()
		void SetupChProperties();
	//
	UPROPERTY()
		UCharacterMovementComponent* ChMovComp;
};
