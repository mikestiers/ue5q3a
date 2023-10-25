// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "Q3A_Character.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AQ3A_Character>(GetOwner());
	SetupStartingWeapons();
}

void UInventoryComponent::SetupStartingWeapons()
{
	for (int32 i = 0; i < StartingWeapons.Num(); i++)
	{
		AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(StartingWeapons[i], GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		
		if (Weapon && Character)
		{
			Weapon->SetOwner(Character);
			FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetCharacterMesh(), AttachmentTransformRules, Weapon->SocketName);
			Weapons.Add(Weapon);
		}


	}
}

void UInventoryComponent::FireCurrentWeapon()
{
	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		Weapons[CurrentWeaponIndex]->Fire();
	}
}

void UInventoryComponent::ReloadCurrentWeapon()
{
	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		//Weapons[CurrentWeaponIndex]->Reload();
	}
}

void UInventoryComponent::SelectNextWeapon()
{
	if (Weapons.Num() > 1)
	{
		CurrentWeaponIndex++;
		if (CurrentWeaponIndex >= Weapons.Num())
		{
			CurrentWeaponIndex = 0;
		}
	}
}

void UInventoryComponent::SelectPreviousWeapon()
{
	if (Weapons.Num() > 1) // if more than one weapon you have to select the next weapon
	{
		CurrentWeaponIndex--;
		if (CurrentWeaponIndex < 0)
		{
			CurrentWeaponIndex = Weapons.Num() - 1;
		}
	}
}

AWeapon* UInventoryComponent::GetCurrentWeapon()
{
	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		return Weapons[CurrentWeaponIndex];
	}
	return nullptr;
}

