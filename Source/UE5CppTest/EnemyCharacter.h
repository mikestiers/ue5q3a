// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Q3A_Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class UE5CPPTEST_API AEnemyCharacter : public AQ3A_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensingComponent;


protected:
	// CalleyCd when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
