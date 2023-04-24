// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

DECLARE_DELEGATE_OneParam(OnReset, APoolableActor*)

UCLASS(Abstract)
class PROJECTTANKS_API APoolableActor : public AActor
{
	GENERATED_BODY()

public:
	OnReset ResetDelegate;

protected:
	bool bIsActive = false;
	
public:	
	// Sets default values for this actor's properties
	APoolableActor();

	UFUNCTION(BLueprintCallable, Category = "Behaviour")
	virtual void Activate();

protected:

	UFUNCTION(BLueprintCallable, Category = "Behaviour")
	virtual void Reset();
};