// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

// Sets default values
AKing::AKing(): ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = ENamePiece::KING;

}

TArray<FVector2D> AKing::PossibleMoves()
{
	TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(), false);
	return Moves;
}

// Called when the game starts or when spawned
void AKing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

