// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePiece.h"

// Sets default values
ABasePiece::ABasePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// every actor has a RootComponent that defines the transform in the World
	//attacco l'actor scena alla staticMesh
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	
	//non appartiene a nessun giocatore
	PlayerOwner = -1;

	//centrata nell'origine degli assi
	PieceGridPosition = FVector2D(0, 0);

}

int32 ABasePiece::GetPlayerOwner()
{
	return PlayerOwner;
}

FVector2D ABasePiece::GetGridPosition()
{
	return PieceGridPosition;
}

void ABasePiece::SetGridPosition(const double InX, const double InY)
{
	PieceGridPosition.Set(InX, InY);
}

void ABasePiece::SetPlayerOwner(const int32 PieceOwner)
{
	PlayerOwner = PieceOwner;
}

// Called when the game starts or when spawned
void ABasePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

