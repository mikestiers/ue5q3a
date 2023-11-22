// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamageTakenDelegate, float, Damage, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealDelegate, float, HealAmount, float, CurrentHealth, float, MaxHealth);

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class UE5CPPTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintAssignable)
	FOnDamageTakenDelegate OnDamageTakenDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealDelegate OnHealDelegate;

	UHealthComponent();
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxHealth;
	UPROPERTY(BlueprintReadOnly)
	bool bDead;
	UPROPERTY(EditAnywhere)
	float DeathTime;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MapToLoadOnDeath;
	FTimerHandle DeathTimerHandle;

public:	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);

	void Died();

	UFUNCTION()
	void OnDeathComplete();

	UFUNCTION()
	void Heal(float HealAmount);

};
