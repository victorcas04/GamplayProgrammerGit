// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
// include for screen messages
#include "Runtime/Engine/Public/Engine.h"
// include for timers (delays)
#include <Engine/World.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Setup our character movement component ref
	BaseCharacterMovementComponent = GetCharacterMovement();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupChProperties();
	SlidingDecayTimelineSetup();
}

void ABaseCharacter::SetupChProperties()
{
	SetCurrHealth(GetMaxHealth());
	SetCurrAmmo(GetMaxAmmo());
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

int ABaseCharacter::GetCurrHealth()
{
	return ChProperties.mCurrHealth;
}

void ABaseCharacter::SetIsInvulnerable(bool newIsInvulnerable)
{
	ChProperties.bIsInvulnerable = newIsInvulnerable;
}

void ABaseCharacter::SetCurrHealth(int newCurrHealth)
{
	ChProperties.mCurrHealth = newCurrHealth;
	if (newCurrHealth == 0)
	{
		CustomCharacterDie();
	}
}

void ABaseCharacter::CustomCharacterLoseHealth(int ammount)
{
	if (CheckCanLoseHealth())
	{
		int newHealthTemp = GetCurrHealth() - ammount;
		newHealthTemp = FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
		SetCurrHealth(newHealthTemp);
		// here should go the call to play anim or effects of losing health
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "losing health anim...");
		StartInvulnerability();
	}
}

void ABaseCharacter::CustomCharacterGainHealth(int ammount)
{
	if (CheckCanGainHealth())
	{
		int newHealthTemp = GetCurrHealth() + ammount;
		newHealthTemp = FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
		SetCurrHealth(newHealthTemp);
		// here should go the call to play anim or effects of gaining health
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "gaining health anim...");
	}
}

void ABaseCharacter::CustomCharacterDie()
{
	if (CheckIsAlive())
	{
		// here should go the call to play anim or effects of dying
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "dying...");

		// TODO: restart level
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
	return ChProperties.mCurrSpeed;
}

void ABaseCharacter::SetCurrentSpeed(float newSpeed)
{
	ChProperties.mCurrSpeed = newSpeed;
}

float ABaseCharacter::GetRunSpeedMux()
{
	return ChProperties.mRunSpeedMux;
}

float ABaseCharacter::GetCrouchSpeedMux()
{
	return ChProperties.mCrouchSpeedMux;
}

float ABaseCharacter::GetZoomInSpeedMux()
{
	return ChProperties.mZoomInSpeedMux;
}

void ABaseCharacter::SetIsReloading(bool newIsReloading)
{
	ChProperties.bIsReloading = newIsReloading;
}

void ABaseCharacter::SetIsZoomingIn(bool newIsZoomingIn)
{
	ChProperties.bIsZoomingIn = newIsZoomingIn;
}

int ABaseCharacter::GetMaxAmmo()
{
	return ChProperties.mMaxAmmo;
}

int ABaseCharacter::GetCurrAmmo()
{
	return ChProperties.mCurrAmmo;
}

void ABaseCharacter::SetCurrAmmo(int newCurrAmmo)
{
	ChProperties.mCurrAmmo = newCurrAmmo;
	if (newCurrAmmo == 0)
	{
		DoWhenAmmoIsEmpty();
	}
}

void ABaseCharacter::DecreaseAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() - ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
	// here should go the call to play anim or effects of decreasing ammo
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "decreasing ammo anim...");
}

void ABaseCharacter::IncreaseAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() + ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
	// here should go the call to play anim or effects of increasing ammo
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "increasing ammo anim...");
}

void ABaseCharacter::RestoreFullAmmo()
{
	IncreaseAmmo(GetMaxAmmo());
}

void ABaseCharacter::EmptyAmmo()
{
	DecreaseAmmo(GetMaxAmmo());
}

void ABaseCharacter::DoWhenAmmoIsEmpty()
{
	StartReloading();
}

float ABaseCharacter::GetReloadTime()
{
	return ChProperties.mReloadTime;
}

void ABaseCharacter::SetReloadTime(float newReloadTime)
{
	ChProperties.mReloadTime = newReloadTime;
}

float ABaseCharacter::GetZoomInMux()
{
	return ChProperties.mZoomInMux;
}

void ABaseCharacter::SetZoomInMux(float newZoomInMux)
{
	ChProperties.mZoomInMux = newZoomInMux;
}

//////////////////////////////////////////////////////////////////////////

