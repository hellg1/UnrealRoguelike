// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealRoguelike/Public/RogueCharacter.h"

#include "DrawDebugHelpers.h"
#include "RogueInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARogueCharacter::ARogueCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<URogueInteractionComponent>("InteractionComponent");
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FString test = 123;
}

void ARogueCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ARogueCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
    	
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
}

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(AnimMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARogueCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ARogueCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}

// Called to bind functionality to input
void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARogueCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARogueCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARogueCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ARogueCharacter::PrimaryInteract);
}

void ARogueCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;
	
	AddMovementInput(ControlRotation.Vector(), Value);
}

