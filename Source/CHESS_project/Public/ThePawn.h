// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePiece.h"
#include "GameField.h"
#include "ThePawn.generated.h"

UCLASS()
class CHESS_PROJECT_API AThePawn : public ABasePiece
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThePawn();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//void ApplyMaterial (bool value) override;

	TArray<FVector2D> PossibleMoves() override;




	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