// SPEED RELATED FUNCTIONS //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::SetWalkSpeedOnZoomIn()
{
	BaseCharacterMovementComponent->MaxWalkSpeed = GetZoomInSpeedMux() * GetDefaultSpeed();
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

//////////////////////////////////////////////////////////////////////////

// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

void ABaseCharacter::StartInvulnerability()
{
	if (CheckCanStartInvulnerability())
	{
		SetIsInvulnerable();

		// here should go the call to play anim or effects of invulnerability
		GEngine->AddOnScreenDebugMessage(-1, GetInvulnerableTime(), FColor::Yellow, "INVULNERABLE");

		FTimerHandle InvulnerableHandle;
		FTimerDelegate InvulnerableDelegate;
		InvulnerableDelegate.BindUFunction(this, TEXT("StopInvulnerability"));
		GetWorld()->GetTimerManager().SetTimer(InvulnerableHandle, InvulnerableDelegate, GetInvulnerableTime(), false);
	}
}

void ABaseCharacter::StopInvulnerability()
{
	if (CheckCanStopInvulnerability())
	{
		SetIsInvulnerable(false);
	}
}

void ABaseCharacter::StartRunning()
{
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
	if (CheckCanStopRunning())
	{
		SetWalkSpeedOnDiv(GetRunSpeedMux());
		SetIsRunning(false);
		StopSliding(true);
	}
}

void ABaseCharacter::StartCrouching()
{
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
	if (CheckCanStartSliding())
	{
		StartCrouching();
		SetIsSliding();
		SlidingDecayTimeline->PlayFromStart();
	}
}

void ABaseCharacter::StopSliding(bool bKeepCrouched)
{
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
	SlidingDecayTimeline->Stop();
	ResetCrouchSpeed();
}

void ABaseCharacter::ZoomIn()
{
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
		FirstPersonCameraComponent->FieldOfView *= (1 - GetZoomInMux());
	}
}

void ABaseCharacter::ZoomOut()
{
	if (CheckCanZoomOut())
	{
		SetWalkSpeedOnDiv(GetZoomInSpeedMux());
		SetWalkSpeedOnCrouched();
		FirstPersonCameraComponent->FieldOfView /= (1 - GetZoomInMux());
		SetIsZoomingIn(false);
	}
}

void ABaseCharacter::StartReloading()
{
	if (CheckCanStartReloading())
	{
		SetIsReloading();
		ZoomOut();
		// here should go the call to play anim or effects of reloading
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "reloading...");
		
		FTimerHandle ReloadHandle;
		FTimerDelegate ReloadDelegate;
		ReloadDelegate.BindUFunction(this, TEXT("StopReloading"));
		GetWorld()->GetTimerManager().SetTimer(ReloadHandle, ReloadDelegate, GetReloadTime(), false);
	}
}

void ABaseCharacter::StopReloading()
{
	RestoreFullAmmo();
	if (CheckCanStopReloading())
	{
		SetIsReloading(false);
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
	return ChProperties.mCurrHealth > 0;
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
	return !(CheckIsZoomingIn() || CheckIsReloading());
}

bool ABaseCharacter::CheckCanZoomOut()
{
	return CheckIsZoomingIn();
}

bool ABaseCharacter::CheckIsAmmoFull()
{
	return ChProperties.mCurrAmmo == ChProperties.mMaxAmmo;
}

bool ABaseCharacter::CheckCanStartReloading()
{
	return !CheckIsReloading() && !CheckIsAmmoFull();
}

bool ABaseCharacter::CheckCanStopReloading()
{
	return CheckIsReloading() && CheckIsAmmoFull();
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

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//////////////////////////////////////////////////////////////////////////
// Timelines Management
//////////////////////////////////////////////////////////////////////////

void ABaseCharacter::SlidingDecayTimelineUpdate(float DeltaTime)
{
	if (SlidingDecayTimeline)
	{
		SlidingDecayTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ABaseCharacter::SlidingDecayTimelineCallback(float value)
{
	// here should go the call to play anim or effects of sliding
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, "sliding...");
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
		UCurveFloat* FloatCurveSlidingTemp = NewObject<UCurveFloat>();

		FOnTimelineFloat OnTimelineCallback;
		FOnTimelineEventStatic OnTimelineFinishedCallback;

		SlidingDecayTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));

		SlidingDecayTimeline->SetLooping(false);
		//SlidingDecayTimeline->SetPlayRate(.5f);

		// we reasign dynamically the keypoints on the timeline to make it fit the sliding duration //////////////////////////////////////////////////////////////////////////
		SlidingDecayTimeline->SetTimelineLength(GetMaxSlidingTime());

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
		//////////////////////////////////////////////////////////////////////////

		OnTimelineCallback.BindUFunction(this, FName{ TEXT("SlidingDecayTimelineCallback") });
		SlidingDecayTimeline->AddInterpFloat(FloatCurveSlidingDecay, OnTimelineCallback);

		OnTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SlidingDecayTimelineFinishedCallback") });
		SlidingDecayTimeline->SetTimelineFinishedFunc(OnTimelineFinishedCallback);

		SlidingDecayTimeline->RegisterComponent();
	}
}
//////////////////////////////////////////////////////////////////////////
