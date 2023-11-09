// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupAmmo.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

APickupAmmo::APickupAmmo()
{
	AmmoAmount = 10; //change in blueprint
}

void APickupAmmo::ApplyPickUp(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter && PlayerCharacter->InventoryComponent)
	{
		PlayerCharacter->InventoryComponent->AddAmmo(AmmoType, AmmoAmount);
	}

}
