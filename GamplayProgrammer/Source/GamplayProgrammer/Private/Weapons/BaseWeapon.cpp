/// @author: Victor de Castro Hurtado

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

	SetupWpProperties();

	OwnerAsCharacter = dynamic_cast<ABaseCharacter*>(GetOwner());
}

ABaseCharacter * UWeaponComponent::GetOwnerAsCharacter()
{
	return OwnerAsCharacter;
}

void UWeaponComponent::SetupWpProperties()
{
	SetCurrentAmmoPrimary(GetMaxAmmoPrimary());
	SetCurrentAmmoSecondary(GetMaxAmmoSecondary());
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

bool UWeaponComponent::CheckIsValidCurrentAmmo()
{
	return WpProperties.CurrentProjectile.ProjectileType != EProjectileTypes::E_LAST;
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
	return WpProperties.CurrentProjectile == WpProperties.PrimaryProjectile;
}

TSubclassOf<class ABaseProjectile> UWeaponComponent::GetProjectileToSpawn()
{
	return WpProperties.CurrentProjectile.ProjectileToSpawn;
}

USoundBase* UWeaponComponent::GetFireSound()
{
	return WpProperties.CurrentProjectile.FireSound;
}

UAnimMontage * UWeaponComponent::GetFireAnimation()
{
	return WpProperties.CurrentProjectile.FireAnimation;
}

void UWeaponComponent::SetProjectileToSpawn(TSubclassOf<class ABaseProjectile> newProjectileToSpawn)
{
	WpProperties.CurrentProjectile.ProjectileToSpawn = newProjectileToSpawn;
}

float UWeaponComponent::GetZoomInSpeedMux()
{
	return WpProperties.CurrentProjectile.mZoomInSpeedMux;
}

int UWeaponComponent::GetMaxAmmoCurrent()
{
	return WpProperties.CurrentProjectile.mMaxAmmo;
}

int UWeaponComponent::GetMaxAmmoPrimary()
{
	return WpProperties.PrimaryProjectile.mMaxAmmo;
}

int UWeaponComponent::GetMaxAmmoSecondary()
{
	return WpProperties.SecondaryProjectile.mMaxAmmo;
}

int UWeaponComponent::GetCurrentAmmo()
{
	return WpProperties.CurrentProjectile.mCurrentAmmo;
}

int UWeaponComponent::GetCurrentAmmoPrimary()
{
	return WpProperties.PrimaryProjectile.mCurrentAmmo;
}

int UWeaponComponent::GetCurrentAmmoSecondary()
{
	return WpProperties.SecondaryProjectile.mCurrentAmmo;
}

void UWeaponComponent::SetCurrentAmmo(int newCurrentAmmo)
{
	WpProperties.CurrentProjectile.mCurrentAmmo = newCurrentAmmo;
	if (newCurrentAmmo == 0)
	{
		DoWhenAmmoIsEmpty();
	}
}

void UWeaponComponent::SetCurrentAmmoPrimary(int newCurrentAmmo)
{
	WpProperties.PrimaryProjectile.mCurrentAmmo = newCurrentAmmo;
}

void UWeaponComponent::SetCurrentAmmoSecondary(int newCurrentAmmo)
{
	WpProperties.SecondaryProjectile.mCurrentAmmo = newCurrentAmmo;
}

int UWeaponComponent::GetAmmoPerShot()
{
	return WpProperties.CurrentProjectile.mAmmoPerShot;
}

void UWeaponComponent::SetAmmoPerShot(int newAmmoPerShot)
{
	WpProperties.CurrentProjectile.mAmmoPerShot = newAmmoPerShot;
}

float UWeaponComponent::GetReloadTime()
{
	return WpProperties.CurrentProjectile.mReloadTime;
}

void UWeaponComponent::SetReloadTime(float newReloadTime)
{
	WpProperties.CurrentProjectile.mReloadTime = newReloadTime;
}

bool UWeaponComponent::CheckHaveEnoughAmmo()
{
	return GetAmmoPerShot() <= GetCurrentAmmo();
}

UCurveFloat* UWeaponComponent::GetFloatCurveZoomInDelay()
{
	return WpProperties.CurrentProjectile.FloatCurveZoomInDelay;
}

bool UWeaponComponent::CheckIsAmmoFull()
{
	return WpProperties.CurrentProjectile.mCurrentAmmo == WpProperties.CurrentProjectile.mMaxAmmo;
}

float UWeaponComponent::GetZoomInDelay()
{
	return WpProperties.CurrentProjectile.mZoomInDelay;
}

void UWeaponComponent::SetZoomInDelay(float newZoomInDelay)
{
	WpProperties.CurrentProjectile.mZoomInDelay = newZoomInDelay;
}

float UWeaponComponent::GetZoomInMux()
{
	return WpProperties.CurrentProjectile.mZoomInMux;
}

void UWeaponComponent::SetZoomInMux(float newZoomInMux)
{
	WpProperties.CurrentProjectile.mZoomInMux = newZoomInMux;
}

//////////////////////////////////////////////////////////////////////////

// MAIN ACTIONS //////////////////////////////////////////////////////////////////////////

void UWeaponComponent::ChangeAmmoToPrimary()
{
	WpProperties.CurrentProjectile = WpProperties.PrimaryProjectile;
}

void UWeaponComponent::ChangeAmmoToSecondary()
{
	WpProperties.CurrentProjectile = WpProperties.SecondaryProjectile;
}

void UWeaponComponent::ChangeAmmoType()
{
	if (CheckIsPrimaryAmmoType())
	{
		if (CheckIsValidSecondaryAmmo())
		{
			WpProperties.PrimaryProjectile.mCurrentAmmo = WpProperties.CurrentProjectile.mCurrentAmmo;
			ChangeAmmoToSecondary();
		}
	}
	else
	{
		if (CheckIsValidPrimaryAmmo())
		{
			WpProperties.SecondaryProjectile.mCurrentAmmo = WpProperties.CurrentProjectile.mCurrentAmmo;
			ChangeAmmoToPrimary();
		}
	}
}

void UWeaponComponent::Shoot(FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
	UWorld* const World = GetWorld();
	if (World)
	{
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		TSubclassOf<ABaseProjectile> TempProjectileToSpawn = GetProjectileToSpawn();
		if(TempProjectileToSpawn)
		{
			ABaseProjectile* ProjectileSpawned = World->SpawnActor<ABaseProjectile>(TempProjectileToSpawn, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (ProjectileSpawned)
			{
				ProjectileSpawned->SetBaseChOwner(OwnerAsCharacter);

				// try and play the sound if specified
				if (GetFireSound())
				{
					UGameplayStatics::PlaySoundAtLocation(this, GetFireSound(), OwnerAsCharacter->GetActorLocation());
				}

				// try and play a firing animation if specified
				if (GetFireAnimation())
				{
					// Get the animation object for the arms mesh
					if (OwnerAsCharacter)
					{
						UAnimInstance* AnimInstance = OwnerAsCharacter->GetMesh1P()->GetAnimInstance();
						if (AnimInstance)
						{
							AnimInstance->Montage_Play(GetFireAnimation(), 1.f);
						}
					}
				}

				DecreaseCurrentAmmo(GetAmmoPerShot());
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "WARNING: no Projectile Class assigned.");
		}
	}
}

void UWeaponComponent::IncreaseCurrentAmmo(int ammount)
{
	int newAmmoTemp = GetCurrentAmmo() + ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmoCurrent());
	SetCurrentAmmo(newAmmoTemp);
}

void UWeaponComponent::IncreasePrimaryAmmo(int ammount)
{
	int newAmmoTemp = GetCurrentAmmoPrimary() + ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmoPrimary());
	(newAmmoTemp);
}

