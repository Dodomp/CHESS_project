// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"

// Sets default values
ABishop::ABishop(): ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = ENamePiece::BISHOP;

}

TArray<FVector2D> ABishop::PossibleMoves()
{
	TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(), false);
	return Moves;
}

// Called when the game starts or when spawned
void ABishop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABishop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABishop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

