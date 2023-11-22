// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Q3A_Character.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AExplosion::Explode()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	TArray<AActor*> OverlappedActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), Radius, ObjectTypes, AActor::StaticClass(), TArray<AActor*>(), OverlappedActors);
	for (AActor* Actor : OverlappedActors)
	{
		if (AQ3A_Character* Character = Cast<AQ3A_Character>(Actor))
		{
			if (Character->HealthComponent)
			{
				Character->HealthComponent->TakeDamage(Damage);
			}
		}
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	Explode();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

