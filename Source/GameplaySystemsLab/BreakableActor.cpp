// GameplaySystemsLabCharacter.h
// Copyright Epic Games, Inc. All Rights Reserved.

#include "BreakableActor.h"
#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABreakableActor::ABreakableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));

    Mesh->OnComponentHit.AddDynamic(this, &ABreakableActor::OnHit);
}

void ABreakableActor::BeginPlay()
{
    Super::BeginPlay();
}

void ABreakableActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        AEnemy* Enemy = Cast<AEnemy>(OtherActor);

        if (Enemy)
        {
			UGameplayStatics::ApplyDamage(
				Enemy,
				50.f,
				nullptr,
				this,
				nullptr
			);
            Destroy();
        }
        Destroy();
    }
}
