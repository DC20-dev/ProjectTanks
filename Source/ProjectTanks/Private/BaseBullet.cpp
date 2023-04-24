// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("bullet")));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = Mesh;
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collider"));
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
	currentBounces = 0;
	// reset to initial state
}

void ABaseBullet::Bounce(FVector HitNormal)
{
	// get the dot between forward (negative) and the normal
	float DirForwardDot = FVector::DotProduct(-GetActorForwardVector(), HitNormal);
	float angle = FMath::Acos(DirForwardDot);

	FVector rotationAxis = FVector::CrossProduct(HitNormal, -GetActorForwardVector());
	rotationAxis.Normalize();

	// rotate around the collision point and reverse the bullet
	FVector newLocation = GetActorLocation().RotateAngleAxis(angle*2, rotationAxis);
	SetActorLocation(newLocation);
	AddActorLocalRotation(FRotator(0, 180, 0));

	currentBounces++;
}

void ABaseBullet::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// if other actor is the wall and bullet can bounce then bounce
	if (false)
	{
		if (currentBounces < MaxBounces)
		{
			Bounce(Hit.ImpactNormal);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("On component hit executed"));
}


// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	capsule->OnComponentHit.AddDynamic(this, &ABaseBullet::OnComponentHit);
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

