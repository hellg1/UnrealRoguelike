// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealRoguelike/Public/RogueCharacter.h"

#include "RogueAttributeComponent.h"
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

	AttributeComponent=CreateDefaultSubobject<URogueAttributeComponent>("AttributeComponent");
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
}

void ARogueCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ARogueCharacter::SpawnProjectile(TSubclassOf<AActor> SpawnClass)
{
	if (ensure(SpawnClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComponent->GetComponentLocation();
		FVector TraceEnd = CameraComponent->GetComponentLocation() + (GetControlRotation().Vector()*5000.f);

		FHitResult Hit;

		FRotator ProjRotation;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Adjust location to end up at crosshair look-at
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			// Fall-back since we failed to find any blocking hit
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		}
		
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnTM, SpawnParameters);
	}
}

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(AnimMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARogueCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ARogueCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashClass);
}

void ARogueCharacter::Dash()
{
	PlayAnimMontage(AnimMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ARogueCharacter::Dash_TimeElapsed, 0.2f);
}

void ARogueCharacter::Blackhole_TimeElapsed()
{
	SpawnProjectile(BlackholeClass);
}

void ARogueCharacter::Blackhole()
{
	PlayAnimMontage(AnimMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_Blackhole, this, &ARogueCharacter::Blackhole_TimeElapsed, 0.2f);
}

void ARogueCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ARogueCharacter::PrimaryInteract()
{
	if (InteractionComponent)
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
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ARogueCharacter::Blackhole);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ARogueCharacter::Dash);
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

