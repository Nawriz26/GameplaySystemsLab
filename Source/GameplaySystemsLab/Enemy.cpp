#include "Enemy.h"

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // Mesh
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    // 🔥 IMPORTANT: Blocking collision
    Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// Set default health value
    Health = 100.f;
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 🔥 Step 6.3 — APPLY DAMAGE SYSTEM
float AEnemy::TakeDamage(float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser)
{
    Health -= DamageAmount;

    if (Health <= 0.f)
    {
        Destroy();
    }

    return DamageAmount;
}
