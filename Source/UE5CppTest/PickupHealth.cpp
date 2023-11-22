// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupHealth.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"

APickupHealth::APickupHealth()
{
	HealthAmount = 50.0f;
}

void APickupHealth::ApplyPickUp(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter && PlayerCharacter->HealthComponent)
	{
		PlayerCharacter->HealthComponent->Heal(HealthAmount);
	}
}
