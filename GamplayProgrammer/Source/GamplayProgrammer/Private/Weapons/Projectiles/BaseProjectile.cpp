// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// include for timers (delays)
#include <Engine/World.h>

ABaseProjectile::ABaseProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
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

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetupPtProperties();

	FTimerHandle AutoDestroyHandle;
	FTimerDelegate AutoDestroyDelegate;
	AutoDestroyDelegate.BindUFunction(this, TEXT("DestroyByTime"));
	GetWorld()->GetTimerManager().SetTimer(AutoDestroyHandle, AutoDestroyDelegate, GetLifeTime(), false);
}

void ABaseProjectile::DestroyByTime()
{
	// here should go the call to play anim or effects of autodestroying (explosions)
	DoWhenDestroyed();
	Destroy();
}

void ABaseProjectile::SetupPtProperties()
{
	SetLifeTime(GetLifeTime());
	SetFallOff(GetFallOff());
	SetProjectileMaxSpeed(GetProjectileMaxSpeed());
	SetProjectileInitSpeed(GetProjectileInitSpeed());
	SetCanBounce(CheckCanBounce());
	SetCanStepOnIt(CheckCanStepOnIt());
}

// STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

void ABaseProjectile::DoWhenDestroyed_Implementation()
{
}

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
	return PtProperties.bCanBounce;
}

void ABaseProjectile::SetCanBounce(bool newShouldBounce)
{
	PtProperties.bCanBounce = newShouldBounce;
	ProjectileMovement->bShouldBounce = newShouldBounce;
}

bool ABaseProjectile::CheckShouldBeDestroyedOncontact()
{
	return PtProperties.bShouldBeDestroyedOncontact;
}

void ABaseProjectile::SetShouldBeDestroyedOncontact(bool newShouldBeDestroyedOnContact)
{
	PtProperties.bShouldBeDestroyedOncontact = newShouldBeDestroyedOnContact;
}

bool ABaseProjectile::CheckCanStepOnIt()
{
	return PtProperties.bCanStepOnIt;
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

float ABaseProjectile::GetProjectileMaxSpeed()
{
	return PtProperties.mProjectileMaxSpeed;
}

void ABaseProjectile::SetProjectileMaxSpeed(float newProjectileMaxSpeed)
{
	PtProperties.mProjectileMaxSpeed = newProjectileMaxSpeed;
	ProjectileMovement->MaxSpeed = newProjectileMaxSpeed;
}

float ABaseProjectile::GetProjectileInitSpeed()
{
	return PtProperties.mProjectileInitSpeed;
}

void ABaseProjectile::SetProjectileInitSpeed(float newProjectileInitSpeed)
{
	PtProperties.mProjectileInitSpeed = newProjectileInitSpeed;
	ProjectileMovement->InitialSpeed = newProjectileInitSpeed;
}

//////////////////////////////////////////////////////////////////////////

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		if ((OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		if (CheckShouldBeDestroyedOncontact())
		{
			DoWhenDestroyed();
			Destroy();
		}
	}
}
