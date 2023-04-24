// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "GameFramework/Actor.h"
#include "BaseMine.generated.h"

UCLASS()
class PROJECTTANKS_API ABaseMine : public APoolableActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	ABaseMine();
	
	virtual void Activate() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Reset() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
