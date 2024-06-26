// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

// Sets default values
AQueen::AQueen()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = ENamePiece::QUEEN;

}

TArray<FVector2D> AQueen::PossibleMoves()
{
	TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(), false);
	return Moves;
}

// Called when the game starts or when spawned
void AQueen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQueen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQueen::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

