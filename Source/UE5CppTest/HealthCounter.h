// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthCounter.generated.h"

class UTextBlock;

UCLASS()
class UE5CPPTEST_API UHealthCounter : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;  // like onbeginplay but for widgets

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) // meta makes sure the component names match in the blueprint  // relates to q3a_charcter->uninventorycomponent
	UTextBlock* HealthText;

	UFUNCTION()
	void OnHealthChange(float Damage, float CurrentHealth, float MaxHealth);
};
