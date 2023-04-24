// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolableActor.h"
#include "ActorPoolComponent.generated.h"


UCLASS( ClassGroup=(Pool), meta=(BlueprintSpawnableComponent) )
class PROJECTTANKS_API UActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pool", meta = (ClampMin = "0"))
	int32 ActorsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pool")
	TSubclassOf<class APoolableActor> ActorClass = nullptr;

protected:
	TQueue<APoolableActor*> Pool;

public:	
	// Sets default values for this component's properties
	UActorPoolComponent();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void AddToPool(APoolableActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	APoolableActor* GetFromPool();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void InitPool();

};
