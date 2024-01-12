// Fill out your copyright notice in the Description page of Project Settings��������\


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spanw Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);


}

void ABasePawn::HandleDestruction()
{
	//TODO : 시각 및 사운드 효과
	if(_deathEffect){
		UGameplayStatics::SpawnEmitterAtLocation(
			this, 
			_deathEffect,
			GetActorLocation(),
			GetActorRotation());
	}
}

void ABasePawn::DamagedEffectsOn()
{
	if(!isFired){
		UGameplayStatics::SpawnEmitterAttached(
			_damagedEffect,
			RootComponent,
			TEXT("EFFECTS"),
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();// 방향벡터 구하기
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); // 정면만 바라보게 yaw값만 가져온다. 
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		_lerpSpeed
		)
	);
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint ->GetComponentLocation();
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPointLocation,
		20.f,
		12,
		FColor::Red,
		false,
		2.f
	);
	FVector Location = ProjectileSpawnPoint -> GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}