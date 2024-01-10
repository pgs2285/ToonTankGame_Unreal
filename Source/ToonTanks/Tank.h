// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* _springArm;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* _camera;

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category="Movement")
	float _speed = 200.f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float _turnRate = 45.f;

	APlayerController* PlayerControllerRef;
	
};
