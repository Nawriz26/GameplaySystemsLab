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

// 🔥 APPLY DAMAGE SYSTEM
float AEnemy::TakeDamage(float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser)
{
    Health -= DamageAmount;

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %f damage from %s. Health now: %f"),
		DamageAmount,
		DamageCauser ? *DamageCauser->GetName() : TEXT("None"),
		Health);

    if (Health <= 0.f)
    {
        Destroy();
    }

    return DamageAmount;
}
