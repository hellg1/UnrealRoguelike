// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "RogueGameplayInterface.h"


// Sets default values for this component's properties
URogueInteractionComponent::URogueInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URogueInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyesLocation;
	FRotator EyesRotation;
	MyOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);

	FVector End = EyesLocation + (EyesRotation.Vector()*1000);

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyesLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.f;

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyesLocation, End, FQuat::Identity, ObjectQueryParams, CollisionShape);
	FColor Color = bBlockingHit ? FColor::Green : FColor::Red;

	for (auto Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor) 
		{
			if (HitActor->Implements<URogueGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IRogueGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, Color, false, 2.f);
	}
	

	DrawDebugLine(GetWorld(), EyesLocation, End, Color, false, 2.f, 0, 2.f);
}


// Called when the game starts
void URogueInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

