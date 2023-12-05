// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDamageTakenDelegate, float, Damage, float, CurrentHealth, float, MaxHealth, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealDelegate, float, HealAmount, float, CurrentHealth, float, MaxHealth, AActor*, Instigator);

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
	void TakeDamage(float DamageAmount, AActor* Instigator);

	void Died();

	UFUNCTION()
	void OnDeathComplete();

	UFUNCTION()
	void Heal(float HealAmount);

};
