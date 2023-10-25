// Fill out your copyright notice in the Description page of Project Settings.


#include "Q3A_Character.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"

// Sets default values
AQ3A_Character::AQ3A_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void AQ3A_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQ3A_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQ3A_Character::MoveForward(const FInputActionValue& ActionValue)
{
	FVector direction = GetActorForwardVector();
	float directionValue = ActionValue.GetMagnitude();
	AddMovementInput(direction, directionValue);
}

void AQ3A_Character::MoveRight(const FInputActionValue& ActionValue)
{
	FVector direction = GetActorRightVector();
	float directionValue = ActionValue.GetMagnitude();
	AddMovementInput(direction, directionValue);
}

void AQ3A_Character::LookUp(const FInputActionValue& ActionValue)
{
	float DirectionValue = ActionValue.Get<float>();
	AddControllerPitchInput(DirectionValue);
}

void AQ3A_Character::LookRight(const FInputActionValue& ActionValue)
{
	float DirectionValue = ActionValue.Get<float>();
	AddControllerYawInput(DirectionValue);
}

void AQ3A_Character::Fire(const FInputActionValue& ActionValue)
{
	if (InventoryComponent)
	{
		InventoryComponent->FireCurrentWeapon();
	}
}

USkeletalMeshComponent* AQ3A_Character::GetCharacterMesh()
{
	return GetMesh();
}

