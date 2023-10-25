// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Q3A_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5CPPTEST_API UQ3A_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UQ3A_AnimInstance();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingWeapon;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
