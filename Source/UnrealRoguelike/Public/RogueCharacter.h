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

	UPROPERTY(EditAnywhere)
	FString MyString = TEXT("");

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> DashClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> BlackholeClass;

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
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_Blackhole;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float Value);
	void SpawnProjectile(TSubclassOf<AActor> SpawnClass);
	void PrimaryAttack_TimeElapsed();
	void PrimaryAttack();
	void Dash_TimeElapsed();
	void Dash();
	void Blackhole_TimeElapsed();
	void Blackhole();
	void PrimaryInteract();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
};
