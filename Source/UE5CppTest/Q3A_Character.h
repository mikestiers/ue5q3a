// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Q3A_Character.generated.h"

class UHealthComponent;
class UInventoryComponent;
class AWeapon;

UCLASS()
class UE5CPPTEST_API AQ3A_Character : public ACharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) // technically blueprintreadonly not needed
	UInventoryComponent* InventoryComponent;

public:
	// Sets default values for this character's properties
	AQ3A_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(const FInputActionValue& ActionValue);

	void MoveRight(const FInputActionValue& ActionValue);

	void LookUp(const FInputActionValue& ActionValue);

	void LookRight(const FInputActionValue& ActionValue);

	void Fire(const FInputActionValue& ActionValue);

	void WeaponSwitch(const FInputActionValue& ActionValue);

	virtual USkeletalMeshComponent* GetCharacterMesh();
};
