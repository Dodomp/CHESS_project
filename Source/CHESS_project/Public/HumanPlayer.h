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

	//Variable where I can save temporarly a piece
	ABasePiece* TempPiece;

	//Array where I save legal moves
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

	//This function manage the logic when the human player select a particular moves e wants to use it
	UFUNCTION()
	void OnClick();

	//when the player move his peace the new tile will became OCCUPIED as well as the player owner of tile.
	//It also update the PieceGridPosition of Piece and the KingGridPosition if required
	void UpdateTiles(ABasePiece* Piece, ATile* Tile);

	//When the player select another piece or moves, this method delete all possible suggests
	void DeleteSuggestion(ABasePiece* Piece);
	
	//this method allow to capture another piece
	void Eat(ABasePiece* Lived, ABasePiece* Dead);

	//Find legal moves for each peace 
	TArray<FVector2D> FindLegalMoves(ABasePiece* Piece);


	//When a pawn reach the end of game field, it transforms in a Queen
	void isPromotion(ABasePiece* Piece);

};
