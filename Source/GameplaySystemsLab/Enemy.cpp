#include "Enemy.h"

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
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

void AEnemy::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;

    if (Health <= 0.f)
    {
        Destroy();
    }
}
