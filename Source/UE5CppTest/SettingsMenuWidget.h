// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenuWidget.generated.h"

class UMainMenuButton;
class USlider;
/**
 * 
 */

UCLASS()
class UE5CPPTEST_API USettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainMenuButton* BackButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider* VolumeSlider;

	UFUNCTION()
	void OnVolumeSliderValueChanged(float Value);
};
