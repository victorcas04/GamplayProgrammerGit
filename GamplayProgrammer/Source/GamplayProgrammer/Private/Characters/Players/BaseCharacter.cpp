/// @author: Victor de Castro Hurtado

#include "BaseCharacter.h"
// include for screen messages
#include "Runtime/Engine/Public/Engine.h"
// include for timers (delays)
#include <Engine/World.h>
#include "BaseWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"

// DEFAULT INCLUDES (UE4) //////////////////////////////////////////////////////////////////////////

#include "BaseProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(false);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = true;
	Mesh1P->CastShadow = true;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Setup our character movement component ref
	BaseCharacterMovementComponent = GetCharacterMovement();

	// Create our weapon logic
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	Mesh1P->SetHiddenInGame(false, true);

	SetupChProperties();
	mOriginalFOV = FirstPersonCameraComponent->FieldOfView;

	// Timelines setup
	SlidingDecayTimelineSetup();
	// components are initialized before the begin play of the actor, so we don't have problems using weapon variables here
	ZoomInTimelineSetup();

	// need to do this here instead of the constructor because it gets overrided by unreal on play
	BaseCharacterMovementComponent->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ABaseCharacter::SetupChProperties()
{
	SetCurrentHealth(GetMaxHealth());
	SetDefaultSpeed(BaseCharacterMovementComponent->MaxWalkSpeed);
	ResetCrouchSpeed();
}

// CHARACTER PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

float ABaseCharacter::GetInvulnerableTime()
{
	return ChProperties.mInvulnerableTime;
}

void ABaseCharacter::SetInvulnerableTime(float newInvulnerableTime)
{
	ChProperties.mInvulnerableTime = newInvulnerableTime;
}

int ABaseCharacter::GetMaxHealth()
{
	return ChProperties.mMaxHealth;
}

int ABaseCharacter::GetCurrentHealth()
{
	return ChProperties.mCurrentHealth;
}

void ABaseCharacter::SetIsInvulnerable(bool newIsInvulnerable)
{
	ChProperties.bIsInvulnerable = newIsInvulnerable;
}

bool ABaseCharacter::CheckIsDying()
{
	return ChProperties.bIsDying;
}

void ABaseCharacter::SetIsDying(bool newIsDying)
{
	ChProperties.bIsDying = true;
}

void ABaseCharacter::SetCurrentHealth(int newCurrentHealth)
{
	ChProperties.mCurrentHealth = newCurrentHealth;
	if (newCurrentHealth == 0)
	{
		CustomCharacterDie();
	}
}

void ABaseCharacter::CustomCharacterLoseHealth(int ammount)
{
	if (CheckCanLoseHealth())
	{
		int newHealthTemp = GetCurrentHealth() - ammount;
		newHealthTemp = FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
		int tempCurrentHealth = GetCurrentHealth();
		SetCurrentHealth(newHealthTemp);
		if (tempCurrentHealth != GetCurrentHealth())
		{
			// here should go the call to play the hurt anim
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "losing health anim...");
			StartInvulnerability();
		}
	}
}

void ABaseCharacter::CustomCharacterGainHealth(int ammount)
{
	if (CheckCanGainHealth())
	{
		int newHealthTemp = GetCurrentHealth() + ammount;
		newHealthTemp = FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
		int tempCurrentHealth = GetCurrentHealth();
		SetCurrentHealth(newHealthTemp);
		if (tempCurrentHealth != GetCurrentHealth())
		{
			// here should go the call to play anim or effects of gaining health
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "gaining health effect...");
		}
	}
}

void ABaseCharacter::CustomCharacterDie()
{
	if (!CheckIsDying())
	{
		SetIsDying();

		// here should go the call to play death anim
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "dying anim...");

		// here should call Game Instance to restart the level or do whatever needed if you die
	}
}

void ABaseCharacter::SetIsRunning(bool newIsRunning)
{
	ChProperties.bIsRunning = newIsRunning;
}

