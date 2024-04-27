// Fill out your copyright notice in the Description page of Project Settings.


#include "ThePawn.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"

// Sets default values
AThePawn::AThePawn() : ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

    Name = ENamePiece::PAWN;

}

// Called when the game starts or when spawned
void AThePawn::BeginPlay()
{
	Super::BeginPlay();
	
}




TArray<FVector2D> AThePawn::PossibleMoves()
{
    TArray<FVector2D> Moves = GameField->HighlightMoves(Name, PlayerOwner, GetGridPosition(), HasMoved);
    return Moves;
}

// Called every frame
void AThePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

