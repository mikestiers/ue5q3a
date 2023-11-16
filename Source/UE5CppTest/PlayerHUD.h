// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE5CPPTEST_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

	APlayerHUD();

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HudWidget;
	
	virtual void BeginPlay() override;
};