void UWeaponComponent::IncreaseSecondaryAmmo(int ammount)
{
	int newAmmoTemp = GetCurrentAmmoSecondary() + ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmoSecondary());
	(newAmmoTemp);
}

void UWeaponComponent::DecreaseCurrentAmmo(int ammount)
{
	int newAmmoTemp = GetCurrentAmmo() - ammount;
	newAmmoTemp = FMath::Clamp(newAmmoTemp, 0, GetMaxAmmoCurrent());
	SetCurrentAmmo(newAmmoTemp);
}

void UWeaponComponent::RestoreFullAmmoCurrent()
{
	IncreaseCurrentAmmo(GetMaxAmmoCurrent());
}

void UWeaponComponent::RestoreFullAmmoPrimary()
{
	IncreasePrimaryAmmo(GetMaxAmmoPrimary());
}

void UWeaponComponent::RestoreFullAmmoSecondary()
{
	IncreaseSecondaryAmmo(GetMaxAmmoSecondary());
}

void UWeaponComponent::EmptyAmmo()
{
	DecreaseCurrentAmmo(GetMaxAmmoCurrent());
}

void UWeaponComponent::DoWhenAmmoIsEmpty()
{
	if (OwnerAsCharacter)
	{
		OwnerAsCharacter->StartReloading();
	}
}

//////////////////////////////////////////////////////////////////////////

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

