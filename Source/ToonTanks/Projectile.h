// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	UStaticMeshComponent* _projectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Movement")
	class UProjectileMovementComponent* _projectileMovementComponent;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float _projectileMaxSpeed = 1300.f;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float _projectileInitialSpeed = 1300.f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
