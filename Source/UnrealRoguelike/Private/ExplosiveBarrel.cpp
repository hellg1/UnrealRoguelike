// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "RogueMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius=600.f;
	RadialForceComponent->ImpulseStrength = 2500.f;
	RadialForceComponent->bImpulseVelChange = true;

	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void AExplosiveBarrel::OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult)
{
	RadialForceComponent->FireImpulse();
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnHit);
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

