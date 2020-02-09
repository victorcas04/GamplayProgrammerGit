// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
// include for timelines
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterMovementComponent;
class UInputComponent;
class UWeaponComponent;

USTRUCT()
struct FCharacterProperties
{
	GENERATED_BODY()

public:

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Invulnerable")
		bool bIsInvulnerable = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Invulnerable Time", meta = (ClampMin = "0", ClampMax = "10"))
		float mInvulnerableTime = 2.0f;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Dying")
		bool bIsDying = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Health", meta = (ClampMin = "0", ClampMax = "10"))
		int mMaxHealth = 3;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Health")
		int mCurrHealth;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Running")
		bool bIsRunning = false;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Crouching")
		bool bIsCrouching = false;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Sliding")
		bool bIsSliding = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Sliding Time", meta = (ClampMin = "0", ClampMax = "8"))
		float mMaxSlidingTime = 2.0f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Default Speed", meta = (ClampMin = "0", ClampMax = "1000"))
		float mDefaultSpeed = 600.0f;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Speed")
		float mCurrSpeed;

	// 1.0 = no extra speed while running
	// 10.0 = max extra speed while running
	UPROPERTY(EditAnywhere, DisplayName = "Mux Run Speed", meta = (ClampMin = "1", ClampMax = "10"))
		float mRunSpeedMux = 2.0f;

	// 0.1 = max slow down when crouching
	// 1.0 = no slow down when crouching
	UPROPERTY(EditAnywhere, DisplayName = "Mux Crouch Speed", meta = (ClampMin = "0.1", ClampMax = "1"))
		float mCrouchSpeedMux = 0.6f;
	/*
	// REM
	// 0.0 = instant zoom in
	// 2.0 = it'll take 2 secs to zoom in
	UPROPERTY(EditAnywhere, DisplayName = "ZoomIn Delay", meta = (ClampMin = "0", ClampMax = "2"))
		float mZoomInDelay = 0.2f;
	
	// 0.1 = max slow down when zooming in
	// 1.0 = no slow down when zooming in
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn Speed", meta = (ClampMin = "0.1", ClampMax = "1"))
		float mZoomInSpeedMux = 0.2f;
	*/
	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is ZoomingIn")
		bool bIsZoomingIn = false;
	/*
	// REM
	UPROPERTY(EditAnywhere, DisplayName = "Max Ammo", meta = (ClampMin = "0", ClampMax = "100"))
		int mMaxAmmo = 10;

	// REM
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Ammo")
		int mCurrAmmo;

	// REM
	UPROPERTY(EditAnywhere, DisplayName = "Ammo Per Shot")
		int mAmmoPerShot = 1;
	*/

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Reloading")
		bool bIsReloading = false;
	/*
	// REM
	UPROPERTY(EditAnywhere, DisplayName = "ReloadTime", meta = (ClampMin = "0", ClampMax = "10"))
		float mReloadTime = 2.0f;

	// REM
	// 0.0 = no zoom
	// 0.9 = max zoom
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn", meta = (ClampMin = "0", ClampMax = "0.9"))
		float mZoomInMux = 0.4f;
	*/
};

