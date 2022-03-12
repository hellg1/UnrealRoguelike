// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueMagicProjectile.h"

#include "RogueAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


void ARogueMagicProjectile::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (Actor)
	{
		URogueAttributeComponent* AttributeComponent = Cast<URogueAttributeComponent>(Actor->GetComponentByClass(URogueAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChanges(-20.f);
			Destroy();
		}
	}
}

// Sets default values
ARogueMagicProjectile::ARogueMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueMagicProjectile::OnActorOverlap);
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	EffectComponent->SetupAttachment(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ARogueMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

