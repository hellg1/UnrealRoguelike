// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueMagicProjectile.h"

#include "RogueAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ARogueMagicProjectile::ARogueMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SphereComponent->SetSphereRadius(20.f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueMagicProjectile::OnActorOverlap);

	DamageAmount = 20.f;
}

void ARogueMagicProjectile::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (Actor && Actor != GetInstigator())
	{
		URogueAttributeComponent* AttributeComponent = Cast<URogueAttributeComponent>(Actor->GetComponentByClass(URogueAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChanges(-DamageAmount);
			Explode();
		}
	}
}

// Sets default values


// Called when the game starts or when spawned