UCLASS(Blueprintable, config = Game)
class GAMPLAYPROGRAMMER_API ABaseCharacter : public ACharacter, public IIHealth
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ABaseCharacter();

	//
	UPROPERTY(BlueprintReadOnly)
		UCharacterMovementComponent* BaseCharacterMovementComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		class USkeletalMeshComponent* Mesh1P;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// APawn interface
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	// CHARACTER PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION()
		void SetIsInvulnerable(bool newIsInvulnerable = true);

	//
	UFUNCTION(BlueprintCallable)
		float GetInvulnerableTime();

	//
	UFUNCTION(BlueprintCallable)
		void SetInvulnerableTime(float newInvulnerableTime);

	//
	UFUNCTION(BlueprintCallable)
		int GetMaxHealth();

	//
	UFUNCTION(BlueprintCallable)
		int GetCurrHealth();

	//
	UFUNCTION(BlueprintCallable)
		float GetMaxSlidingTime();

	//
	UFUNCTION(BlueprintCallable)
		void SetMaxSlidingTime(float newSlidingTime);

	//
	UFUNCTION(BlueprintCallable)
		float GetDefaultSpeed();

	//
	UFUNCTION(BlueprintCallable)
		float GetCurrentSpeed();

	//
	UFUNCTION(BlueprintCallable)
		float GetRunSpeedMux();
	
	//
	UFUNCTION(BlueprintCallable)
		float GetCrouchSpeedMux();
	/*
	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInSpeedMux();
	
	//
	UFUNCTION(BlueprintCallable)
		int GetMaxAmmo();

	//
	UFUNCTION(BlueprintCallable)
		int GetCurrAmmo();

	//
	UFUNCTION(BlueprintCallable)
		int GetAmmoPerShot();

	//
	UFUNCTION(BlueprintCallable)
		void SetAmmoPerShot(int newAmmoPerShot = 1);

	//
	UFUNCTION(BlueprintCallable)
		float GetReloadTime();

	//
	UFUNCTION(BlueprintCallable)
		void SetReloadTime(float newReloadTime);

	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInDelay();

	//
	UFUNCTION(BlueprintCallable)
		void SetZoomInDelay(float newZoomInDelay);

	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInMux();

	//
	UFUNCTION(BlueprintCallable)
		void SetZoomInMux(float newZoomInMux);
	*/
	//////////////////////////////////////////////////////////////////////////

	// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		void StartInvulnerability();

	//
	UFUNCTION(BlueprintCallable)
		void StopInvulnerability();

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomCharacterLoseHealth(int ammount = 1);

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomCharacterGainHealth(int ammount = 1);

	// function to be called from the IHealth interface on the blueprint
	UFUNCTION(BlueprintCallable)
		void CustomCharacterDie();

	//
	UFUNCTION(BlueprintCallable)
		void CustomCharacterStartJumping();

	//
	UFUNCTION(BlueprintCallable)
		void CustomCharacterStopJumping();

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
		void CharacterChangeAmmoType();

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

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
		void OnFire();
	/*
	//
	UFUNCTION(BlueprintCallable)
		void DecreaseAmmo(int ammount);

	//
	UFUNCTION(BlueprintCallable)
		void IncreaseAmmo(int ammount);

	//
	UFUNCTION(BlueprintCallable)
		void RestoreFullAmmo();

	//
	UFUNCTION(BlueprintCallable)
		void EmptyAmmo();

	//
	UFUNCTION(BlueprintCallable)
		void DoWhenAmmoIsEmpty();
	*/
	//////////////////////////////////////////////////////////////////////////

	// BOOLEAN CHECKERS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsInvulnerable();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsDying();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsAlive();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsRunning();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsCrouching();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsSliding();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsZoomingIn();
	/*
	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsAmmoFull();
	*/
	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsReloading();
	/*
	//
	UFUNCTION(BlueprintCallable)
		bool CheckHaveEnoughAmmo();
	*/
	//////////////////////////////////////////////////////////////////////////

	// WEAPON //////////////////////////////////////////////////////////////////////////

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UWeaponComponent* BaseWeaponComponent;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		class USceneComponent* FP_MuzzleLocation;

	/** Projectile class to spawn */
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class ABaseProjectile> ProjectileClass;
	*/

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FVector GunOffset;

	// TODO FROM HERE

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UAnimMontage* FireAnimation;

	//////////////////////////////////////////////////////////////////////////

	// CAMERA //////////////////////////////////////////////////////////////////////////

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseTurnRate = 45.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseLookUpRate = 45.0f;

	//
	UFUNCTION()
		float GetBaseTurnRate();

	//
	UFUNCTION()
		void SetBaseTurnRate(float newBaseTurnRate);

	//
	UFUNCTION()
		float GetBaseLookUpRate();

	//
	UFUNCTION()
		void SetBaseLookUpRate(float newBaseLookUpRate);

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//////////////////////////////////////////////////////////////////////////

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Character Properties"))
		FCharacterProperties ChProperties;

	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Sliding Decay Curve"))
		UCurveFloat* FloatCurveSlidingDecay;
	/*
	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "ZoomIn Delay Curve"))
		UCurveFloat* FloatCurveZoomInDelay;
	*/
	// DEFAULT METHODS (UE4) //////////////////////////////////////////////////////////////////////////

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//////////////////////////////////////////////////////////////////////////

