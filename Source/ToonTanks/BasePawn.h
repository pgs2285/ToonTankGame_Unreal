// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleInstanceOnly)
	int VisibleInstanceOnlyInt=11;

	UPROPERTY(VisibleDefaultsOnly)
	int VisibleDefaultsOnlyInt = 5;

	UPROPERTY(EditDefaultsOnly)
	int EditDefaultOnlyInt = 0;
	UPROPERTY(EditInstanceOnly)
	int EditInstanfceOnlyInt = 14;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 40.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
    class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))	// SceneComponent 는 다른 요스들에 부착되어 해당 요소의 위치와 회전을 정의하는데 사용.
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Super Duper Jisung",meta = (AllowPrivateAccess = "true"))
	int VisibleAnywhereInt = 12;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Duper Jisung",meta = (AllowPrivateAccess="true"))
	int EditAnywhereInt;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
