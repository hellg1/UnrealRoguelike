// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectileBase.h"
#include "GameFramework/Actor.h"
#include "RogueMagicProjectile.generated.h"

UCLASS()
class UNREALROGUELIKE_API ARogueMagicProjectile : public ARogueProjectileBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	// Sets default values for this actor's properties

public:
	ARogueMagicProjectile();
};
