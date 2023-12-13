// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMainMenuButton::NativePreConstruct()
{
	if (ButtonTextBlock)
	{
		ButtonTextBlock->SetText(ButtonText);
	}
	Super::NativePreConstruct();
}

void UMainMenuButton::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind to Clicked event
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UMainMenuButton::OnButtonClicked);
	}
}

void UMainMenuButton::OnButtonClicked()
{
	OnButtonClickedDelegate.Broadcast();
}
