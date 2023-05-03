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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* Box;

protected:

	virtual void Reset() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnComponentBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	virtual void Activate() override;
};
