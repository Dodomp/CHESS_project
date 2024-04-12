// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "GameFramework/Pawn.h"
#include "Queen.generated.h"

UCLASS()
class CHESS_PROJECT_API AQueen : public ABasePiece
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AQueen();

	TArray<FVector2D> PossibleMoves() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
