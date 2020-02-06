// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TimerManager.h>
#include "BaseProjectile.generated.h"

class UStaticMeshComponent;
class ABaseCharacter;

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
	UPROPERTY(VisibleAnywhere, DisplayName = "Time of Life Remaining")
		float mLifeTimeRemaining;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Fall Off", meta = (ClampMin = "0", ClampMax = "1"))
		float mFallOff = 0.1f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Can Bounce Of Walls")
		bool bCanBounce = false;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Bounces", meta = (ClampMin = "0", ClampMax = "10", EditCondition = "bCanBounce"))
		int mMaxBounces = 1;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Curr Bounces")
		int mCurrBounces;

	// time to add to lifespan after a bounce
	UPROPERTY(EditAnywhere, DisplayName = "Extra Time Per Bounce", meta = (ClampMin = "0", ClampMax = "5", EditCondition = "bCanBounce"))
		float mExtraTimePerBounce = 1.0f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Can Do Damage To Owner")
		bool bCanSelfDamage = false;

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
	UFUNCTION()
		void SetBaseChOwner(ABaseCharacter* newBaseChOwner);

	//
	UFUNCTION(BlueprintCallable)
		ABaseCharacter* GetBaseChOwner();

	// each implementation must be done in blueprint, so design can iterate over it easily
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
		float GetLifeTimeRemaining();

	//
	UFUNCTION(BlueprintCallable)
		void SetLifeTimeRemaining(float newTimeOfLifeRemaining);

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
		int GetMaxBounces();

	//
	UFUNCTION(BlueprintCallable)
		void SetMaxBounces(int newMaxBounces = 1);

	//
	UFUNCTION(BlueprintCallable)
		int GetCurrBounces();

	//
	UFUNCTION(BlueprintCallable)
		float GetExtraTimePerBounce();

	//
	UFUNCTION(BlueprintCallable)
		void SetExtraTimePerBounce(float newExtraTimePerBounce = 1);

	//
	UFUNCTION(BlueprintCallable)
		bool CheckCanSelfDamage();

	//
	UFUNCTION(BlueprintCallable)
		void SetCanSelfDamage(bool newCanSelfDamage = true);

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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	UPROPERTY()
		ABaseCharacter* BaseChOwner;

	//
	UFUNCTION()
		void SetupPtProperties();

	//
	UPROPERTY()
		FTimerHandle AutoDestroyHandle;

	//
	FTimerDelegate AutoDestroyDelegate;

	//
	UFUNCTION()
		void StartAutodestroyTimer();

	//
	UFUNCTION()
		void DestroyByTime();

	//
	UFUNCTION()
		void SetCurrBounces(int newCurrBounces = 1);
};

