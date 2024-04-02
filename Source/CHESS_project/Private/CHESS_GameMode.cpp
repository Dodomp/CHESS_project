// Fill out your copyright notice in the Description page of Project Settings.


#include "CHESS_GameMode.h"
#include "CHESS_PlayerController.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
//#include "TTT_MinimaxPlayer.h"
#include "EngineUtils.h"

ACHESS_GameMode::ACHESS_GameMode()
{
	PlayerControllerClass = ACHESS_PlayerController::StaticClass();
	DefaultPawnClass = AHumanPlayer::StaticClass();
	FieldSize = 8;
}

void ACHESS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	MoveCounter = 0;

	AHumanPlayer* HumanPlayer = Cast<AHumanPlayer>(*TActorIterator<AHumanPlayer>(GetWorld()));

	if (GameFieldClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGameField>(GameFieldClass);
		GField->Size = FieldSize;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	float CameraPosX = ((GField->TileSize * (FieldSize + ((FieldSize - 1)) - (FieldSize - 1))) / 2) - (GField->TileSize / 2);
	FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	// Human player = 0
	Players.Add(HumanPlayer);
	// Random Player
	auto* AI = GetWorld()->SpawnActor<ARandomPlayer>(FVector(), FRotator());

	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	this->ChoosePlayerAndStartGame();
}

void ACHESS_GameMode::ChoosePlayerAndStartGame()
{
}

void ACHESS_GameMode::SetCellSign(const int32 PlayerNumber, const FVector& SpawnPosition)
{
}

int32 ACHESS_GameMode::GetNextPlayer(int32 Player)
{
	return int32();
}

void ACHESS_GameMode::TurnNextPlayer()
{
}
