// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTANKS_API APlayerTank : public ABaseTank
{
	GENERATED_BODY()

public:
	APlayerTank();

protected:

	bool bUsingMouseKeyboard = false;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	virtual void MoveAction(const struct FInputActionValue& ActionValue);


	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void SetMouseAim(const struct FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void SetGamepadAim(const struct FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void ShootBulletAction(const struct FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void PlaceMineAction(const struct FInputActionValue& ActionValue);
	
};
