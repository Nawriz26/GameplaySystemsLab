#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "GameplaySystemsLabCharacter.h"
#include "Kismet/GameplayStatics.h"

ATriggerActor::ATriggerActor()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OnOverlapBegin);
}

void ATriggerActor::BeginPlay()
{
    Super::BeginPlay();
}

void ATriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // DEBUG MESSAGE
        AGameplaySystemsLabCharacter* Player = Cast<AGameplaySystemsLabCharacter>(OtherActor);
        if (Player)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Player Entered Trigger"));
        }

        TArray<AActor*> FoundEnemies;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

        for (AActor* Actor : FoundEnemies)
        {
            Actor->Destroy();
        }
    }
}
