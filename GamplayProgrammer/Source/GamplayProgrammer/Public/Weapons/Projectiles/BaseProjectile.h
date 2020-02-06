// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UStaticMeshComponent;

USTRUCT()
struct FProjectileProperties
{
	GENERATED_BODY()

public:

	//
	UPROPERTY(EditAnywhere, DisplayName = "Damage", meta = (ClampMin = "0", ClampMax = "10"))
		int mDamage = 1;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Time of Life", meta = (ClampMin = "0", ClampMax = "60"))
		float mLifeTime = 3.0f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Fall Off", meta = (ClampMin = "0", ClampMax = "1"))
		float mFallOff = 0.1f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Can Bounce Of Walls")
		bool bCanBounce = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Can Step On It")
		bool bCanStepOnIt = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Should Be Destroyed On Contact")
		bool bShouldBeDestroyedOncontact = true;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Projectile Max Speed", meta = (ClampMin = "0", ClampMax = "10000"))
		float mProjectileMaxSpeed = 3000.0f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Projectile Init Speed", meta = (ClampMin = "0", ClampMax = "10000"))
		float mProjectileInitSpeed = 3000.0f;
};

UCLASS(config=Game)
class ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABaseProjectile();

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ProjectileMesh;

	//
	UFUNCTION(BlueprintNativeEvent)
		void DoWhenDestroyed();

	// STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		int GetDamage();

	//
	UFUNCTION(BlueprintCallable)
		void SetDamage(int newDamage);

	//
	UFUNCTION(BlueprintCallable)
		float GetLifeTime();
	
	//
	UFUNCTION(BlueprintCallable)
		void SetLifeTime(float newTimeOfLife);

	//
	UFUNCTION(BlueprintCallable)
		float GetFallOff();

	//
	UFUNCTION(BlueprintCallable)
		void SetFallOff(float newFallOff);

	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanBounce();

	//
	UFUNCTION(BlueprintCallable)
		void SetCanBounce(bool newShouldBounce = true);

	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanStepOnIt();

	//
	UFUNCTION(BlueprintCallable)
		void SetCanStepOnIt(bool newCanStepOnIt = true);

	//
	UFUNCTION(BlueprintCallable)
		bool CheckShouldBeDestroyedOncontact();

	//
	UFUNCTION(BlueprintCallable)
		void SetShouldBeDestroyedOncontact(bool newShouldBeDestroyedOnContact = true);

	//
	UFUNCTION(BlueprintCallable)
		float GetProjectileMaxSpeed();

	//
	UFUNCTION(BlueprintCallable)
		void SetProjectileMaxSpeed(float newProjectileMaxSpeed);

	//
	UFUNCTION(BlueprintCallable)
		float GetProjectileInitSpeed();

	//
	UFUNCTION(BlueprintCallable)
		void SetProjectileInitSpeed(float newProjectileInitSpeed);

	//////////////////////////////////////////////////////////////////////////

	// DEFAULT (UE4) //////////////////////////////////////////////////////////////////////////

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, Category = Projectile)
		class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	//////////////////////////////////////////////////////////////////////////

protected:
	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Projectile Properties"))
		FProjectileProperties PtProperties;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//
	UFUNCTION()
		void SetupPtProperties();

	//
	UFUNCTION()
		void DestroyByTime();
};

