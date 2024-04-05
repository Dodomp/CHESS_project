// Fill out your copyright notice in the Description page of Project Settings.


#include "CHESS_GameInstance.h"

void UCHESS_GameInstance::IncrementScoreHumanPlayer()
{
	ScoreHumanPlayer += 1;
}

void UCHESS_GameInstance::IncrementScoreAiPlayer()
{
	ScoreAiPlayer += 1;
}

int32 UCHESS_GameInstance::GetScoreHumanPlayer()
{
	return ScoreHumanPlayer;
}

int32 UCHESS_GameInstance::GetScoreAiPlayer()
{
	return ScoreAiPlayer;
}

FString UCHESS_GameInstance::GetTurnMessage()
{
	return CurrentTurnMessage;
}

void UCHESS_GameInstance::SetTurnMessage(FString Message)
{
	CurrentTurnMessage = Message;
}