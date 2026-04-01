// GameplaySystemsLabCharacter.h
// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplaySystemsLabCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplaySystemsLab.h"
#include "Kismet/GameplayStatics.h"

// Added these
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include <BreakableActor.h>

AGameplaySystemsLabCharacter::AGameplaySystemsLabCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	// Health values
	Health = 100.f;
	MaxHealth = 100.f;
}

void AGameplaySystemsLabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGameplaySystemsLabCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AGameplaySystemsLabCharacter::Look);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGameplaySystemsLabCharacter::Look);

		// 🔥 ATTACK INPUT
		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGameplaySystemsLabCharacter::Attack);
		}
	}
}

void AGameplaySystemsLabCharacter::Attack()
{
	FVector Start = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FVector End = Start + (Forward * 500.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	// Debug line
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);

	if (bHit)
	{
		AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());

		if (Enemy)
		{
			UGameplayStatics::ApplyDamage(
				Enemy,
				25.f,
				GetController(),
				this,
				nullptr
			);
		}
		else if (ABreakableActor* Breakable = Cast<ABreakableActor>(Hit.GetActor()))
		{
			Breakable->Destroy();
		}
	}
}

void AGameplaySystemsLabCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AGameplaySystemsLabCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AGameplaySystemsLabCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AGameplaySystemsLabCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGameplaySystemsLabCharacter::DoJumpStart()
{
	Jump();
}

void AGameplaySystemsLabCharacter::DoJumpEnd()
{
	StopJumping();
}

void AGameplaySystemsLabCharacter::AddHealth(float Amount)
{
	Health += Amount;
	Health = FMath::Clamp(Health, 0.f, 100.f);
}

// Health percentage calculation and getter for UI
float AGameplaySystemsLabCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

