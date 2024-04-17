// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

// Sets default values
AKnight::AKnight(): ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = ENamePiece::KNIGHT;

}

TArray<FVector2D> AKnight::PossibleMoves()
{
	TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(), false);
	return Moves;
	
}

// Called when the game starts or when spawned
void AKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

