// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueGameplayInterface.h"
#include "GameFramework/Character.h"
#include "RogueItemChest.generated.h"

UCLASS()
class UNREALROGUELIKE_API ARogueItemChest : public AActor, public IRogueGameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueItemChest();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