void ABaseCharacter::SetIsCrouching(bool newIsCrouching)
{
	ChProperties.bIsCrouching = newIsCrouching;
}

void ABaseCharacter::SetIsSliding(bool newIsSliding)
{
	ChProperties.bIsSliding = newIsSliding;
}

float ABaseCharacter::GetMaxSlidingTime()
{
	return ChProperties.mMaxSlidingTime;
}

void ABaseCharacter::SetMaxSlidingTime(float newSlidingTime)
{
	ChProperties.mMaxSlidingTime = newSlidingTime;
}

void ABaseCharacter::SetDefaultSpeed(float newDefaultSpeed)
{
	ChProperties.mDefaultSpeed = newDefaultSpeed;
}

float ABaseCharacter::GetDefaultSpeed()
{
	return ChProperties.mDefaultSpeed;
}

float ABaseCharacter::GetCurrentSpeed()
{
	return ChProperties.mCurrentSpeed;
}

void ABaseCharacter::SetCurrentSpeed(float newSpeed)
{
	ChProperties.mCurrentSpeed = newSpeed;
}

float ABaseCharacter::GetRunSpeedMux()
{
	return ChProperties.mRunSpeedMux;
}

float ABaseCharacter::GetCrouchSpeedMux()
{
	return ChProperties.mCrouchSpeedMux;
}

void ABaseCharacter::SetIsReloading(bool newIsReloading)
{
	ChProperties.bIsReloading = newIsReloading;
}

void ABaseCharacter::SetIsZoomingIn(bool newIsZoomingIn)
{
	ChProperties.bIsZoomingIn = newIsZoomingIn;
}

//////////////////////////////////////////////////////////////////////////

// SPEED RELATED FUNCTIONS //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::SetWalkSpeedOnZoomIn()
{
	if (WeaponComponent)
	{
		BaseCharacterMovementComponent->MaxWalkSpeed = WeaponComponent->GetZoomInSpeedMux() * GetDefaultSpeed();
	}
}

void ABaseCharacter::SetWalkSpeedOnCrouched()
{
	BaseCharacterMovementComponent->MaxWalkSpeedCrouched = BaseCharacterMovementComponent->MaxWalkSpeed;
}

void ABaseCharacter::SetWalkSpeedOnMux(float mux)
{
	BaseCharacterMovementComponent->MaxWalkSpeed *= mux;
}

void ABaseCharacter::SetWalkSpeedOnDiv(float div)
{
	BaseCharacterMovementComponent->MaxWalkSpeed /= div;
}

void ABaseCharacter::SetCrouchSpeedOnMux(float mux)
{
	BaseCharacterMovementComponent->MaxWalkSpeedCrouched *= mux;
}

void ABaseCharacter::ResetCrouchSpeed()
{
	BaseCharacterMovementComponent->MaxWalkSpeedCrouched = GetCrouchSpeedMux() * GetDefaultSpeed();
}

void ABaseCharacter::ResetDefaultSpeed()
{
	BaseCharacterMovementComponent->MaxWalkSpeed = ChProperties.mDefaultSpeed;
}

void ABaseCharacter::ResetSpeedOnAmmoChange()
{
	ResetDefaultSpeed();
	if (CheckIsRunning())
	{
		SetWalkSpeedOnMux(GetRunSpeedMux());
	}
	if (CheckIsCrouching())
	{
		SetWalkSpeedOnMux(GetCrouchSpeedMux());
		SetWalkSpeedOnCrouched();
	}
}

//////////////////////////////////////////////////////////////////////////

// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::StartInvulnerability()
{
	if (CheckCanStartInvulnerability())
	{
		SetIsInvulnerable();

		float TempInvulnerableTime = GetInvulnerableTime();

		if (TempInvulnerableTime > 0.0f)
		{
			// here should go the call to play anim or effects of invulnerability
			GEngine->AddOnScreenDebugMessage(-1, TempInvulnerableTime, FColor::Yellow, "INVULNERABLE");

			FTimerHandle InvulnerableHandle;
			FTimerDelegate InvulnerableDelegate;
			InvulnerableDelegate.BindUFunction(this, TEXT("StopInvulnerability"));
			GetWorld()->GetTimerManager().SetTimer(InvulnerableHandle, InvulnerableDelegate, TempInvulnerableTime, false);
		}
		else
		{
			StopInvulnerability();
		}
	}
}

void ABaseCharacter::StopInvulnerability()
{
	if (CheckCanStopInvulnerability())
	{
		SetIsInvulnerable(false);
	}
}

void ABaseCharacter::CustomCharacterStartJumping()
{
	// here should go the call to play the jumping anim
	// we use the standard jump from ACharacter
	Jump();
}

void ABaseCharacter::CustomCharacterStopJumping()
{
	// we use the standard jump from ACharacter
	StopJumping();
}

void ABaseCharacter::StartRunning()
{
	// play animation
	if (CheckCanStartRunning())
	{
		StopCrouching();
		SetIsRunning();
		if (CheckIsZoomingIn())
		{
			SetWalkSpeedOnZoomIn();
		}
		SetWalkSpeedOnMux(GetRunSpeedMux());
	}
}

void ABaseCharacter::StopRunning()
{
	// play animation
	if (CheckCanStopRunning())
	{
		SetWalkSpeedOnDiv(GetRunSpeedMux());
		SetIsRunning(false);
		StopSliding(true);
	}
}

void ABaseCharacter::StartCrouching()
{
	// play animation
	if (CheckCanStartCrouching())
	{
		SetIsCrouching();

		// we use the standard crouch from ACharacter
		Crouch();
		if (CheckIsZoomingIn())
		{
			SetWalkSpeedOnZoomIn();
		}
		SetWalkSpeedOnMux(GetCrouchSpeedMux());
		SetWalkSpeedOnCrouched();
	}
}

void ABaseCharacter::StopCrouching()
{
	// play animation
	if (CheckCanStopCrouching())
	{
		// we use the standard uncrouch from ACharacter
		UnCrouch();
		SetWalkSpeedOnDiv(GetCrouchSpeedMux());
		ResetCrouchSpeed();
		SetIsCrouching(false);
		SetIsSliding(false);
	}
}

void ABaseCharacter::StartSliding()
{
	// play animation
	if (CheckCanStartSliding())
	{
		StartCrouching();
		SetIsSliding();
		if (SlidingDecayTimeline)
		{
			SlidingDecayTimeline->PlayFromStart();
		}
	}
}

void ABaseCharacter::StopSliding(bool bKeepCrouched)
{
	// play animation
	if (CheckCanStopSliding())
	{
		if (!bKeepCrouched)
		{
			StopCrouching();
		}
		RestartSliding();
		SetIsSliding(false);
	}
}

void ABaseCharacter::RestartSliding()
{
	if (SlidingDecayTimeline)
	{
		SlidingDecayTimeline->Stop();
	}
	ResetCrouchSpeed();
}

void ABaseCharacter::CharacterChangeAmmoType()
{
	CancelReload();
	ResetZoom();
	ResetSpeedOnAmmoChange();
	if (WeaponComponent)
	{
		WeaponComponent->ChangeAmmoType();
		ZoomInTimelineSetup();
	}
}

void ABaseCharacter::ZoomIn()
{
	// play animation
	if (CheckCanZoomIn())
	{
		SetIsZoomingIn();

		// first we set the walk speed while zomming
		SetWalkSpeedOnZoomIn();

		// then we set the rest of the walk speed multipliers
		if (CheckIsRunning())
		{
			SetWalkSpeedOnMux(GetRunSpeedMux());
		}
		if (CheckIsCrouching())
		{
			SetWalkSpeedOnMux(GetCrouchSpeedMux());
			SetWalkSpeedOnCrouched();
		}
		if (ZoomInTimeline)
		{
			ZoomInTimeline->Play();
		}
	}
}

