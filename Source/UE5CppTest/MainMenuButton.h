// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class UE5CPPTEST_API UMainMenuButton : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClickedDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ButtonTextBlock;

	UPROPERTY(EditAnywhere)
	FText ButtonText;

	UFUNCTION()
	void OnButtonClicked();
};
