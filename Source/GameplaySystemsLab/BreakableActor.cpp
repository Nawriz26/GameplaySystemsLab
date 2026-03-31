#include "BreakableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"

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
            Enemy->TakeDamage(50.f);
            Destroy();
        }
    }
}
