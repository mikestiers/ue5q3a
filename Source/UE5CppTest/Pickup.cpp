// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	check(Collider != nullptr);
	RootComponent = Collider;
	bCanPickup = true;
	RespawnTime = 30.0f;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	StaticMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		if (bCanPickup)
		{
			bCanPickup = false;
			if (StaticMesh)
			{
				StaticMesh->SetVisibility(false);
			}
			GetWorld()->GetTimerManager().SetTimer(PickupTimerHandle, this, &APickup::PickupTimerHandleComplete, RespawnTime, false);
			ApplyPickUp(PlayerCharacter);
		}
	}
}

void APickup::ApplyPickUp(APlayerCharacter* PlayerCharacter)
{

}

void APickup::PickupTimerHandleComplete()
{
	bCanPickup = true;
	StaticMesh->SetVisibility(true);
}

