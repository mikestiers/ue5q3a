// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainMenuButton.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Overlay.h"
#include "SettingsMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnButtonClickedDelegate.AddDynamic(this, &UMainMenuWidget::OnPlayButtonClicked);
	SettingsButton->OnButtonClickedDelegate.AddDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	QuitButton->OnButtonClickedDelegate.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	SettingsMenu->BackButton->OnButtonClickedDelegate.AddDynamic(this, &UMainMenuWidget::OnSettingsBackButtonClicked);
}

void UMainMenuWidget::OnPlayButtonClicked()
{
	// open level
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelToOpen);
}

void UMainMenuWidget::OnSettingsButtonClicked()
{
	MainMenuSwitcher->SetActiveWidget(SettingsMenu);
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMainMenuWidget::OnSettingsBackButtonClicked()
{
	MainMenuSwitcher->SetActiveWidget(MainMenuOverlay);
}
