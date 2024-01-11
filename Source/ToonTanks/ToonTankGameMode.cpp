// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTankGameMode::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(Tank->GetTankPlayerController())
        {
            Tank->DisableInput(Tank->GetTankPlayerController()); // input을 막고
            Tank->GetTankPlayerController() ->bShowMouseCursor=false; // 마우스커서를 비활성화
        }

    }
    else if(ATower* DestroyTower = Cast<ATower>(DeadActor)) // 이 식이 성공하면 들어감
    {
        DestroyTower->HandleDestruction();
    }
}

void AToonTankGameMode::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}