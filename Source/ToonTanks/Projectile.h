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
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* TrailParticles;
	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* PlayersTrailParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound; // 이미 전방선언 했으니 여기는 제외 
	// 그래서 맨위에 올려두는 사람도 많다 취향차이
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
