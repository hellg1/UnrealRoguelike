// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectileBase.h"
#include "RogueDashProjectile.generated.h"

UCLASS()
class UNREALROGUELIKE_API ARogueDashProjectile : public ARogueProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueDashProjectile();

protected:

	UPROPERTY(EditDefaultsOnly)
	float DetonateDelay;

	UPROPERTY(EditDefaultsOnly)
	float TeleportDelay;

	FTimerHandle TimerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
