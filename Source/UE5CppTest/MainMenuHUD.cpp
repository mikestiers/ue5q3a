// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
