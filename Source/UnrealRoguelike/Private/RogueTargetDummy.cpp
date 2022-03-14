// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTargetDummy.h"

#include "RogueAttributeComponent.h"


// Sets default values
ARogueTargetDummy::ARogueTargetDummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;

	AttributeComponent = CreateDefaultSubobject<URogueAttributeComponent>(TEXT("Attribute"));
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ARogueTargetDummy::OnHealthChanged);
}

void ARogueTargetDummy::OnHealthChanged(AActor* InstigatorActor, URogueAttributeComponent* OwningComp, float Health,
	float Delta)
{
	if (Delta < 0.f)
		StaticMeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
}

// Called when the game starts or when spawned
void ARogueTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

