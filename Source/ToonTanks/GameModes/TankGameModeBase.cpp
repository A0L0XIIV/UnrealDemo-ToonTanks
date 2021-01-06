// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay() {
    Super::BeginPlay();

    // Call HandleGameStart to initialise the start countdown, turret activation, pawn check etc.
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {
    // Check what type of Actor died. If Turret, tally. If Player -> go to lose condition.
    if (DeadActor == PlayerTank) {
        PlayerTank->HandleDestruction();
        HandleGameOver(false); // Lost
        // Player cannot control the tank anymore
        if (PlayerControllerRef) {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
        DestroyedTurret->HandleDestruction();

        if (--TargetTurrets == 0) {
            HandleGameOver(true); // Won
        }
    }
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart() {
    // initialise the start countdown, turret activation, pawn check etc.

    // Get references and game win/lose conditions.
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Assign custom player controller
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    // Call Blueprint version GameStart();
    GameStart();
    // Player cannot control the tank at the beginnig
    if (PlayerControllerRef) {
        PlayerControllerRef->SetPlayerEnabledState(false);
        // After a certain time (StartDelay), enable player controls
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) {
    // See if the player has destroyed all the turrets, show win result.
    // else if turret destroyed player, show lose result. 
    // Call blueprint version GameOver();
    GameOver(PlayerWon);
}
