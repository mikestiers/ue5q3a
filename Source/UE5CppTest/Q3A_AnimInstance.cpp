// Fill out your copyright notice in the Description page of Project Settings.


#include "Q3A_AnimInstance.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UQ3A_AnimInstance::UQ3A_AnimInstance()
{
	bIsHoldingWeapon = false;
	Speed = 0.0f;
	bIsFalling = false;
}

void UQ3A_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (AQ3A_Character* Character = Cast<AQ3A_Character>(TryGetPawnOwner()))
	{
		if (Character->InventoryComponent)
		{
			bIsHoldingWeapon = Character->InventoryComponent->GetCurrentWeapon() ? true : false;
		}

		Speed = Character->GetVelocity().Size();  // taking vector and converting it to float (this is magnitude)

		if (UCharacterMovementComponent* CharacterMovementComponent = Character->GetCharacterMovement())
		{
			bIsFalling = CharacterMovementComponent->IsFalling();
		}
	}
}
