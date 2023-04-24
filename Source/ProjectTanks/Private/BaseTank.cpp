// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"
#include "TankPlayerController.h"

// Sets default values
ABaseTank::ABaseTank()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName(TEXT("tank")));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	Bullets = CreateDefaultSubobject<UActorPoolComponent>(TEXT("Bullets"));

	Mines = CreateDefaultSubobject<UActorPoolComponent>(TEXT("Mines"));
}

void ABaseTank::ShootBullet()
{
	ABaseBullet* bullet = (ABaseBullet*) Bullets->GetFromPool();
	if (bullet)
	{
		bIsShooting = true;
		// set the position and direction of the bullet and activate it
		bullet->SetActorLocationAndRotation(GetActorLocation(), Turret->GetComponentRotation());
		bullet->Activate();

		// set isShooting back to false on next tick
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, [this]()
			{
				bIsShooting = false;
			}, shootStopDuration, false);
	}
}

void ABaseTank::PlaceMine()
{
	ABaseMine* mine = (ABaseMine*)Mines->GetFromPool();
	if (mine)
	{
		bIsShooting = true;
		// set the position of the mine and activate it
		mine->SetActorLocation(GetActorLocation());
		mine->Activate();
		// set isShooting back to false on next tick
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, [this]()
			{
				bIsShooting = false;
			}, shootStopDuration, false);
	}
}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	Bullets->InitPool();

	Mines->InitPool();
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTank::Move(FVector2D inputNormalized)
{
	if (bIsShooting)
	{
		return;
	}
	// Let's get the dot product between the right vector and the direction;
	// this will provide the sense we have to rotate the actor (at least on the forward two sectors)
	float DotDirRight = FVector::DotProduct(FVector(inputNormalized.Y, inputNormalized.X, 0), GetActorRightVector());

	// Now we get the dot between the forward and direction;
	// this will give us the angle to rotate and the sign to which adjust the rotation sense
	float DotDirForw = FVector::DotProduct(FVector(inputNormalized.Y, inputNormalized.X, 0), GetActorForwardVector());

	// if the direction is not parallel to the forward we can rotate
		float rotation = bodyRotationSpeed * GetWorld()->GetDeltaSeconds();
		// now adjust the orientation with the dots sign
		rotation *= FMath::Sign(DotDirForw) * FMath::Sign(DotDirRight);

		AddActorWorldRotation(FRotator(0, rotation, 0));

	// finally add the forward movement input
	AddMovementInput(GetActorForwardVector(), 1 * FMath::Sign(DotDirForw));
	// if you want to allow precise control over the movement speed with analogs then use this instead
	//AddMovementInput(GetActorForwardVector(), DotDirForw);
}
