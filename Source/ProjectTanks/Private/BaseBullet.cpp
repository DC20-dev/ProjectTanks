// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("bullet")));
}

void ABaseBullet::Reset()
{
	Super::Reset();
	currentBounces = 0;
	// reset to initial state
}

void ABaseBullet::Bounce(const FVector& HitNormal, const FVector& HitLocation)
{
	SetActorRotation(GetActorForwardVector().MirrorByVector(HitNormal).Rotation());
	currentBounces++;
}

void ABaseBullet::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (OtherActor->ActorHasTag(TEXT("wall")))
	{
		if (currentBounces < MaxBounces)
		{
			Bounce(Hit.Normal, Hit.Location);
		}
		else
		{
			Reset();
		}
	}
	else if (OtherActor->ActorHasTag(TEXT("mine")))
	{
		// do mine stuff
		Reset();
	}
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
	SetActorLocation(newLocation, true);
}

