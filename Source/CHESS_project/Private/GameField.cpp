// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGameField::AGameField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Dimensions of field
	Size = 8;
	TileSize = 120;
	PieceSize = 120;



}

void AGameField::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();

}

void AGameField::ResetField()
{
	//for (ATile* Obj : TileArray)
	//{
	//	Obj->SetTileStatus(NOT_ASSIGNED, ETileStatus::EMPTY);
	//}

	//// send broadcast event to registered objects 
	//OnResetEvent.Broadcast();

	//ATTT_GameMode* GameMode = Cast<ATTT_GameMode>(GetWorld()->GetAuthGameMode());
	//GameMode->IsGameOver = false;
	//GameMode->MoveCounter = 0;
	//GameMode->ChoosePlayerAndStartGame();
}

void AGameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++) {
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj;
			ABasePiece* Piece;
			if (((x + y) % 2) == 0) {
				Obj = GetWorld()->SpawnActor<ATile>(TileClassBlack, Location, FRotator::ZeroRotator);
			}
			else {
				Obj = GetWorld()->SpawnActor<ATile>(TileClassWhite, Location, FRotator::ZeroRotator);
			}
			if( Obj) {
				const float TileScale = TileSize / 100;
				Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
				Obj->SetGridPosition(x, y);
				TileArray.Add(Obj);
				TileMap.Add(FVector2D(x, y), Obj);
			}
			if (x == 0 && y == 1) {
				Piece = GetWorld()->SpawnActor<ABasePiece>(PawnClassWhite, Location, FRotator::ZeroRotator);
			}
		}
	}
}

FVector2D AGameField::GetPosition(const FHitResult& Hit)
{
	return Cast<ATile>(Hit.GetActor())->GetGridPosition();
}

TArray<ATile*>& AGameField::GetTileArray()
{
	return TileArray;
}

FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, InY, 0);
}

FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = Location[0] / (TileSize);
	const double y = Location[1] / (TileSize);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), x, y));
	return FVector2D(x, y);
}

inline bool AGameField::IsValidPosition(const FVector2D Position) const
{
	return 0 <= Position[0] && Position[0] < Size && 0 <= Position[1] && Position[1] < Size;
}

// Called every frame
//void AGameField::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

//}

