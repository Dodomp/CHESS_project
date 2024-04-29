// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CHESS_PlayerInterface.h"
#include "CHESS_GameInstance.h"
#include "CHESS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "RandomPlayer.generated.h"

UCLASS()
class CHESS_PROJECT_API ARandomPlayer : public APawn, public ICHESS_PlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARandomPlayer();

	UCHESS_GameInstance* GameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnTurn() override;
	virtual void OnWin() override;
	virtual void OnLose() override;

	//retun a rando black piece, only constrain is that the piece has almost one legal moves
	ABasePiece* GetRandomBlackPiece(ACHESS_GameMode* GameMode);

	//return one randome legal moves
	FVector2D GetRandomMove(TArray<FVector2D> Moves);


};
