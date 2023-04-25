// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("bullet")));

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("collider"));
	check(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	Box->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Box->SetNotifyRigidBodyCollision(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	check(Mesh);
	RootComponent = Box;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->AttachToComponent(Box, FAttachmentTransformRules::KeepRelativeTransform);

	bIsActive = false;
	SetActorHiddenInGame(true);
}

void ABaseBullet::Activate()
{
	Super::Activate();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
}


void ABaseBullet::Reset()
{
	Super::Reset();
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	currentBounces = 0;
	// reset to initial state
}

void ABaseBullet::Bounce(const FVector& HitNormal, const FVector& HitLocation)
{
	// get the dot between forward (negative) and the normal to know the angle
	float DirForwardDot = FVector::DotProduct(-GetActorForwardVector(), HitNormal);
	// get the cross between the same vectors to know the angle sign (Z sign is the one to use)
	FVector DirForwardCross = FVector::CrossProduct(-GetActorForwardVector(), HitNormal).GetSignVector();

	float angle = FMath::RadiansToDegrees(FMath::Acos(DirForwardDot));
	angle *= DirForwardCross.Z;

	AddActorLocalRotation(FRotator(0, 180 + 2 * angle, 0));

	currentBounces++;
}

void ABaseBullet::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// if other actor is the wall and bullet can bounce then bounce
	if (OtherActor->ActorHasTag(TEXT("tank")))
	{
		// do tank stuff
		Reset();
	}
	else if (OtherActor->ActorHasTag(TEXT("mine")))
	{
		// do mine stuff
		Reset();
	}
	else if (OtherActor->ActorHasTag(TEXT("bullet")))
	{
		// do bullet stuff
		Reset();
	}
	else
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
}


// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentHit.AddDynamic(this, &ABaseBullet::OnComponentHit);
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

