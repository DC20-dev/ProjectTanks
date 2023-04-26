// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PoolableActor.h"
#include "DamagingActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTANKS_API ADamagingActor : public APoolableActor
{
	GENERATED_BODY()

public:
	ADamagingActor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Box;

protected:

	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	virtual void Reset() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Activate() override;
};