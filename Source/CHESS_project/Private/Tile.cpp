// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "Tile.h"

// Sets default values
//COSTRUTTORE
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// every actor has a RootComponent that defines the transform in the World
	//attacco l'actor scena alla staticMesh
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	//inizialmente la Tile è vuota
	Status = ETileStatus::EMPTY;
	//non appartiene a nessun giocatore
	PlayerOwner = -1;

	//centrata nell'origine degli assi
	TileGridPosition = FVector2D(0, 0);


}

void ATile::SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;

}

ETileStatus ATile::GetTileStatus()
{
	return Status;
}

int32 ATile::GetOwner()
{
	return PlayerOwner;
}

void ATile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

UStaticMeshComponent* ATile::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}



// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

