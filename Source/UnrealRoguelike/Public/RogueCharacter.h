// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class URogueAttributeComponent;
class URogueInteractionComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UNREALROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	FTimerHandle TimerHandle_PrimaryAttack;

	UPROPERTY(VisibleAnywhere)
	URogueInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	URogueAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AnimMontage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float Value);
	void PrimaryAttack_TimeElapsed();
	void PrimaryAttack();
	void PrimaryInteract();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
};
