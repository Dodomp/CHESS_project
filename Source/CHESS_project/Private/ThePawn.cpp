// Fill out your copyright notice in the Description page of Project Settings.


#include "ThePawn.h"

// Sets default values
AThePawn::AThePawn(): ABasePiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HasMoved = false;

}

// Called when the game starts or when spawned
void AThePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThePawn::Move(const double InX, const double InY)
{
	SetGridPosition(InX, InY);
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

