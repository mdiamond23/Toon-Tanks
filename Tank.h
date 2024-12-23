#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
    GENERATED_BODY()

public:
    ATank();

    void HandleDestruction();

    APlayerController* GetTankPlayerController() const {return TankPlayerController;}

        bool IsAlive = true;

protected:
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(EditAnywhere, Category = "Components")
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, Category = "Components")
    class UCameraComponent* Camera;

    // Movement and rotation functions
    void MoveForward(const FInputActionValue& Value);
    void Turn(const FInputActionValue& Value);
    void RotateTurret(const FInputActionValue& Value);
	void Firing(const FInputActionValue&);

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 100.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnSpeed = 50.f;

    // Enhanced Input properties
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveForwardAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* TurnAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, Category = "Input");
	UInputAction* FireAction;

    APlayerController* TankPlayerController;

};
