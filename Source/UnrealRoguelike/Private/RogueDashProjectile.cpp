// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ARogueDashProjectile::ARogueDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetonateDelay = 0.2f;
	TeleportDelay = 0.2f;

	MovementComponent->InitialSpeed = 6000.f;
}

void ARogueDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComponent->DeactivateSystem();
	MovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);
	
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ARogueDashProjectile::TeleportInstigator, TeleportDelay);
}

void ARogueDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

// Called when the game starts or when spawned
void ARogueDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ARogueDashProjectile::Explode, DetonateDelay);
	
}

