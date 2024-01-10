// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //범위안에 들어온 탱크 찾기
    if(Tank)
    {
        FVector TankLocation = Tank->GetActorLocation();
        FVector MyLocation = GetActorLocation();
        float Distance = FVector::Dist(MyLocation,TankLocation);
    
        //범위안에 탱크가 들어왔으면 바라보기
        if (Distance <= _fireRange)
        {
            FVector ToTarget = TankLocation - MyLocation;
            RotateTurret(Tank->GetActorLocation());
        
        }
        //
    
    }
    

}
void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}