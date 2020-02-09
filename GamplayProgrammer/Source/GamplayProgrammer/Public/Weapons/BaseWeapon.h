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
	UPROPERTY(EditAnywhere, DisplayName = "Projectile To Spawn")
		TSubclassOf<class ABaseProjectile> ProjectileToSpawn;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Fire Sound")
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Fire Animation")
		class UAnimMontage* FireAnimation;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Max Ammo", meta = (ClampMin = "0", ClampMax = "100"))
		int mMaxAmmo = 100;

	//
	UPROPERTY(VisibleAnywhere, DisplayName = "Current Ammo")
		int mCurrAmmo;

	//
	UPROPERTY(EditAnywhere, DisplayName = "Ammo Per Shot")
		int mAmmoPerShot = 1;

	//
	UPROPERTY(EditAnywhere, DisplayName = "ReloadTime", meta = (ClampMin = "0", ClampMax = "10"))
		float mReloadTime = 2.0f;

	//
	UPROPERTY(EditAnywhere, DisplayName = "ZoomIn Delay Curve")
		UCurveFloat* FloatCurveZoomInDelay;

	// 0.1 = max slow down when zooming in
	// 1.0 = no slow down when zooming in
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn Speed", meta = (ClampMin = "0.1", ClampMax = "1"))
		float mZoomInSpeedMux = 0.2f;

	// 0.0 = no zoom
	// 0.9 = max zoom
	UPROPERTY(EditAnywhere, DisplayName = "Mux ZoomIn", meta = (ClampMin = "0", ClampMax = "0.9"))
		float mZoomInMux = 0.4f;

	// 0.0 = instant zoom in
	// 2.0 = it'll take 2 secs to zoom in
	UPROPERTY(EditAnywhere, DisplayName = "ZoomIn Delay", meta = (ClampMin = "0", ClampMax = "2"))
		float mZoomInDelay = 0.2f;

	// all properties (except current ammo) must be the same to consider two weapons the same weapon
	bool operator==(const FAmmoProperties& other) const 
	{
		return (ProjectileType == other.ProjectileType) && (mMaxAmmo == other.mMaxAmmo) && 
			(mAmmoPerShot == other.mAmmoPerShot) && (mReloadTime == other.mReloadTime) && (mZoomInMux == other.mZoomInMux);
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

	//
	UFUNCTION(BlueprintCallable)
		ABaseCharacter* GetOwnerAsCharacter();

	// WEAPON PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsValidCurrAmmo();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsPrimaryAmmoType();

	//
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class ABaseProjectile> GetProjectileToSpawn();

	//
	UFUNCTION(BlueprintCallable)
		USoundBase* GetFireSound();

	//
	UFUNCTION(BlueprintCallable)
		UAnimMontage* GetFireAnimation();

	//
	UFUNCTION(BlueprintCallable)
		void SetProjectileToSpawn(TSubclassOf<class ABaseProjectile> newProjectileToSpawn);

	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInSpeedMux();

	//
	UFUNCTION(BlueprintCallable)
		int GetMaxAmmo();

	//
	UFUNCTION(BlueprintCallable)
		int GetCurrAmmo();

	//
	UFUNCTION(BlueprintCallable)
		int GetAmmoPerShot();

	//
	UFUNCTION(BlueprintCallable)
		void SetAmmoPerShot(int newAmmoPerShot = 1);

	//
	UFUNCTION(BlueprintCallable)
		float GetReloadTime();

	//
	UFUNCTION(BlueprintCallable)
		void SetReloadTime(float newReloadTime);

	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInDelay();

	//
	UFUNCTION(BlueprintCallable)
		void SetZoomInDelay(float newZoomInDelay);

	//
	UFUNCTION(BlueprintCallable)
		float GetZoomInMux();

	//
	UFUNCTION(BlueprintCallable)
		void SetZoomInMux(float newZoomInMux);

	//
	UFUNCTION(BlueprintCallable)
		bool CheckIsAmmoFull();

	//
	UFUNCTION(BlueprintCallable)
		bool CheckHaveEnoughAmmo();

	//////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION()
		UCurveFloat* GetFloatCurveZoomInDelay();

	// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

	//
	UFUNCTION()
		void ChangeAmmoType();

	//
	UFUNCTION()
		void Shoot(FVector const& SpawnLocation, FRotator const& SpawnRotation);

	//
	UFUNCTION(BlueprintCallable)
		void IncreaseCurrAmmo(int ammount);

	//
	UFUNCTION(BlueprintCallable)
		void DecreaseCurrAmmo(int ammount);

	//
	UFUNCTION(BlueprintCallable)
		void RestoreFullAmmo();

	//
	UFUNCTION(BlueprintCallable)
		void EmptyAmmo();

	//
	UFUNCTION(BlueprintCallable)
		void DoWhenAmmoIsEmpty();

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
	UPROPERTY()
		ABaseCharacter* OwnerAsCharacter;

	//
	UFUNCTION()
		void SetupWpProperties();

	// we set this private to avoid problems
	UFUNCTION()
		void SetCurrAmmo(int newCurrAmmo);

	//
	UFUNCTION()
		void ChangeAmmoToSecondary();

	//
	UFUNCTION()
		void ChangeAmmoToPrimary();

};
