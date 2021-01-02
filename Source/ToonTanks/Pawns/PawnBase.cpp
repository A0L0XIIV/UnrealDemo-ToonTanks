// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjictileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projictile Spawn Point"));
	ProjictileSpawnPoint->IsBasedOnArchetype(TurretMesh);
}

void APawnBase::RotateTurretFunction(FVector LookAtTarget){
	// Update TurretMesh rotation to face towards the LookAtTarget passed in from Child Classes.
	// TurretMesh->SetWorldRotation()...

}

void APawnBase::Fire(){
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation.
}

void APawnBase::HandleDestruction(){
	// --- Universal functionality --- 
	// Play death effects particle, sound and camera shake. 

	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self. 

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.
}
