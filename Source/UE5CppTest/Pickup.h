// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class APlayerCharacter;

UCLASS()
class UE5CPPTEST_API APickup : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickup();

	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	bool bCanPickup;

	UPROPERTY(EditAnywhere)
	float RespawnTime;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	FTimerHandle PickupTimerHandle;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	virtual void ApplyPickUp(APlayerCharacter* PlayerCharacter);

	UFUNCTION()
	void PickupTimerHandleComplete();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
