// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseMine::ABaseMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("mine")));

	// disable hit simulation events, we don't need them here
	// instead we'll use overlap events for this oblject because we need to be able to pass throught it
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Box->SetGenerateOverlapEvents(true);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABaseMine::OnComponentBeginOverlapBox);

	ExplosionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion"));
	check(ExplosionCollider);
	// deactivate collisions and enable query only
	ExplosionCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExplosionCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ExplosionCollider->SetNotifyRigidBodyCollision(false);
	ExplosionCollider->SetGenerateOverlapEvents(false);
	ExplosionCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseMine::OnComponentBeginOverlapExplosion);
	ExplosionCollider->SetupAttachment(RootComponent);
}

void ABaseMine::Activate()
{
	Super::Activate();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ABaseMine::Reset, Lifespan, false);
	//TODO add visual representation for the last seconds before it blows up
}

void ABaseMine::Reset()
{
	// do explosion
	ExplosionCollider->SetGenerateOverlapEvents(true);
	// delay resetting the mine in the pool just enought to have the explosion last a few more frames
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]()
		{
			ExplosionCollider->SetGenerateOverlapEvents(false);
			Super::Reset();
		}, ExplosionDuration, false);
}

void ABaseMine::OnComponentBeginOverlapExplosion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("tank")) ||
		OtherActor->ActorHasTag(TEXT("mine")) ||
		OtherActor->ActorHasTag(TEXT("destructible")))
	{
		APawn* tank = Cast<APawn>(OtherActor);
		if (tank)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 1, tank->GetController(), OtherActor, nullptr);	// not using damage types in the game
			Reset();
		}
	}
}

void ABaseMine::OnComponentBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner)
	{
		return;
	}

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
}

float ABaseMine::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Reset();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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

