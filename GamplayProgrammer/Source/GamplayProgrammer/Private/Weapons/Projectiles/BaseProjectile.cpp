// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BaseProjectile.h"
#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// include for timers (delays)
#include <Engine/World.h>

#include "Runtime/Engine/Public/Engine.h"

ABaseProjectile::ABaseProjectile() 
{
	PrimaryActorTick.bCanEverTick = false; PrimaryActorTick.bCanEverTick = false;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	// set to ignore with pawn so we can walk through the projectiles
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CollisionComp->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Set as root component
	RootComponent = CollisionComp;

	// Create a gun mesh component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pt_Mesh"));
	ProjectileMesh->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	ProjectileMesh->bCastDynamicShadow = true;
	ProjectileMesh->CastShadow = true;
	ProjectileMesh->SetupAttachment(RootComponent);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->bRotationFollowsVelocity = true;
}

void ABaseProjectile::SetBaseChOwner(ABaseCharacter* newBaseChOwner)
{
	if (newBaseChOwner)
	{
		BaseChOwner = newBaseChOwner;
	}
}

ABaseCharacter* ABaseProjectile::GetBaseChOwner()
{
	return BaseChOwner;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetupPtProperties();
	SetLifeTimeRemaining(GetLifeTime());
	StartAutodestroyTimer();
}

void ABaseProjectile::SetupPtProperties()
{
	SetLifeTime(GetLifeTime());
	SetFallOff(GetFallOff());
	SetProjectileSpeed(GetProjectileSpeed());
	SetCanBounce(CheckCanBounce());
	SetCanStepOnIt(CheckCanStepOnIt());
}

void ABaseProjectile::StartAutodestroyTimer()
{
	// After cleaning and invalidating a timer we need to rebind it
	GetWorld()->GetTimerManager().ClearTimer(AutoDestroyHandle);
	AutoDestroyHandle.Invalidate();
	AutoDestroyDelegate.BindUFunction(this, TEXT("DestroyByTime"));

	GetWorld()->GetTimerManager().SetTimer(AutoDestroyHandle, AutoDestroyDelegate, GetLifeTimeRemaining(), false);
}

void ABaseProjectile::DestroyByTime()
{
	// here should go the call to play anim or effects of autodestroying (explosions) -> ON THE BLUEPRINT EVENT
	DoWhenDestroyed();
	Destroy();
}

// STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

int ABaseProjectile::GetDamage()
{
	return PtProperties.mDamage;
}

void ABaseProjectile::SetDamage(int newDamage)
{
	PtProperties.mDamage = newDamage;
}

float ABaseProjectile::GetLifeTime()
{
	return PtProperties.mLifeTime;
}

void ABaseProjectile::SetLifeTime(float newTimeOfLife)
{
	PtProperties.mLifeTime = newTimeOfLife;
	InitialLifeSpan = newTimeOfLife;
}

float ABaseProjectile::GetLifeTimeRemaining()
{
	return PtProperties.mLifeTimeRemaining;
}

void ABaseProjectile::SetLifeTimeRemaining(float newTimeOfLifeRemaining)
{
	PtProperties.mLifeTimeRemaining = newTimeOfLifeRemaining;
}

float ABaseProjectile::GetFallOff()
{
	return PtProperties.mFallOff;
}

void ABaseProjectile::SetFallOff(float newFallOff)
{
	PtProperties.mFallOff = newFallOff;
	ProjectileMovement->ProjectileGravityScale = newFallOff;
}

bool ABaseProjectile::CheckCanBounce()
{
	return PtProperties.bCanBounce && (GetCurrentBounces() < GetMaxBounces());
}

void ABaseProjectile::SetCanBounce(bool newShouldBounce)
{
	PtProperties.bCanBounce = newShouldBounce;
	ProjectileMovement->bShouldBounce = newShouldBounce;
}

int ABaseProjectile::GetMaxBounces()
{
	return PtProperties.mMaxBounces;
}

bool ABaseProjectile::CheckShouldBeDestroyedOncontact()
{
	return PtProperties.bShouldBeDestroyedOncontact;
}

void ABaseProjectile::SetShouldBeDestroyedOncontact(bool newShouldBeDestroyedOnContact)
{
	PtProperties.bShouldBeDestroyedOncontact = newShouldBeDestroyedOnContact;
}

void ABaseProjectile::SetMaxBounces(int newMaxBounces)
{
	PtProperties.mMaxBounces = newMaxBounces;
}

int ABaseProjectile::GetCurrentBounces()
{
	return PtProperties.mCurrentBounces;
}

void ABaseProjectile::SetCurrentBounces(int newCurrentBounces)
{
	PtProperties.mCurrentBounces = newCurrentBounces;
}

float ABaseProjectile::GetExtraTimePerBounce()
{
	return PtProperties.mExtraTimePerBounce;
}

void ABaseProjectile::SetExtraTimePerBounce(float newExtraTimePerBounce)
{
	PtProperties.mExtraTimePerBounce = newExtraTimePerBounce;
}

bool ABaseProjectile::CheckCanStepOnIt()
{
	return PtProperties.bCanStepOnIt;
}

void ABaseProjectile::SetCanSelfDamage(bool newCanSelfDamage)
{
	PtProperties.bCanSelfDamage = newCanSelfDamage;
}

bool ABaseProjectile::CheckCanSelfDamage()
{
	return PtProperties.bCanSelfDamage;
}

void ABaseProjectile::SetCanStepOnIt(bool newCanStepOnIt)
{
	PtProperties.bCanStepOnIt = newCanStepOnIt;

	// Players can walk on it
	if (newCanStepOnIt)
	{
		CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Default, 0.f));
		CollisionComp->CanCharacterStepUpOn = ECB_Yes;
	}
	// Players can't walk on it
	else
	{
		CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		CollisionComp->CanCharacterStepUpOn = ECB_No;
	}
}

float ABaseProjectile::GetProjectileSpeed()
{
	return PtProperties.mProjectileSpeed;
}

void ABaseProjectile::SetProjectileSpeed(float newProjectileSpeed)
{
	PtProperties.mProjectileSpeed = newProjectileSpeed;
	ProjectileMovement->MaxSpeed = newProjectileSpeed;
	ProjectileMovement->Velocity *= newProjectileSpeed;
}

//////////////////////////////////////////////////////////////////////////

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetLifeTimeRemaining(GetLifeTimeRemaining() - DeltaTime);
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		CustomProjectileHit(OtherActor);

		if ((OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		if (CheckCanBounce())
		{
			SetCurrentBounces(GetCurrentBounces() + 1);
			SetLifeTimeRemaining(GetLifeTimeRemaining() + GetExtraTimePerBounce());
			StartAutodestroyTimer();
		}

		if (CheckShouldBeDestroyedOncontact() && (this->StaticClass() != OtherActor->StaticClass()))
		{
			DoWhenDestroyed();
			Destroy();
		}
	}
}

void ABaseProjectile::CustomProjectileHit_Implementation(AActor* OtherActor)
{

}

void ABaseProjectile::DoWhenDestroyed_Implementation()
{

}
