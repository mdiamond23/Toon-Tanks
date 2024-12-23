// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank:: HandleDestruction(){
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    IsAlive = false;
}

void ATank::MoveForward(const FInputActionValue& Value)
{
    // Get the axis value from the input action
    float ForwardValue = Value.Get<float>();

    // If ForwardValue is positive, W is pressed, moving forward
    // If ForwardValue is negative, S is pressed, moving backward
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = ForwardValue * MoveSpeed * GetWorld()->DeltaTimeSeconds;

    // Move the tank forward or backward based on the input value
    AddActorLocalOffset(DeltaLocation, true);
}


void ATank::Turn(const FInputActionValue& Value)
{
    // Get the axis value from the input action
    float TurnValue = Value.Get<float>();

    // Apply rotation around the Z axis (Yaw)
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = TurnValue * TurnSpeed * GetWorld()->DeltaTimeSeconds;

    // Rotate the tank left or right based on the input value
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::RotateTurret(const FInputActionValue& Value)
{
    float RotateValue = Value.Get<float>();
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = RotateValue * TurnSpeed * GetWorld()->DeltaTimeSeconds;
    GetTurretMesh()->AddLocalRotation(DeltaRotation, true);
}

void ATank::Firing(const FInputActionValue&)
{
    Fire();
    UE_LOG(LogTemp, Display, TEXT("Fire"));
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Assuming you have set up Enhanced Input in your project
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        // Get the Enhanced Input Local Player Subsystem
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        // Add the Input Mapping Context
        if (Subsystem && InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }

        // Ensure the PlayerInputComponent is of type UEnhancedInputComponent
        UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
        if (EnhancedInputComponent)
        {
            // Bind actions to input triggers
            EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATank::MoveForward);
            EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);
            EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateTurret);
            EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
        }
    }
}