void ABaseCharacter::ZoomOut()
{
	// play animation
	if (CheckCanZoomOut())
	{
		if (WeaponComponent)
		{
			SetWalkSpeedOnDiv(WeaponComponent->GetZoomInSpeedMux());
		}
		SetWalkSpeedOnCrouched();
		if (ZoomInTimeline)
		{
			ZoomInTimeline->Reverse();
		}
		SetIsZoomingIn(false);
	}
}

void ABaseCharacter::ResetZoom()
{
	FirstPersonCameraComponent->FieldOfView = mOriginalFOV;
	if (ZoomInTimeline)
	{
		ZoomInTimeline->Stop();
	}
	SetIsZoomingIn(false);
}

void ABaseCharacter::StartReloading()
{
	// play animation
	if (CheckCanStartReloading())
	{
		SetIsReloading();
		ZoomOut();

		float TempReloadTime = WeaponComponent->GetReloadTime();
		GEngine->AddOnScreenDebugMessage(-1, TempReloadTime, FColor::Yellow, "reloading anim...");
		
		if (WeaponComponent)
		{
			
			if (TempReloadTime > 0.0f)
			{
				FTimerDelegate ReloadDelegate;
				ReloadDelegate.BindUFunction(this, TEXT("StopReloading"));
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, ReloadDelegate, TempReloadTime, false);
			}
			else
			{
				StopReloading();
			}
		}
	}
}

void ABaseCharacter::StopReloading()
{
	// play animation
	if (WeaponComponent)
	{
		WeaponComponent->RestoreFullAmmoCurrent();
	}
	if (CheckCanStopReloading())
	{
		SetIsReloading(false);
	}
}

void ABaseCharacter::CancelReload()
{
	if (CheckCanStopReloading())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadHandle);
		ReloadHandle.Invalidate();
		SetIsReloading(false);
	}
}

void ABaseCharacter::CharacterShoot()
{
	if (WeaponComponent)
	{
		if (WeaponComponent->CheckIsValidCurrentAmmo())
		{
			if (!CheckIsReloading())
			{
				if (WeaponComponent->CheckHaveEnoughAmmo())
				{
					UWorld* const World = GetWorld();
					if (World)
					{
						const FRotator SpawnRotation = GetControlRotation();
						// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
						const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

						// call weapon component shoot
						WeaponComponent->Shoot(SpawnLocation, SpawnRotation);
					}
				}
				else
				{
					// if you try to shoot and have no ammo, you will start reloading
					StartReloading();
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ERROR: no Valid Ammo Type assigned.");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ERROR: no Weapon Component found.");
	}
}

//////////////////////////////////////////////////////////////////////////

// BOOLEAN CHECKERS //////////////////////////////////////////////////////////////////////////

bool ABaseCharacter::CheckIsRunning()
{
	return ChProperties.bIsRunning;
}

bool ABaseCharacter::CheckIsCrouching()
{
	return ChProperties.bIsCrouching;
}

bool ABaseCharacter::CheckIsSliding()
{
	return ChProperties.bIsSliding;
}

bool ABaseCharacter::CheckIsReloading()
{
	return ChProperties.bIsReloading;
}

bool ABaseCharacter::CheckIsZoomingIn()
{
	return ChProperties.bIsZoomingIn;
}

bool ABaseCharacter::CheckIsAlive()
{
	return ChProperties.mCurrentHealth > 0;
}

bool ABaseCharacter::CheckCanStartInvulnerability()
{
	return !CheckIsInvulnerable();
}

bool ABaseCharacter::CheckCanStopInvulnerability()
{
	return CheckIsInvulnerable();
}

bool ABaseCharacter::CheckIsInvulnerable()
{
	return ChProperties.bIsInvulnerable;
}

bool ABaseCharacter::CheckCanLoseHealth()
{
	return CheckIsAlive() && !CheckIsInvulnerable();
}

bool ABaseCharacter::CheckCanGainHealth()
{
	return CheckIsAlive();
}

bool ABaseCharacter::CheckCanStartRunning()
{
	return !CheckIsRunning();
}

bool ABaseCharacter::CheckCanStopRunning()
{
	return CheckIsRunning();
}

bool ABaseCharacter::CheckCanStartCrouching()
{
	return !CheckIsCrouching();
}

bool ABaseCharacter::CheckCanStopCrouching()
{
	return CheckIsCrouching();
}

bool ABaseCharacter::CheckCanStartSliding()
{
	return !(CheckIsSliding() || CheckIsZoomingIn());
}

bool ABaseCharacter::CheckCanStopSliding()
{
	return CheckIsSliding();
}

bool ABaseCharacter::CheckCanZoomIn()
{
	if (!CheckIsZoomingIn())
	{
		if (!CheckIsReloading())
		{
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "Cannot ZoomIn while Reloading...");
		}
	}
	return false;
}

bool ABaseCharacter::CheckCanZoomOut()
{
	return CheckIsZoomingIn();
}

bool ABaseCharacter::CheckCanStartReloading()
{
	if (WeaponComponent)
	{
		return !CheckIsReloading() && !WeaponComponent->CheckIsAmmoFull();
	}
	else
	{
		// if we don't have a weapon, cannot reload it
		return false;
	}
}

bool ABaseCharacter::CheckCanStopReloading()
{
	return CheckIsReloading();
}

//////////////////////////////////////////////////////////////////////////

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckIsSliding())
	{
		SlidingDecayTimelineUpdate(DeltaTime);
	}
}

