// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;
class AQ3A_Character;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponChangeDelegate, TSubclassOf<AWeapon>, Weapon, int32, CurrentAmmo, int32, ReserveAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFireCurrentWeaponDelegate, TSubclassOf<AWeapon>, Weapon, int32, CurrentAmmo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5CPPTEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnWeaponChangeDelegate OnWeaponChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnFireCurrentWeaponDelegate OnFireCurrentWeaponDelegate;

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

	UFUNCTION()
	void AddAmmo(TSubclassOf<AWeapon> AmmoType, int32 AmmoAmount);

	UFUNCTION()
	int32 CheckAmmo(TSubclassOf<AWeapon> AmmoType);

	UFUNCTION()
	void SubtractAmmo(TSubclassOf<AWeapon> AmmoType, int32 AmmoAmount);

	UFUNCTION()
	void SetupStartingWeapons();

	UFUNCTION()
	void AddWeapon(TSubclassOf<AWeapon> WeaponClass);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<TSubclassOf<AWeapon>, int32> AmmoMap;

public:	
	void FireCurrentWeapon();

	void ReloadCurrentWeapon();

	void SelectNextWeapon();

	void SelectPreviousWeapon();

	void SelectWeaponByIndex(int32 index);

	AWeapon* GetCurrentWeapon();

	void OnFireCurrentWeapon(TSubclassOf<AWeapon> Weapon, int32 CurrentAmmo);
};
