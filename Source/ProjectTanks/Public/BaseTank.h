// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorPoolComponent.h"
#include "BaseBullet.h"
#include "BaseMine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BaseTank.generated.h"

UCLASS(Blueprintable)
class PROJECTTANKS_API ABaseTank : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Turret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	UActorPoolComponent* Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	UActorPoolComponent* Mines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float bodyRotationSpeed;

	float shootStopDuration = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (MakeEditWidget = true))
	FVector MuzzleLocation;

	bool bIsShooting = false;

public:	
	// Sets default values for this actor's properties
	ABaseTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move(FVector2D inputNormalized);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void ShootBullet();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void PlaceMine();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
