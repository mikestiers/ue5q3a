// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCounter.generated.h"

class UTextBlock;

UCLASS()
class UE5CPPTEST_API UAmmoCounter : public UUserWidget
{

	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) // meta makes sure the component names match in the blueprint  // relates to q3a_charcter->uninventorycomponent
	UTextBlock* CurrentAmmoText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ReserveAmmoText;

	UFUNCTION()
	void OnCharacterChangedWeapon(TSubclassOf<AWeapon> Weapon, int32 CurrentAmmo, int32 ReserveAmmo);

	UFUNCTION()
	void OnFireCurrentWeapon(TSubclassOf<AWeapon> Weapon, int32 CurrentAmmo);
};
