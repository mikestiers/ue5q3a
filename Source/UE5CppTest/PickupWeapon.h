// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupWeapon.generated.h"

class AWeapon;

UCLASS()
class UE5CPPTEST_API APickupWeapon : public APickup
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	void ApplyPickUp(APlayerCharacter* PlayerCharacter) override;
};
