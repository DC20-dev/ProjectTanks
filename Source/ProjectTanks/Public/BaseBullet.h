// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class PROJECTTANKS_API ABaseBullet : public APoolableActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	virtual void Activate() override;

	virtual void Reset() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
