// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CHESS_PlayerInterface.generated.h"



UENUM()
enum class EColor : uint8
{
	White,
	Black,
	NotDefined
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCHESS_PlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_PROJECT_API ICHESS_PlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int32 PlayerNumber;
	EColor Color;

	virtual void OnTurn() {};
	virtual void OnWin() {};
	virtual void OnLose() {};
};
