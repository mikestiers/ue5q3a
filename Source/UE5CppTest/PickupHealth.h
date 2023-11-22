// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupHealth.generated.h"


UCLASS()
class UE5CPPTEST_API APickupHealth : public APickup
{
	GENERATED_BODY()

	APickupHealth();

	void ApplyPickUp(APlayerCharacter* PlayerCharacter) override;

public:
	UPROPERTY(EditAnywhere)
	float HealthAmount;
};
