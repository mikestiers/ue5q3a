// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuButton;
/**
 * 
 */
UCLASS()
class UE5CPPTEST_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

	AMainMenuHUD();

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* MainMenuWidget;

	virtual void BeginPlay() override;
};
