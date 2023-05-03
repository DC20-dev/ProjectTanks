// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleActor.h"

// Sets default values
ADestructibleActor::ADestructibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("destructible"));
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->SetGenerateOverlapEvents(true);
}

float ADestructibleActor::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// TODO manage VFX first
	Destroy();
	return 1.f;
}
