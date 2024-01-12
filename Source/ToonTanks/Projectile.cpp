// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = _projectileMesh;

	_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	_projectileMovementComponent->MaxSpeed = 1300.f;
	_projectileMovementComponent->InitialSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);

	PlayersTrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail Player"));
	PlayersTrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	_projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// 충돌시 OnHit callback
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{//Projectile 은 BasePawn에서 Spawn할 때 생성자(player or turret으로 생성자를 바꿔줌)

	auto MyOwner = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("OWNER : %s"), *MyOwner->GetName());
	if(MyOwner == nullptr)  // owner아까 바꿔줬었음
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor!=this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles){
			UGameplayStatics::SpawnEmitterAtLocation(
				this, 
				HitParticles, 
				GetActorLocation(), 
				GetActorRotation());
		}
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			GetActorLocation()
			);
		}
		
	
	}
	Destroy();

}

