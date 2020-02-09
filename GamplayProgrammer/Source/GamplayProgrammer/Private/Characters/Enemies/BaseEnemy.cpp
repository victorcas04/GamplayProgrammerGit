// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"
// include for screen messages
#include "Runtime/Engine/Public/Engine.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	// This should be a SkeletalMeshComponent instead of a StaticMeshComponent, but it's faster to use Static Meshes
	MeshEn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	MeshEn->SetOnlyOwnerSee(false);
	MeshEn->bCastDynamicShadow = true;
	MeshEn->CastShadow = true;
	MeshEn->RelativeRotation = FRotator::ZeroRotator;
	MeshEn->RelativeLocation = FVector::ZeroVector;
	MeshEn->SetupAttachment(RootComponent);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	MeshEn->SetHiddenInGame(false, true);

	SetupEnProperties();
}

void ABaseEnemy::SetupEnProperties()
{
	SetCurrentHealth(GetMaxHealth());
}

bool ABaseEnemy::CheckIsDying()
{
	return EnProperties.bIsDying;
}

void ABaseEnemy::SetIsDying(bool newIsDying)
{
	EnProperties.bIsDying = true;
}

bool ABaseEnemy::CheckIsAlive()
{
	return EnProperties.mCurrentHealth > 0;
}

int ABaseEnemy::GetMaxHealth()
{
	return EnProperties.mMaxHealth;
}

int ABaseEnemy::GetCurrentHealth()
{
	return EnProperties.mCurrentHealth;
}

void ABaseEnemy::SetCurrentHealth(int newCurrentHealth)
{
	EnProperties.mCurrentHealth = newCurrentHealth;
	if (newCurrentHealth == 0)
	{
		CustomEnemyDie();
	}
}

int ABaseEnemy::GetDamage()
{
	return EnProperties.mDamage;
}

void ABaseEnemy::SetDamage(int newDamage)
{
	EnProperties.mDamage = newDamage;
}

void ABaseEnemy::CustomEnemyLoseHealth(int ammount)
{
	int newHealthTemp = GetCurrentHealth() - ammount;
	newHealthTemp = FMath::Clamp(newHealthTemp, 0, GetMaxHealth());
	int tempCurrentHealth = GetCurrentHealth();
	SetCurrentHealth(newHealthTemp);
	if (tempCurrentHealth != GetCurrentHealth())
	{
		// here should go the call to play the hurt anim
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "enemy losing health anim...");
	}
}

void ABaseEnemy::CustomEnemyGainHealth(int ammount)
{
	
}

void ABaseEnemy::CustomEnemyDie()
{
	if (!CheckIsDying())
	{
		SetIsDying();

		// here should go the call to play death anim
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "enemy dying anim...");

		Destroy();
	}
}
