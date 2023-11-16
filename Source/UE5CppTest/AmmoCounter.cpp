// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "Q3A_Character.h"
#include "InventoryComponent.h"
#include "Components/TextBlock.h"

void UAmmoCounter::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwningPlayerPawn()))
	{
		if (Character->InventoryComponent)
		{
			Character->InventoryComponent->OnWeaponChangeDelegate.AddUniqueDynamic(this, &UAmmoCounter::OnCharacterChangedWeapon);
			Character->InventoryComponent->OnFireCurrentWeaponDelegate.AddUniqueDynamic(this, &UAmmoCounter::OnFireCurrentWeapon);
		}
	}
}

void UAmmoCounter::OnCharacterChangedWeapon(TSubclassOf<AWeapon> Weapon, int32 CurrentAmmo, int32 ReserveAmmo)
{
	CurrentAmmoText->SetText(FText::AsNumber(CurrentAmmo));
	ReserveAmmoText->SetText(FText::AsNumber(ReserveAmmo));
}

void UAmmoCounter::OnFireCurrentWeapon(TSubclassOf<AWeapon> Weapon, int32 CurrentAmmo)
{
	CurrentAmmoText->SetText(FText::AsNumber(CurrentAmmo));
}
