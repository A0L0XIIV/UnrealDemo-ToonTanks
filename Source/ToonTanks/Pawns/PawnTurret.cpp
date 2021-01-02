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

// Called every frame
void APawnTurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition(){
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn)
		return;
	// If Player is IN range THEN FIRE!!
	if (ReturnDistanceToPlayer() <= FireRange) {
		// Fire
		UE_LOG(LogTemp, Warning, TEXT("FIRE!!"));
	}
}

float APawnTurret::ReturnDistanceToPlayer() {
	if (!PlayerPawn)
		return 0.0f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}