// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TankPlayerController.h"

APlayerTank::APlayerTank() : ABaseTank()
{
	Tags.Add(FName(TEXT("player")));
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// enhanced input system handling as explained by Lively Geek here: https://www.youtube.com/watch?v=4wWIjlkSj2w&t=894s

	// get the input component and cst it to the enhanced version 
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// get the player controller
	ATankPlayerController* playerController = Cast<ATankPlayerController>(Controller);
	check(playerController);

	// bind actions
	enhancedInputComponent->BindAction(playerController->MoveAction, ETriggerEvent::Triggered, this, &APlayerTank::MoveAction);
	enhancedInputComponent->BindAction(playerController->ShootAction, ETriggerEvent::Started, this, &APlayerTank::ShootBulletAction);
	enhancedInputComponent->BindAction(playerController->PlaceMineAction, ETriggerEvent::Started, this, &APlayerTank::PlaceMineAction);
	enhancedInputComponent->BindAction(playerController->MouseAimAction, ETriggerEvent::Triggered, this, &APlayerTank::SetMouseAim);
	enhancedInputComponent->BindAction(playerController->GamepadAimAction, ETriggerEvent::Triggered, this, &APlayerTank::SetGamepadAim);

	// get local player subsystem and bind the input component to the subsystem
	UEnhancedInputLocalPlayerSubsystem* subsystem =
		playerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(subsystem);

	// clear all mappings as this system allows dynamic mapping
	subsystem->ClearAllMappings();
	// finally bind the mappings
	subsystem->AddMappingContext(playerController->KeyboardMappingContext, 0);
	subsystem->AddMappingContext(playerController->GamepadMappingContext, 1);
}

void APlayerTank::Tick(float DeltaTime)
{
	// manage mouse pointing if not using gamepad
	if (bUsingMouseKeyboard)
	{
		APlayerController* playerController = Cast<APlayerController>(Controller);
		check(playerController);

		// Get the location the cursor is pointing at
		FHitResult hit;
		playerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);

		// Debug point to know where we are pointing as there is still no UI
		DrawDebugCircle(GetWorld(), hit.Location, 20, 8, FColor::Red, false);

		// Move the Z component to match the turret Z component to have no roll and pitch rotation
		hit.Location.Z = Turret->GetComponentLocation().Z;

		// compute the look at rotation and set it to the turret
		FRotator rotation = (hit.Location - Turret->GetComponentLocation()).Rotation();
		Turret->SetWorldRotation(FMath::RInterpTo(Turret->GetComponentRotation(), rotation, GetWorld()->DeltaTimeSeconds, 10));
	}
}

void APlayerTank::MoveAction(const struct FInputActionValue& ActionValue)
{
	FVector2D input = ActionValue.Get<FInputActionValue::Axis2D>();
	input.Normalize();

	Move(input);
}


void APlayerTank::SetMouseAim(const FInputActionValue& ActionValue)
{
	bUsingMouseKeyboard = true;
}

void APlayerTank::SetGamepadAim(const FInputActionValue& ActionValue)
{
	bUsingMouseKeyboard = false;
	// get the direction pointed by the analog
	FVector2D input = ActionValue.Get<FInputActionValue::Axis2D>();
	FVector input3D(-input.Y, input.X, 0);

	Turret->SetWorldRotation(FMath::RInterpTo(Turret->GetComponentRotation(), input3D.Rotation(), GetWorld()->DeltaTimeSeconds, 10));
}

void APlayerTank::ShootBulletAction(const struct FInputActionValue& ActionValue)
{
	
	ShootBullet();
}

void APlayerTank::PlaceMineAction(const struct FInputActionValue& ActionValue)
{
	PlaceMine();
}