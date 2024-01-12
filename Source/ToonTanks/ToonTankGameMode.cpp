// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTankGameMode::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if(ATower* DestroyTower = Cast<ATower>(DeadActor)) // 이 식이 성공하면 들어감
    {
        DestroyTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTankGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));


    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false // 반복금지
        );
    }
}

int AToonTankGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    for(int i = 0; i < Towers.Num(); ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("Towers - %d : %s %s"), i,*Towers[i]->GetName());
    }
    return Towers.Num();
}
