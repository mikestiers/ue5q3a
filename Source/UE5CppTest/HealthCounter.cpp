// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthCounter.h"
#include "Q3A_Character.h"
#include "HealthComponent.h"
#include "Components/TextBlock.h"

void UHealthCounter::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AQ3A_Character* Character = Cast<AQ3A_Character>(GetOwningPlayerPawn()))
	{
		if (Character->HealthComponent)
		{
			Character->HealthComponent->OnDamageTakenDelegate.AddUniqueDynamic(this, &UHealthCounter::OnHealthChange);
			Character->HealthComponent->OnHealDelegate.AddUniqueDynamic(this, &UHealthCounter::OnHealthChange);
		}
	}
}

void UHealthCounter::OnHealthChange(float Damage, float CurrentHealth, float MaxHealth) // these params come from the delegate in healthcomponent.h
{
	if (HealthText)
	{
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::RoundToInt(CurrentHealth))));
	}
}
