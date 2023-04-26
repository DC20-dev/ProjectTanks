// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingActor.h"
#include "Kismet/GameplayStatics.h"

ADamagingActor::ADamagingActor()
{
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

void ADamagingActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
}

void ADamagingActor::Activate()
{
	Super::Activate();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
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
	Box->OnComponentHit.AddDynamic(this, &ADamagingActor::OnComponentHit);
}