private:

	//
	UPROPERTY()
		float mTempDeltaTime;

	//
	UPROPERTY()
		float mOriginalFOV;

	//
	UFUNCTION()
		void SetupChProperties();

	// SETS //////////////////////////////////////////////////////////////////////////
	// we set this private to avoid problems

	//
	UFUNCTION()
		void SetIsDying(bool newIsDying = true);

	// 
	UFUNCTION()
		void SetCurrHealth(int newCurrHealth);

	// 
	UFUNCTION()
		void SetIsRunning(bool newIsRunning = true);

	// 
	UFUNCTION()
		void SetIsCrouching(bool newIsCrouching = true);

	// 
	UFUNCTION()
		void SetIsSliding(bool newIsSliding = true);

	// 
	UFUNCTION()
		void SetIsReloading(bool newIsReloading = true);

	// 
	UFUNCTION()
		void SetIsZoomingIn(bool newIsZoomingIn = true);
	/*
	// 
	UFUNCTION()
		void SetCurrAmmo(int newCurrAmmo);
	*/
	//////////////////////////////////////////////////////////////////////////

	// SPEED RELATED FUNCTIONS //////////////////////////////////////////////////////////////////////////

	// we set this private to avoid problems
	UFUNCTION()
		void SetDefaultSpeed(float newDefaultSpeed);

	// we set this private to avoid problems
	UFUNCTION()
		void SetCurrentSpeed(float newSpeed);

	// need to reset the walk speed before start to multiplying it on the different states of the character
	UFUNCTION()
		void SetWalkSpeedOnZoomIn();

	// this function equals the crouched with the walk speed because we need to use it after setting the correct walk speed
	UFUNCTION()
		void SetWalkSpeedOnCrouched();

	// to increase or decrease walk speed with a %
	UFUNCTION()
		void SetWalkSpeedOnMux(float mux);

	// to restore the walk speed with a %, previously increased or decreased by SetWalkSpeedOnMux
	UFUNCTION()
		void SetWalkSpeedOnDiv(float div);

	// to increase or decrease crouch speed with a %
	UFUNCTION()
		void SetCrouchSpeedOnMux(float mux);

	// to restore the crouch speed (no need to specify a % since it's gonna be the same al the time)
	UFUNCTION()
		void ResetCrouchSpeed();

	//////////////////////////////////////////////////////////////////////////

	// BOOLEAN CHECKERS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION()
		bool CheckCanStartInvulnerability();

	//
	UFUNCTION()
		bool CheckCanStopInvulnerability();

	//
	UFUNCTION()
		bool CheckCanLoseHealth();

	//
	UFUNCTION()
		bool CheckCanGainHealth();

	//
	UFUNCTION()
		bool CheckCanStartRunning();

	//
	UFUNCTION()
		bool CheckCanStopRunning();

	//
	UFUNCTION()
		bool CheckCanStartCrouching();

	//
	UFUNCTION()
		bool CheckCanStopCrouching();

	//
	UFUNCTION()
		bool CheckCanStartSliding();

	//
	UFUNCTION()
		bool CheckCanStopSliding();

	//
	UFUNCTION()
		bool CheckCanZoomIn();

	//
	UFUNCTION()
		bool CheckCanZoomOut();

	//
	UFUNCTION()
		bool CheckCanStartReloading();

	//
	UFUNCTION()
		bool CheckCanStopReloading();

	//////////////////////////////////////////////////////////////////////////

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
	
	//
	UPROPERTY()
		UTimelineComponent* ZoomInTimeline;

	//
	UFUNCTION()
		void ZoomInTimelineUpdate(float DeltaTime);

	//
	UFUNCTION()
		void ZoomInTimelineCallback(float value);

	//
	UFUNCTION()
		void ZoomInTimelineSetup();
	
	//////////////////////////////////////////////////////////////////////////
};
