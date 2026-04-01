#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEPLAYSYSTEMSLAB_API AEnemy : public AActor
{
    GENERATED_BODY()

public:
    AEnemy();

protected:
    virtual void BeginPlay() override;

    // 🔥 OVERRIDE DAMAGE SYSTEM (LAB REQUIREMENT)
    virtual float TakeDamage(float DamageAmount,
        struct FDamageEvent const& DamageEvent,
        class AController* EventInstigator,
        AActor* DamageCauser) override;


public:
    virtual void Tick(float DeltaTime) override;

    // Mesh
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Mesh;

    // Health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float Health;

    void TakeDamage(float DamageAmount);
};
