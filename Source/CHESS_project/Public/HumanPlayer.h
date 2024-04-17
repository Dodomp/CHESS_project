// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "GameFramework/Pawn.h"
#include "CHESS_GameInstance.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Chess_PlayerInterface.h"
#include "HumanPlayer.generated.h"

UCLASS()
class CHESS_PROJECT_API AHumanPlayer : public APawn, public ICHESS_PlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHumanPlayer();

	// camera component attacched to player pawn
	UCameraComponent* Camera;

	// game instance reference
	UCHESS_GameInstance* GameInstance;

	ABasePiece* TempPiece;

	TArray<FVector2D> TempMoves;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// keeps track of turn
	bool IsMyTurn = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnTurn() override;
	virtual void OnWin() override;
	virtual void OnLose() override;

	UFUNCTION()
	void OnClick();

	void UpdateTiles(ABasePiece* Piece, ATile* Tile);

	void DeleteSuggestion(ABasePiece* Piece);
	
	void Eat(ABasePiece* Lived, ABasePiece* Dead);

	TArray<FVector2D> FindLegalMoves(ABasePiece* Piece);

};
