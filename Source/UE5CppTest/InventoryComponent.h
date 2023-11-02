// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;
class AQ3A_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5CPPTEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AWeapon>> StartingWeapons;
	
	UPROPERTY()
	TArray<AWeapon*> Weapons;

	UPROPERTY()
	int32 CurrentWeaponIndex;

	UPROPERTY()
	int32 MaxWeapons;

	UPROPERTY()
	AQ3A_Character* Character;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupStartingWeapons();

public:	
	void FireCurrentWeapon();

	void ReloadCurrentWeapon();

	void SelectNextWeapon();

	void SelectPreviousWeapon();

	void SelectWeaponByIndex(int32 index);

	AWeapon* GetCurrentWeapon();
};
