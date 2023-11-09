// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeapon.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.h"

void APickupWeapon::ApplyPickUp(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter && PlayerCharacter->InventoryComponent)
	{
		PlayerCharacter->InventoryComponent->AddWeapon(WeaponClass);
	}
}
