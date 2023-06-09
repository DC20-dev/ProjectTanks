// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagingActor.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class PROJECTTANKS_API ABaseBullet : public ADamagingActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxBounces = 1;

protected:

	int currentBounces = 0;

public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	virtual void Reset() override;

	void Bounce(const FVector& HitNormal, const FVector& HitLocation);

protected:

	virtual void OnComponentBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

};
