// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjictileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projictile Mesh"));
	RootComponent = ProjictileMesh;

	ProjictileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projictile Movement"));
	ProjictileMovement->InitialSpeed = MovementSpeed;
	ProjictileMovement->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}