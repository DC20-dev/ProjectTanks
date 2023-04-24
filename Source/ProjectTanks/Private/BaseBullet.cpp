// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = Mesh;
	bIsActive = false;
	SetActorHiddenInGame(true);
}

void ABaseBullet::Activate()
{
	Super::Activate();
}


void ABaseBullet::Reset()
{
	Super::Reset();
	// reset to initial state
}


// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActive)
	{
		return;
	}

	// move projectile forward
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(newLocation);
}

