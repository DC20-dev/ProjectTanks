// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxBounces = 1;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Box;

	int currentBounces = 0;

public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	virtual void Activate() override;

	virtual void Reset() override;

	void Bounce(const FVector& HitNormal, const FVector& HitLocation);

	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
