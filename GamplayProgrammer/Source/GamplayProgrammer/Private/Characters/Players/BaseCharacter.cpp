// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChMovComp = GetCharacterMovement();
	SetupChProperties();
}

void ABaseCharacter::SetupChProperties()
{
	SetCurrHealth(GetMaxHealth());
	SetCurrAmmo(GetMaxAmmo());
}

int ABaseCharacter::GetMaxHealth()
{
	return ChProperties.mMaxHealth;
}

int ABaseCharacter::GetCurrHealth()
{
	return ChProperties.mCurrHealth;
}

void ABaseCharacter::SetCurrHealth(int newCurrHealth)
{
	ChProperties.mCurrHealth = newCurrHealth;
	if (newCurrHealth == 0)
	{
		ChDie();
	}
}

void ABaseCharacter::ChLoseHealth(int ammount)
{
	int newHealthTemp = GetCurrHealth() - ammount;
	FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
	SetCurrHealth(newHealthTemp);
	// TODO: play anim or effects of losing health
}

void ABaseCharacter::ChGainHealth(int ammount)
{
	int newHealthTemp = GetCurrHealth() + ammount;
	FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
	SetCurrHealth(newHealthTemp);
	// TODO: play anim or effects of gaining health
}

void ABaseCharacter::ChDie()
{
	// TODO: restart level or smtg
}

void ABaseCharacter::SetIsRunning(bool newIsRunning)
{
	ChProperties.bIsRunning = newIsRunning;
}

bool ABaseCharacter::CheckIsRunning()
{
	return ChProperties.bIsRunning;
}

void ABaseCharacter::SetIsCrouching(bool newIsCrouching)
{
	ChProperties.bIsCrouching = newIsCrouching;
}

bool ABaseCharacter::CheckIsCrouching()
{
	return ChProperties.bIsCrouching;
}

void ABaseCharacter::SetIsSliding(bool newIsSliding)
{
	ChProperties.bIsSliding = newIsSliding;
}

bool ABaseCharacter::CheckIsSliding()
{
	return ChProperties.bIsSliding;
}

float ABaseCharacter::GetSlidingTime()
{
	return ChProperties.mSlidingTime;
}

void ABaseCharacter::SetSlidingTime(float newSlidingTime)
{
	ChProperties.mSlidingTime = newSlidingTime;
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

bool ABaseCharacter::CheckIsReloading()
{
	return ChProperties.bIsReloading;
}

void ABaseCharacter::SetIsZoomingIn(bool newIsZoomingIn)
{
	ChProperties.bIsZoomingIn = newIsZoomingIn;
}

bool ABaseCharacter::CheckIsZoomingIn()
{
	return ChProperties.bIsZoomingIn;
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
		ChEmptyAmmo();
	}
}

void ABaseCharacter::ChDecreaseAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() - ammount;
	FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
	// TODO: play anim or effects of decreasing ammo
}

void ABaseCharacter::ChIncreaseAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() + ammount;
	FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
	// TODO: play anim or effects of increasing ammo
}

void ABaseCharacter::ChEmptyAmmo()
{
	// TODO: call Reload()
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

void ABaseCharacter::SetWalkSpeedOnZoomIn()
{
	ChMovComp->MaxWalkSpeed = GetZoomInSpeedMux() * GetDefaultSpeed();
}

void ABaseCharacter::SetWalkSpeedOnCrouched()
{
	ChMovComp->MaxWalkSpeedCrouched = ChMovComp->MaxWalkSpeed;
}

void ABaseCharacter::SetWalkSpeedOnMux(float mux)
{
	ChMovComp->MaxWalkSpeed *= mux;
}

void ABaseCharacter::SetWalkSpeedOnDiv(float div)
{
	ChMovComp->MaxWalkSpeed /= div;
}

void ABaseCharacter::SetCrouchSpeedOnMux(float mux)
{
	ChMovComp->MaxWalkSpeedCrouched *= mux;
}

void ABaseCharacter::ResetCrouchSpeed()
{
	ChMovComp->MaxWalkSpeedCrouched = GetCrouchSpeedMux() * GetDefaultSpeed();
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
		// TODO: restart sliding timeline
		SetIsSliding(false);
	}
}

void ABaseCharacter::ZoomIn()
{
	if (CheckCanZoomIn())
	{
		SetIsZoomingIn();
		SetWalkSpeedOnZoomIn();
		if (CheckIsRunning())
		{
			SetWalkSpeedOnMux(GetRunSpeedMux());
		}
		if (CheckIsCrouching())
		{
			SetWalkSpeedOnMux(GetCrouchSpeedMux());
			SetWalkSpeedOnCrouched();
		}
		// TODO: get fov from camera
		float FOV = 90;
		FOV *= (1 - GetZoomInMux());
	}
}

void ABaseCharacter::ZoomOut()
{
	if (CheckCanZoomOut())
	{
		SetWalkSpeedOnDiv(GetZoomInMux());
		SetWalkSpeedOnCrouched();
		// TODO: get fov from camera
		float FOV = 90;
		FOV /= (1 - GetZoomInMux());
		SetIsZoomingIn(false);
	}
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
	return !CheckIsReloading() && CheckIsAmmoFull();
}

bool ABaseCharacter::CheckCanStopReloading()
{
	return CheckIsReloading() && CheckIsAmmoFull();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

