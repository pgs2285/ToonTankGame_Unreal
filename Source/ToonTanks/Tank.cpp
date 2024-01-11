// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank :: ATank()
{
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    _springArm -> SetupAttachment(RootComponent);

    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    _camera -> SetupAttachment(_springArm);
} 
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(TankPlayerController)
    {   
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false, 
            HitResult);
            DrawDebugSphere(
                GetWorld(),
                HitResult.ImpactPoint,
                25.f,
                12,
                FColor::Green,
                false,
                -1.f
                );
            RotateTurret(HitResult.ImpactPoint);


    }

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    UE_LOG(LogTemp, Warning, TEXT("내 탱크 부서지는 소리"));
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    FVector deltaLocation = FVector::ZeroVector;
    deltaLocation.X = Value * _speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(deltaLocation, true);
    
}

void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = value * _turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}
