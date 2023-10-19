// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Q3A_Character.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 10.0f;
	CameraRange = 10000.0f;
	FiringRate = 1.0f;
	CurrentAmmo = 10;
	ReserveAmmo = 20;
	MaxReserveAmmo = 100;
	bCanFire = true;
	AmmoMagazineCapacity = 10;
	SocketName = FName("GripPoint");

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	check(SkeletalMeshComponent != nullptr)
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void AWeapon::TryFire()
{
	if (bCanFire)
	{
		Fire();
	}
}

void AWeapon::Fire()
{
	bCanFire = false;
	CurrentAmmo--;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AWeapon::OnCanFireTimerComplete, FiringRate, false);
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
	if (ProjectileClass)
	{
		if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwner()))
		{
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), Character->GetControlRotation());
			if (Projectile)
			{
				Projectile->Init(Damage);
			}
		}
	}
	else
	{
		FHitResult FireHitResult = GetWeaponLineTrace();
		if (FireHitResult.IsValidBlockingHit())
		{
			if (AQ3A_Character* Character = Cast<AQ3A_Character>(FireHitResult.GetActor()))
			{
				if (Character->HealthComponent)
				{
					Character->HealthComponent->TakeDamage(Damage);
				}
			}
		}
	}
}

void AWeapon::OnCanFireTimerComplete()
{
	bCanFire = true;
}

void AWeapon::Reload()
{
	if (CurrentAmmo < AmmoMagazineCapacity && ReserveAmmo > 0)
	{
		int32 RequiredAmmo = AmmoMagazineCapacity - CurrentAmmo;
		if (ReserveAmmo >= RequiredAmmo)
		{
			CurrentAmmo = AmmoMagazineCapacity;
			ReserveAmmo -= RequiredAmmo;
		}
		else
		{
			CurrentAmmo += ReserveAmmo;
			ReserveAmmo = 0;
		}
	}
}

FHitResult AWeapon::GetWeaponLineTrace()
{
	FHitResult HitResult;
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		FVector StartLocation = PlayerCharacter->CameraComponent->GetComponentLocation();
		FVector EndLocation = StartLocation + (PlayerCharacter->CameraComponent->GetForwardVector() * CameraRange);
		
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, FCollisionQueryParams(), FCollisionResponseParams());
	}
	else if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetOwner()))
	{
		FVector StartLocation = EnemyCharacter->GetActorLocation();
		FVector EndLocation = StartLocation + (EnemyCharacter->GetControlRotation().Vector() * CameraRange);

		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, FCollisionQueryParams(), FCollisionResponseParams());

	}
		
	return HitResult;
}