// Timelines Management //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::SlidingDecayTimelineUpdate(float DeltaTime)
{
	if (SlidingDecayTimeline)
	{
		SlidingDecayTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ABaseCharacter::SlidingDecayTimelineCallback(float value)
{
	SetCrouchSpeedOnMux(value);
}

void ABaseCharacter::SlidingDecayTimelineFinishedCallback()
{
	StopSliding();
}

void ABaseCharacter::SlidingDecayTimelineSetup()
{
	if (FloatCurveSlidingDecay)
	{
		FOnTimelineFloat OnSlidingDecayTimelineCallback;
		FOnTimelineEventStatic OnSlidingDecayTimelineFinishedCallback;

		SlidingDecayTimeline = NewObject<UTimelineComponent>(this, FName("SlidingDecayTimelineAnimation"));
		SlidingDecayTimeline->SetLooping(false);

		// we reasign dynamically the keypoints on the timeline to make it fit the sliding duration //////////////////////////////////////////////////////////////////////////

		SlidingDecayTimeline->SetTimelineLength(GetMaxSlidingTime());

		if (GetMaxSlidingTime() > 0.0f)
		{
			float OldTimeBeginTransition; float OldTimeEndTransition;
			FloatCurveSlidingDecay->FloatCurve.GetTimeRange(OldTimeBeginTransition, OldTimeEndTransition);

			float ratioTemp = GetMaxSlidingTime() / OldTimeEndTransition;

			TArray<FRichCurveKey> CopyOfKeys = FloatCurveSlidingDecay->FloatCurve.GetCopyOfKeys();
			FloatCurveSlidingDecay->FloatCurve.Reset();
			for (FRichCurveKey k : CopyOfKeys)
			{
				FRichCurveKey key = FRichCurveKey(k.Time * ratioTemp, k.Value);
				key.InterpMode = k.InterpMode;
				key.TangentMode = k.TangentMode;
				FloatCurveSlidingDecay->FloatCurve.AddKey(key.Time, key.Value);
			}
		}

		//////////////////////////////////////////////////////////////////////////

		OnSlidingDecayTimelineCallback.BindUFunction(this, FName{ TEXT("SlidingDecayTimelineCallback") });
		SlidingDecayTimeline->AddInterpFloat(FloatCurveSlidingDecay, OnSlidingDecayTimelineCallback);

		OnSlidingDecayTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SlidingDecayTimelineFinishedCallback") });
		SlidingDecayTimeline->SetTimelineFinishedFunc(OnSlidingDecayTimelineFinishedCallback);

		SlidingDecayTimeline->RegisterComponent();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "ERROR: no Sliding Decay Curve assigned.");
	}
}

void ABaseCharacter::ZoomInTimelineUpdate(float DeltaTime)
{
	if (WeaponComponent && ZoomInTimeline)
	{
		ZoomInTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ABaseCharacter::ZoomInTimelineCallback(float value)
{
	if (WeaponComponent)
	{
		FirstPersonCameraComponent->FieldOfView = mOriginalFOV * (1 - (WeaponComponent->GetZoomInMux() * value));
	}
}

void ABaseCharacter::ZoomInTimelineSetup()
{
	if (WeaponComponent)
	{
		UCurveFloat* TempZoomInCurveFloat = WeaponComponent->GetFloatCurveZoomInDelay();
		if (TempZoomInCurveFloat)
		{
			FOnTimelineFloat OnZoomInDelayTimelineCallback;

			ZoomInTimeline = NewObject<UTimelineComponent>(this, FName("ZoomInDelayTimelineAnimation"));
			ZoomInTimeline->SetLooping(false);

			// we reasign dynamically the keypoints on the timeline to make it fit the zoom in delay //////////////////////////////////////////////////////////////////////////

			float TempZoomInDelay = WeaponComponent->GetZoomInDelay();
			ZoomInTimeline->SetTimelineLength(TempZoomInDelay);

			if (TempZoomInDelay > 0.0f)
			{
				float OldTimeBeginTransition; float OldTimeEndTransition;
				TempZoomInCurveFloat->FloatCurve.GetTimeRange(OldTimeBeginTransition, OldTimeEndTransition);

				float ratioTemp = TempZoomInDelay / OldTimeEndTransition;

				TArray<FRichCurveKey> CopyOfKeys = TempZoomInCurveFloat->FloatCurve.GetCopyOfKeys();
				TempZoomInCurveFloat->FloatCurve.Reset();
				for (FRichCurveKey k : CopyOfKeys)
				{
					FRichCurveKey key = FRichCurveKey(k.Time * ratioTemp, k.Value);
					key.InterpMode = k.InterpMode;
					key.TangentMode = k.TangentMode;
					TempZoomInCurveFloat->FloatCurve.AddKey(key.Time, key.Value);
				}
			}

			//////////////////////////////////////////////////////////////////////////

			OnZoomInDelayTimelineCallback.BindUFunction(this, FName{ TEXT("ZoomInTimelineCallback") });
			ZoomInTimeline->AddInterpFloat(TempZoomInCurveFloat, OnZoomInDelayTimelineCallback);

			ZoomInTimeline->RegisterComponent();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "ERROR: no ZoomIn Delay assigned.");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "ERROR: no Weapon Component assigned.");
	}
}

//////////////////////////////////////////////////////////////////////////

// CAMERA //////////////////////////////////////////////////////////////////////////

float ABaseCharacter::GetBaseTurnRate()
{
	return BaseTurnRate;
}

void ABaseCharacter::SetBaseTurnRate(float newBaseTurnRate)
{
	BaseTurnRate = newBaseTurnRate;
}

float ABaseCharacter::GetBaseLookUpRate()
{
	return BaseLookUpRate;
}

void ABaseCharacter::SetBaseLookUpRate(float newBaseLookUpRate)
{
	BaseLookUpRate = newBaseLookUpRate;
}

//////////////////////////////////////////////////////////////////////////

// DEFAULT METHODS (UE4) //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);
}

void ABaseCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

//////////////////////////////////////////////////////////////////////////
