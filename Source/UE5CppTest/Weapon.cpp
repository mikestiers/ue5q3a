// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Q3A_Character.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 10.0f;
	CameraRange = 10000.0f;
	FiringRate = 1.0f;
	CurrentAmmo = 10;
	bCanFire = true;
	AmmoMagazineCapacity = 10;
	SocketName = FName("GripPoint");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	check(SkeletalMeshComponent != nullptr)
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void AWeapon::TryFire()
{
	if (bCanFire && CurrentAmmo > 0)
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
	else if (ProjectileClass)
	{
		FireProjectile();
	}
	else
	{
		FireLineTrace();
	}
	if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwner()))
	{
		if (Character->InventoryComponent)
		{
			Character->InventoryComponent->OnFireCurrentWeapon(GetClass(), CurrentAmmo);
		}
	}
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation(), FRotator::ZeroRotator);
	}
}

void AWeapon::FireProjectile()
{
	if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwner()))
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = Character;
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SkeletalMeshComponent->GetSocketLocation("Muzzle"), Character->GetControlRotation(), ActorSpawnParameters);
		if (Projectile)
		{
			Projectile->Init(Damage);
		}
	}
}

void AWeapon::FireLineTrace()
{
	// Line trace #1 for camera
	FHitResult CameraHitResult = GetWeaponLineTrace(); // forward vector of the player * range

	// Line trace #2 for bullet from muzzle of gun
	FHitResult FireHitResult;
	FVector StartLocation = SkeletalMeshComponent->GetSocketLocation("Muzzle"); // point of the gun
	FVector FireDirection = (CameraHitResult.Location - StartLocation).GetSafeNormal();
	FVector EndLocation = (FireDirection * CameraRange) + StartLocation; // gun to target

	// i somehow know the variable or whatever that exists when i start the game

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(FireHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, CollisionQueryParams, FCollisionResponseParams());
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5, 0, 1);

	if (FireHitResult.IsValidBlockingHit())
	{
		if (AQ3A_Character* Character = Cast<AQ3A_Character>(FireHitResult.GetActor()))
		{
			if (Character->HealthComponent)
			{
				Character->HealthComponent->TakeDamage(Damage, GetOwner());
			}
			if (BloodParticleSystem)
			{
				FRotator BloodRotation = FireDirection.Rotation();
				BloodRotation.Yaw += 90.0f;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodParticleSystem, FireHitResult.ImpactPoint, BloodRotation, true);
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
	if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwner()))
	{
		if (Character->InventoryComponent)
		{
			int32 ReserveAmmo = Character->InventoryComponent->CheckAmmo(GetClass()); // GetClass() gets whatever the instance is ... StaticClass() would get the class of AWeapon.  Not what is needed
			if (CurrentAmmo < AmmoMagazineCapacity && ReserveAmmo > 0)
			{
				int32 RequiredAmmo = AmmoMagazineCapacity - CurrentAmmo;
				if (ReserveAmmo >= RequiredAmmo)
				{
					CurrentAmmo = AmmoMagazineCapacity;
					Character->InventoryComponent->SubtractAmmo(GetClass(), RequiredAmmo);
				}
				else
				{
					CurrentAmmo += ReserveAmmo;
					Character->InventoryComponent->SubtractAmmo(GetClass(), ReserveAmmo); // use up everything 
				}
			}
		}
	}
}

FHitResult AWeapon::GetWeaponLineTrace()
{
	FHitResult HitResult;
	FVector StartLocation;
	FVector EndLocation;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.AddIgnoredActor(this);


	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		StartLocation = PlayerCharacter->CameraComponent->GetComponentLocation();
		EndLocation = StartLocation + (PlayerCharacter->CameraComponent->GetForwardVector() * CameraRange);
		
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, CollisionQueryParams, FCollisionResponseParams());
	}
	else if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetOwner()))
	{
		StartLocation = EnemyCharacter->GetActorLocation();
		EndLocation = StartLocation + (EnemyCharacter->GetControlRotation().Vector() * CameraRange);

		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, CollisionQueryParams, FCollisionResponseParams());

	}

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5, 0, 1);
	
	return HitResult;
}

