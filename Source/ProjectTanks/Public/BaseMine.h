// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "DamagingActor.h"
#include "GameFramework/Actor.h"
#include "BaseMine.generated.h"

UCLASS()
class PROJECTTANKS_API ABaseMine : public ADamagingActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* ExplosionCollider;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float Lifespan = 10;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float ExplosionDuration = .1f;

public:	
	// Sets default values for this actor's properties
	ABaseMine();
	
	virtual void Activate() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Reset() override;

	UFUNCTION()
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Call Super::TakeDamage after your operations when overriding
	virtual float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
