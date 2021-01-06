// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnTurret::APawnTurret() {
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay() {
	Super::BeginPlay();

	// Same as GetWorldTimerManager()
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	// this -> is World Object, 0 is Player0
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction(){
	// Call base pawn class HandleDestruction to play effects.
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) {
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition(){
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
		return;
	// If Player is IN range THEN FIRE!!
	if (ReturnDistanceToPlayer() <= FireRange) {
		// Fire
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() {
	if (!PlayerPawn)
		return 0.0f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}