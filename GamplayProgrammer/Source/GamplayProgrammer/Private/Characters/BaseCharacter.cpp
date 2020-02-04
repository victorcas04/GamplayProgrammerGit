// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupChProperties();
}

void ABaseCharacter::SetupChProperties()
{
	SetCurrHealth(GetMaxHealth());
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

