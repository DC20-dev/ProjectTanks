// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingActor.h"

ADamagingActor::ADamagingActor()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("collider"));
	check(Box);
	RootComponent = Box;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	check(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(Box);

	bIsActive = false;
	SetActorHiddenInGame(true);
}

void ADamagingActor::Activate()
{
	Super::Activate();
}

void ADamagingActor::Reset()
{
	Super::Reset();
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


// Called when the game starts or when spawned
void ADamagingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADamagingActor::OnComponentBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
