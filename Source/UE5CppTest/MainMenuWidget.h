// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UMainMenuButton;
class UWidgetSwitcher;
class USettingsMenuWidget;
class UOverlay;
/**
 * 
 */
UCLASS()
class UE5CPPTEST_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainMenuButton* PlayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainMenuButton* SettingsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainMenuButton* QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> LevelToOpen;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* MainMenuSwitcher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOverlay* MainMenuOverlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USettingsMenuWidget* SettingsMenu;

	UFUNCTION()
	void OnPlayButtonClicked();

	UFUNCTION()
	void OnSettingsButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnSettingsBackButtonClicked();
};
