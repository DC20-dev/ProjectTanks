// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("bullet")));

	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Box->SetGenerateOverlapEvents(true);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::OnComponentBeginOverlapBox);
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

void ABaseBullet::OnComponentBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("tank")))
	{
		APawn* tank = Cast<APawn>(OtherActor);
		if (tank)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 1, tank->GetController(), OtherActor, nullptr);	// not using damage types in the game
			Reset();
		}
	}
	else if (OtherActor->ActorHasTag(TEXT("bullet")))
	{
		// do bullet stuff
		Reset();
	}
	else if (OtherActor->ActorHasTag(TEXT("mine")))
	{
		// do mine stuff
		Reset();
	}
	else
	{
		if (currentBounces < MaxBounces)
		{
			Bounce(SweepResult.Normal, SweepResult.Location);
		}
		else
		{
			Reset();
		}
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

void ABaseBullet::Activate()
{
	Super::Activate();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

