// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
// include for screen messages
#include "Runtime/Engine/Public/Engine.h"

#include "BaseCharacter.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//
	SetupWpProperties();
}

void UWeaponComponent::SetupWpProperties()
{
	SetCurrAmmo(GetMaxAmmo());
	if (CheckIsValidPrimaryAmmo())
	{
		ChangeAmmoToPrimary();
	}
	else if (CheckIsValidSecondaryAmmo())
	{
		ChangeAmmoToSecondary();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ERROR: no Valid Ammo Type assigned on weapon.");
	}
}

// WEAPON PROPERTIES STRUCT GETS AND SETS //////////////////////////////////////////////////////////////////////////

bool UWeaponComponent::CheckIsValidCurrAmmo()
{
	return WpProperties.CurrProjectile.ProjectileType != EProjectileTypes::E_LAST;
}

bool UWeaponComponent::CheckIsValidPrimaryAmmo()
{
	return WpProperties.PrimaryProjectile.ProjectileType != EProjectileTypes::E_LAST;
}

bool UWeaponComponent::CheckIsValidSecondaryAmmo()
{
	return WpProperties.SecondaryProjectile.ProjectileType != EProjectileTypes::E_LAST;
}

bool UWeaponComponent::CheckIsPrimaryAmmoType()
{
	return WpProperties.CurrProjectile == WpProperties.PrimaryProjectile;
}

TSubclassOf<class ABaseProjectile> UWeaponComponent::GetProjectileToSpawn()
{
	return WpProperties.CurrProjectile.ProjectileToSpawn;
}

void UWeaponComponent::SetProjectileToSpawn(TSubclassOf<class ABaseProjectile> newProjectileToSpawn)
{
	WpProperties.CurrProjectile.ProjectileToSpawn = newProjectileToSpawn;
}

float UWeaponComponent::GetZoomInSpeedMux()
{
	return WpProperties.CurrProjectile.mZoomInSpeedMux;
}

int UWeaponComponent::GetMaxAmmo()
{
	return WpProperties.CurrProjectile.mMaxAmmo;
}

int UWeaponComponent::GetCurrAmmo()
{
	return WpProperties.CurrProjectile.mCurrAmmo;
}

void UWeaponComponent::SetCurrAmmo(int newCurrAmmo)
{
	WpProperties.CurrProjectile.mCurrAmmo = newCurrAmmo;
	if (newCurrAmmo == 0)
	{
		DoWhenAmmoIsEmpty();
	}
}

int UWeaponComponent::GetAmmoPerShot()
{
	return WpProperties.CurrProjectile.mAmmoPerShot;
}

void UWeaponComponent::SetAmmoPerShot(int newAmmoPerShot)
{
	WpProperties.CurrProjectile.mAmmoPerShot = newAmmoPerShot;
}

float UWeaponComponent::GetReloadTime()
{
	return WpProperties.CurrProjectile.mReloadTime;
}

void UWeaponComponent::SetReloadTime(float newReloadTime)
{
	WpProperties.CurrProjectile.mReloadTime = newReloadTime;
}

bool UWeaponComponent::CheckHaveEnoughAmmo()
{
	return GetAmmoPerShot() <= GetCurrAmmo();
}

UCurveFloat* UWeaponComponent::GetFloatCurveZoomInDelay()
{
	return WpProperties.CurrProjectile.FloatCurveZoomInDelay;
}

bool UWeaponComponent::CheckIsAmmoFull()
{
	return WpProperties.CurrProjectile.mCurrAmmo == WpProperties.CurrProjectile.mMaxAmmo;
}

float UWeaponComponent::GetZoomInDelay()
{
	return WpProperties.CurrProjectile.mZoomInDelay;
}

void UWeaponComponent::SetZoomInDelay(float newZoomInDelay)
{
	WpProperties.CurrProjectile.mZoomInDelay = newZoomInDelay;
}

float UWeaponComponent::GetZoomInMux()
{
	return WpProperties.CurrProjectile.mZoomInMux;
}

void UWeaponComponent::SetZoomInMux(float newZoomInMux)
{
	WpProperties.CurrProjectile.mZoomInMux = newZoomInMux;
}

//////////////////////////////////////////////////////////////////////////

// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

void UWeaponComponent::ChangeAmmoToPrimary()
{
	WpProperties.CurrProjectile = WpProperties.PrimaryProjectile;
}

void UWeaponComponent::ChangeAmmoToSecondary()
{
	WpProperties.CurrProjectile = WpProperties.SecondaryProjectile;
}

void UWeaponComponent::ChangeAmmoType()
{
	if (CheckIsPrimaryAmmoType())
	{
		if (CheckIsValidSecondaryAmmo())
		{
			ChangeAmmoToSecondary();
		}
	}
	else
	{
		if (CheckIsValidPrimaryAmmo())
		{
			ChangeAmmoToPrimary();
		}
	}
}

void UWeaponComponent::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "SHOOTING...");
}

void UWeaponComponent::IncreaseCurrAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() + ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
}

void UWeaponComponent::DecreaseCurrAmmo(int ammount)
{
	int newAmmoTemp = GetCurrAmmo() - ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmo());
	SetCurrAmmo(newAmmoTemp);
}

void UWeaponComponent::RestoreFullAmmo()
{
	IncreaseCurrAmmo(GetMaxAmmo());
}

void UWeaponComponent::EmptyAmmo()
{
	DecreaseCurrAmmo(GetMaxAmmo());
}

void UWeaponComponent::DoWhenAmmoIsEmpty()
{
	ABaseCharacter* TempChOwner = dynamic_cast<ABaseCharacter*>(GetOwner());
	if (TempChOwner)
	{
		TempChOwner->StartReloading();
	}
}

//////////////////////////////////////////////////////////////////////////

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

