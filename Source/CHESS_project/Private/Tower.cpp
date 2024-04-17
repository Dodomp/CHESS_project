// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

// Sets default values
ATower::ATower(): ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = ENamePiece::TOWER;

}

TArray<FVector2D> ATower::PossibleMoves()
{
	TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(),false);
	return Moves;



}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

