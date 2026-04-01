#include "Collectible.h"
#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"
//#include "GameFramework/Character.h"
#include "GameplaySystemsLabCharacter.h"
#include "Engine/Engine.h"

ACollectible::ACollectible()
{
    //PrimaryActorTick.bCanEverTick = false;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    RootComponent = Sphere;

    //Sphere->InitSphereRadius(50.f);
    Sphere->SetCollisionProfileName(TEXT("Trigger"));
    Sphere->SetGenerateOverlapEvents(true);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    //Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnOverlap);
}

void ACollectible::BeginPlay()
{
    Super::BeginPlay();
}

void ACollectible::OnOverlap(UPrimitiveComponent* OverlappedComp, 
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex,
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    // 🔥 REQUIRED CAST
    AGameplaySystemsLabCharacter* Player = Cast<AGameplaySystemsLabCharacter>(OtherActor);
    if (Player)
    {
        // 🔥 Increase Health
        Player->AddHealth(20.f);

        // Debug feedback
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                2.0f,
                FColor::Yellow,
                TEXT("Collected Item! +20 Health")
            );
        }

		// Destroy the collectible
        Destroy();
    }
}
