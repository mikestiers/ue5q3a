// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"

APlayerHUD::APlayerHUD()
{

}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetClass != nullptr)
	{
		HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	}
	
	if (HudWidget != nullptr)
	{
		HudWidget->AddToViewport(0); // default is zero
	}

}
