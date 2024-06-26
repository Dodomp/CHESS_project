// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <CHESS_PlayerController.h>
#include <GameField.h>
#include <BasePiece.h>
#include "CHESS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_PROJECT_API ACHESS_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// tracks if the game is over
	bool IsGameOver;
	// array of player interfaces
	TArray<ICHESS_PlayerInterface*> Players;
	int32 CurrentPlayer;
	// tracks the number of moves in order to signal a drawn game
	int32 MoveCounter;



	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGameField> GameFieldClass;

	// field size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 FieldSize;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere)
		AGameField* GField;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> SignXActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> SignOActor;

	ACHESS_GameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the start of the game
	void ChoosePlayerAndStartGame();

	// set the cell sign and the position 
	void SetCellSign(const int32 PlayerNumber);

	// get the next player index
	int32 GetNextPlayer(int32 Player);

	// called at the end of the game turn
	void TurnNextPlayer();
};
