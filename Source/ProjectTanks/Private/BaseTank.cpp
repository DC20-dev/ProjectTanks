// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"
#include "TankPlayerController.h"

// Sets default values
ABaseTank::ABaseTank()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName(TEXT("tank")));

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	check(Collider);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	Collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Collider->SetNotifyRigidBodyCollision(true);
	RootComponent = Collider;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	check(Body);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Body->SetupAttachment(RootComponent);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	check(Turret);
	Turret->SetupAttachment(Body);
	Turret->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle"));
	check(Barrel);
	Barrel->SetupAttachment(Turret);
	Barrel->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	check(Movement);

	Bullets = CreateDefaultSubobject<UActorPoolComponent>(TEXT("Bullets"));
	check(Bullets);

	Mines = CreateDefaultSubobject<UActorPoolComponent>(TEXT("Mines"));
	check(Mines);
}

void ABaseTank::ShootBullet()
{
	if (bIsShooting)
	{
		return;
	}
	ABaseBullet* bullet = (ABaseBullet*) Bullets->GetFromPool();
	if (bullet)
	{
		bIsShooting = true;
		// set the position and direction of the bullet and activate it
		FVector muzzleLocation = Barrel->GetComponentLocation() + Turret->GetForwardVector() * MuzzleOffset;
		bullet->SetActorLocationAndRotation(muzzleLocation, Turret->GetComponentRotation());
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
	if (bIsShooting)
	{
		return;
	}
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

float ABaseTank::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// has to be triggered to fire events in blueprints
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// common for all tanks is to explode on bullet hit or mine explosion
	// we will only destroy it for the moment
	Destroy();
	return 0;
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
	FVector inputDirection(inputNormalized.Y, inputNormalized.X, 0);
	// Let's get the dot product between the right vector and the direction
	float DotDirRight = FVector::DotProduct(inputDirection, GetActorRightVector());

	// Now we get the dot between the forward and direction
	float DotDirForw = FVector::DotProduct(inputDirection, GetActorForwardVector());
	
	FRotator newRotation = inputDirection.Rotation();
	if (DotDirForw < 0)
	{
		newRotation.Add(0, 180, 0);
	}

	SetActorRotation(FMath::RInterpTo(GetActorRotation(), newRotation, GetWorld()->GetDeltaSeconds(), BodyRotationSpeed));

	// finally add the forward movement input
	AddMovementInput(GetActorForwardVector(), FMath::Sign(DotDirForw));
}
