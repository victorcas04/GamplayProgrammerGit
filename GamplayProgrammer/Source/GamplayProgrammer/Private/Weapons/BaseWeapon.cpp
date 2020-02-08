// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
// include for screen messages
#include "Runtime/Engine/Public/Engine.h"

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

	SetupWpProperties();
}

void UWeaponComponent::SetupWpProperties()
{
	
	if (CheckIsValidPrimaryAmmo())
	{
		SetCurrAmmoToPrimary();
	}
	else if (CheckIsValidSecondaryAmmo())
	{
		SetCurrAmmoToSecondary();
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

//////////////////////////////////////////////////////////////////////////

// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

void UWeaponComponent::SetCurrAmmoToPrimary()
{
	WpProperties.CurrProjectile = WpProperties.PrimaryProjectile;
}

void UWeaponComponent::SetCurrAmmoToSecondary()
{
	WpProperties.CurrProjectile = WpProperties.SecondaryProjectile;
}

void UWeaponComponent::ChangeAmmoType()
{
	if (CheckIsPrimaryAmmoType())
	{
		if (CheckIsValidSecondaryAmmo())
		{
			SetCurrAmmoToSecondary();
		}
	}
	else
	{
		if (CheckIsValidPrimaryAmmo())
		{
			SetCurrAmmoToPrimary();
		}
	}
}

void UWeaponComponent::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "SHOOTING...");
}

//////////////////////////////////////////////////////////////////////////

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

