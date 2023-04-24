// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	// input actions
	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* MoveAction;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* ShootAction;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* PlaceMineAction;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* MouseAimAction;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* GamepadAimAction;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* KeyboardMappingContext;

	UPROPERTY(BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* GamepadMappingContext;

public:
	virtual void SetupInputComponent() override;
	
};
