// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projictile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjictileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projictile Movement"));
	ProjictileMovement->InitialSpeed = MovementSpeed;
	ProjictileMovement->MaxSpeed = MovementSpeed;

	InitialLifeSpan = 3.0f; // 3 Seconds, then destroy
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	// Get the owner class
	AActor* MyOwner = GetOwner();
	// Check the owner's validity
	if (!MyOwner)
		return;

	// If the other actor is NOT self OR Owner AND exist, damage it
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
	}

	// TODO: Add effects...

	Destroy();
}