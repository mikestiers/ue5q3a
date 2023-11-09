// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupAmmo.generated.h"

class AWeapon;

UCLASS()
class UE5CPPTEST_API APickupAmmo : public APickup
{
	GENERATED_BODY()
	
	APickupAmmo();

	void ApplyPickUp(APlayerCharacter* PlayerCharacter) override;

public:
	UPROPERTY(EditAnywhere)
	int32 AmmoAmount;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> AmmoType;
};
