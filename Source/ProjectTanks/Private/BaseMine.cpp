// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMine.h"

// Sets default values
ABaseMine::ABaseMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("mine")));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	bIsActive = false;
	SetActorHiddenInGame(true);
}

void ABaseMine::Activate()
{
	Super::Activate();
}

void ABaseMine::Reset()
{
	// reset to initial state
	Super::Reset();
}

// Called when the game starts or when spawned
void ABaseMine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

