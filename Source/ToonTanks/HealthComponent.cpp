// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
// #include "GameFramework/Actor.h"
#include "KisMet/GameplayStatics.h"
#include "ToonTankGameMode.h"
#include "BasePawn.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *Damagecauser)
{
	if(Damage <=0.f) return ;

	Health -= Damage;
	if(Health < 51)
	{
		if(ABasePawn* pawn = Cast<ABasePawn>(DamagedActor))
			pawn->DamagedEffectsOn();
	}
	UE_LOG(LogTemp, Warning, TEXT("Damaged Target : %s \n HP : %f"), *DamagedActor->GetName(), Health);
	if(Health <=0.f && ToonTankGameMode)
	{
		ToonTankGameMode->ActorDied(DamagedActor);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

