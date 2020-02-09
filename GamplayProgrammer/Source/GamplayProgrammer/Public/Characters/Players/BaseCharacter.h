/// @author: Victor de Castro Hurtado

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
		int mCurrentHealth;

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
		float mCurrentSpeed;

	// 1.0 = no extra speed while running
	// 10.0 = max extra speed while running
	UPROPERTY(EditAnywhere, DisplayName = "Mux Run Speed", meta = (ClampMin = "1", ClampMax = "10"))
		float mRunSpeedMux = 2.0f;

	// 0.1 = max slow down when crouching
	// 1.0 = no slow down when crouching
	UPROPERTY(EditAnywhere, DisplayName = "Mux Crouch Speed", meta = (ClampMin = "0.1", ClampMax = "1"))
		float mCrouchSpeedMux = 0.6f;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is ZoomingIn")
		bool bIsZoomingIn = false;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Is Reloading")
		bool bIsReloading = false;
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
		int GetCurrentHealth();

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

	//
	UFUNCTION(BlueprintCallable)
		void CancelReload();

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
		void CharacterShoot();

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

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsReloading();

	//////////////////////////////////////////////////////////////////////////

	// WEAPON //////////////////////////////////////////////////////////////////////////

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UWeaponComponent* WeaponComponent;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		class USceneComponent* FP_MuzzleLocation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FVector GunOffset;
	
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
		FTimerHandle ReloadHandle;

	//
	UPROPERTY()
		float mOriginalFOV;

	//
	UFUNCTION()
		void SetupChProperties();

	//
	UFUNCTION()
		void ResetZoom();

	// SETS //////////////////////////////////////////////////////////////////////////
	// we set this private to avoid problems

	//
	UFUNCTION()
		void SetIsDying(bool newIsDying = true);

	// 
	UFUNCTION()
		void SetCurrentHealth(int newCurrentHealth);

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

	//
	UFUNCTION()
		void ResetDefaultSpeed();

	//
	UFUNCTION()
	void ResetSpeedOnAmmoChange();

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
