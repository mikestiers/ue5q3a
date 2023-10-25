// Fill out your copyright notice in the Description page of Project Settings.


#include "Q3A_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Q3A_Character.h"

void AQ3A_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    // Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        // PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
        Subsystem->ClearAllMappings();

        // Add each mapping context, along with their priority values. Higher values outprioritize lower values.
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

    // Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
    if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // There are ways to bind a UInputAction* to a handler function and multiple types of ETriggerEvent that may be of interest.

        // This calls the handler function on the tick when MyInputAction starts, such as when pressing an action button.
        if (MoveForwardAction)
        {
            PlayerEnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AQ3A_PlayerController::MoveForward);
        }

        if (MoveRightAction)
        {
            PlayerEnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AQ3A_PlayerController::MoveRight);
        }

        if (LookUpAction)
        {
            PlayerEnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AQ3A_PlayerController::LookUp);
        }

        if (LookRightAction)
        {
            PlayerEnhancedInputComponent->BindAction(LookRightAction, ETriggerEvent::Triggered, this, &AQ3A_PlayerController::LookRight);
        }

        if (FireAction)
        {
            PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AQ3A_PlayerController::Fire);
        }
    }
}

void AQ3A_PlayerController::MoveForward(const FInputActionValue& ActionValue)
{
    if (Q3ACharacter)
    {
        Q3ACharacter->MoveForward(ActionValue);
    }
}

void AQ3A_PlayerController::MoveRight(const FInputActionValue& ActionValue)
{
    if (Q3ACharacter)
    {
        Q3ACharacter->MoveRight(ActionValue);
    }
}

void AQ3A_PlayerController::LookUp(const FInputActionValue& ActionValue)
{
    if (Q3ACharacter)
    {
        Q3ACharacter->LookUp(ActionValue);
    }
}

void AQ3A_PlayerController::LookRight(const FInputActionValue& ActionValue)
{
    if (Q3ACharacter)
    {
        Q3ACharacter->LookRight(ActionValue);
    }
}

void AQ3A_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    Q3ACharacter = Cast<AQ3A_Character>(InPawn);
}

void AQ3A_PlayerController::Fire(const FInputActionValue& ActionValue)
{
    if (Q3ACharacter)
    {
        Q3ACharacter->Fire(ActionValue);
    }
}
