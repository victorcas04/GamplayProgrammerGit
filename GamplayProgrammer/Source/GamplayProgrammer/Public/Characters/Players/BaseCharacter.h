// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
// include for timelines
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterMovementComponent;

USTRUCT()
struct FCharacterProperties
{
	GENERATED_BODY()

public:
	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Health", meta = (ClampMin = "0", ClampMax = "10", Category = "Health"))
		int mMaxHealth = 3;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Health", meta = (Category = "Health"))
		int mCurrHealth;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Running", Category = "Movement")
		bool bIsRunning = false;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Crouching", Category = "Movement")
		bool bIsCrouching = false;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Sliding", Category = "Movement")
		bool bIsSliding = false;
	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Sliding Time", meta = (ClampMin = "0", ClampMax = "8"), Category = "Movement")
		float mMaxSlidingTime = 2.0f;
	//
	UPROPERTY(EditAnywhere, DisplayName = "Default Speed", meta = (ClampMin = "0", ClampMax = "1000"), Category = "Movement | MovementSpeed")
		float mDefaultSpeed = 600.0f;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Speed", Category = "Movement | MovementSpeed")
		float mCurrSpeed;
	// > number = > speed when sprinting
	UPROPERTY(EditAnywhere, DisplayName = "Mux Run Speed", meta = (ClampMin = "1", ClampMax = "10"), Category = "Movement | MovementSpeed | Multipliers")
		float mRunSpeedMux = 2.0f;
	// > number = > slow when crouching
	UPROPERTY(EditAnywhere, DisplayName = "Mux Crouch Speed", meta = (ClampMin = "0", ClampMax = "1"), Category = "Movement | MovementSpeed | Multipliers")
		float mCrouchSpeedMux = 0.6f;
	// > number = > slow when zooming in
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn Speed", meta = (ClampMin = "0", ClampMax = "1"), Category = "Movement | MovementSpeed | Multipliers")
		float mZoomInSpeedMux = 0.2f;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is ZoomingIn", Category = "Weapon")
		bool bIsZoomingIn = false;
	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Ammo", meta = (ClampMin = "0", ClampMax = "100"), Category = "Weapon")
		int mMaxAmmo = 10;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Ammo", Category = "Weapon")
		int mCurrAmmo;
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Reloading", Category = "Weapon")
		bool bIsReloading = false;
	//
	UPROPERTY(EditAnywhere, DisplayName = "ReloadTime", meta = (ClampMin = "0", ClampMax = "10"), Category = "Weapon")
		float mReloadTime = 2.0f;
	// > number = > zoom
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn", meta = (ClampMin = "0", ClampMax = "0.9"), Category = "Weapon | Multipliers")
		float mZoomInMux = 0.4f;
};

UCLASS()
class GAMPLAYPROGRAMMER_API ABaseCharacter : public ACharacter, public IIHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;
	//
	UPROPERTY(BlueprintReadOnly)
		UCharacterMovementComponent* BaseCharacterMovementComponent;
	// this is public so the design team can modify it on editor
	UPROPERTY(EditAnywhere, Category = "Movement")
		UCurveFloat* FloatCurveSlidingDecay;

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
		float GetMaxSlidingTime();
	//
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = true))
		void SetMaxSlidingTime(float newSlidingTime);
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
		void SetIsReloading(bool newIsReloading = true);
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
		void RestartSliding();
	//
	UFUNCTION(BlueprintCallable)
		void ZoomIn();
	//
	UFUNCTION(BlueprintCallable)
		void ZoomOut();
	//
	UFUNCTION(BlueprintCallable)
		void StartReloading();
	//
	UFUNCTION(BlueprintCallable)
		void StopReloading();
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

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

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

	// TIMELINES MANAGEMENT //////////////////////////////////////////////////////////////////////////
	//
	UPROPERTY()
		UTimelineComponent* SlidingDecayTimeline;
	//
	UFUNCTION()
		void SlidingDecayTimelineUpdate(float DeltaTime);
	//
	UFUNCTION()
		void SlidingDecayTimelineCallback(float value);
	//
	UFUNCTION()
		void SlidingDecayTimelineFinishedCallback();
	//
	UFUNCTION()
		void SlidingDecayTimelineSetup();
	//////////////////////////////////////////////////////////////////////////
};
