// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();
    

    Tank = Cast<ATank>(UGameplayStatics:: GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if (InFireRange() && Tank && Tank->IsAlive)
    {
        Fire();
    }

}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Tank){
        return;
    }

    //Find distance
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    //Check range
    if (InFireRange()){
        FVector Direction = Tank->GetActorLocation() - GetActorLocation();
        FRotator LookAtRotation = FRotator(0.f, Direction.Rotation().Yaw, 0.f);

        // Rotate turret towards the tank
        GetTurretMesh()->SetWorldRotation(LookAtRotation);

    }
}

void ATower:: HandleDestruction(){
    Super:: HandleDestruction();

    Destroy();
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }

    return false;
}
