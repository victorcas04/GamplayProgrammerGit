// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "Components/AudioComponent.h"
#include "Components/ActorComponent.h"
#include "BaseWeapon.generated.h"

USTRUCT()
struct FAmmoProperties
{
	GENERATED_BODY()

public:
	//
	UPROPERTY(EditAnywhere, DisplayName = "Ammo Type")
		EProjectileTypes ProjectileType = EProjectileTypes::E_NORMAL;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Ammo", meta = (ClampMin = "0", ClampMax = "100"))
		int mMaxAmmo = 100;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Ammo")
		int mCurrAmmo;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Ammo Per Shot")
		int mAmmoPerShot = 1;

	bool operator==(const FAmmoProperties& other) const 
	{
		return (ProjectileType == other.ProjectileType) && (mMaxAmmo == other.mMaxAmmo) && (mAmmoPerShot == other.mAmmoPerShot);
	}

};

USTRUCT()
struct FWeaponProperties
{
	GENERATED_BODY()

public:

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Ammo Type")
		FAmmoProperties CurrProjectile;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Primary Ammo Type")
		FAmmoProperties PrimaryProjectile;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Secondary Ammo Type")
		FAmmoProperties SecondaryProjectile;
	
};

UCLASS(Blueprintable, BlueprintType, config = Game, meta=(BlueprintSpawnableComponent))
class GAMPLAYPROGRAMMER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// Sets default values for this component's properties
	UWeaponComponent();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UAnimMontage* FireAnimation;

	// WEAPON PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsValidCurrAmmo();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsPrimaryAmmoType();

	//////////////////////////////////////////////////////////////////////////

	// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		void SetCurrAmmoToSecondary();

	//
	UFUNCTION(BlueprintCallable)
		void SetCurrAmmoToPrimary();

	//
	UFUNCTION(BlueprintCallable)
		void ChangeAmmoType();

	//
	UFUNCTION(BlueprintCallable)
		void Shoot();

	//////////////////////////////////////////////////////////////////////////

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	//
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Base Weapon Properties"))
		FWeaponProperties WpProperties;

	// WEAPON PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsValidPrimaryAmmo();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsValidSecondaryAmmo();

	// Called when the game starts
	virtual void BeginPlay() override;

	//////////////////////////////////////////////////////////////////////////

private:

	//
	UFUNCTION()
		void SetupWpProperties();
	
};
