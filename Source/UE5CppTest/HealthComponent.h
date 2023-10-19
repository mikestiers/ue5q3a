// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class UE5CPPTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
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
	void TakeDamage(float DamageAmount);

	void Died();

	UFUNCTION()
	void OnDeathComplete();

};
