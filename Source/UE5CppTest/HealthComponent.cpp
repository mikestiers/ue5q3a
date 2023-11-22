// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

// Sets default values
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	bDead = false;
	DeathTime = 3.0f;
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	if (!bDead)
	{
		CurrentHealth -= DamageAmount;
		
		if (CurrentHealth <= 0.0f)
		{
			Died();
		}
		OnDamageTakenDelegate.Broadcast(DamageAmount, CurrentHealth, MaxHealth);
	}
}

void UHealthComponent::Died()
{
	bDead = true;
	CurrentHealth = 0.0f;
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController()))
		{
			PlayerController->DisableInput(PlayerController);
			GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &UHealthComponent::OnDeathComplete, DeathTime, false);
		}
		else
		{
			// TODO: Add logic for AI character dies
		}
	}
}

void UHealthComponent::OnDeathComplete()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MapToLoadOnDeath, true, "");
}

void UHealthComponent::Heal(float HealAmount)
{
	if (!bDead)
	{
		CurrentHealth += HealAmount;
		CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
		OnHealDelegate.Broadcast(HealAmount, CurrentHealth, MaxHealth);
	}
}
