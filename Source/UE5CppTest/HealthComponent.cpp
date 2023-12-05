// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	bDead = false;
	DeathTime = 3.0f;
}

void UHealthComponent::TakeDamage(float DamageAmount, AActor* Instigator)
{
	if (!bDead)
	{
		CurrentHealth -= DamageAmount;
		
		if (CurrentHealth <= 0.0f)
		{
			Died();
		}
		OnDamageTakenDelegate.Broadcast(DamageAmount, CurrentHealth, MaxHealth, Instigator);
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
		else if (AAIController* AIController = Cast<AAIController>(Pawn->GetController()))
		{
			AIController->GetBrainComponent()->StopLogic("Dead");
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
		OnHealDelegate.Broadcast(HealAmount, CurrentHealth, MaxHealth, GetOwner());
	}
}
