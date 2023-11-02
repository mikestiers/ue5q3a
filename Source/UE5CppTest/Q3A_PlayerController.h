// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "InputAction.h"
//#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Q3A_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class AQ3A_Character;

/**
 * 
 */
UCLASS()
class UE5CPPTEST_API AQ3A_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere)
	UInputAction* LookUpAction;

	UPROPERTY(EditAnywhere)
	UInputAction* LookRightAction;

	UPROPERTY(EditAnywhere)
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere)
	UInputAction* WeaponSwitchAction;

	UPROPERTY()
	AQ3A_Character* Q3ACharacter;

	void SetupInputComponent() override;

	void MoveForward(const FInputActionValue& ActionValue);

	void MoveRight(const FInputActionValue& ActionValue);

	void LookUp(const FInputActionValue& ActionValue);

	void LookRight(const FInputActionValue& ActionValue);

	void OnPossess(APawn* InPawn) override;

	void Fire(const FInputActionValue& ActionValue);

	void WeaponSwitch(const FInputActionValue& ActionValue);
};
