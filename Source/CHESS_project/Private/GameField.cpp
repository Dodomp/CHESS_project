// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"
#include "ThePawn.h"
#include "Tower.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "BasePiece.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGameField::AGameField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Dimensions of field
	Size = 8;
	TileSize = 120;
	PieceSize = 10;



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



void AGameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++) {
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj;
			if (((x + y) % 2) == 0) {
				Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location+ FVector(0.0f, 0.0f, -10) , FRotator::ZeroRotator);
				Obj->StaticMeshComponent->SetMaterial(0, Obj->Black);
			}
			else {
				Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location+ FVector(0.0f, 0.0f, -10), FRotator::ZeroRotator);
				Obj->StaticMeshComponent->SetMaterial(0, Obj->White);
			}
			if( Obj) {
				const float TileScale = TileSize / 100;
				Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
				Obj->SetGridPosition(x, y);
				TileArray.Add(Obj);
				TileMap.Add(FVector2D(x, y), Obj);
			}

			PlacePeaces(x, y, this);
		}
	}
}

void AGameField::PlacePeaces(int32 InX, int32 InY, AGameField* GF)
{
	FVector Location = AGameField::GetRelativeLocationByXYPosition(InX, InY);
	if (InX == 1 || InX==6) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AThePawn>(PawnClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 6);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		if (InX == 6) {
			Piece->PlayerOwner = 1;
			(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
			BlackPieceArray.Add(Piece);
		}
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
	}

	if ((InX == 0 || InX ==7)  && (InY == 0 || InY==7)) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<ATower>(TowerClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 7);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		if (InX == 7) {
			Piece->PlayerOwner = 1;
			(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
			BlackPieceArray.Add(Piece);
		}
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
	}
	
	if ((InX == 0 || InX == 7) && (InY == 1 || InY == 6)){
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 7);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		if (InX == 7) {
			Piece->PlayerOwner = 1;
			(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
			BlackPieceArray.Add(Piece);
		}
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
	}

	if ((InX == 0 || InX == 7) && (InY == 2 || InY == 5)) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<ABishop>(BishopClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 7);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		if (InX == 7) {
			Piece->PlayerOwner = 1;
			(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
			BlackPieceArray.Add(Piece);
		}
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);

	}

	//WhiteQueen on White Tile
	if (InX == 0 && InY == 3) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(false);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);

	}

	//White King
	if (InX == 0 && InY == 4) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AKing>(KingClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(false);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 0;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 0;
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
		KingGridPosition.Add(FVector2D(InX, InY));

	}

	//Black Queen on Black Tile
	if (InX == 7 && InY == 3) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 7);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 1;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
		BlackPieceArray.Add(Piece);
	}

	//Black King
	if (InX == 7 && InY == 4) {
		ABasePiece* Piece;
		Piece = GetWorld()->SpawnActor<AKing>(KingClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		Piece->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Piece->ApplyMaterial(InX == 7);
		Piece->SetGridPosition(InX, InY);
		Piece->PlayerOwner = 1;
		(*TileMap.Find(FVector2D(InX, InY)))->PlayerOwner = 1;
		Piece->GameField = GF;
		if (TileMap.Find(FVector2D(InX, InY)) != nullptr) {
			(*TileMap.Find(FVector2D(InX, InY)))->Status = ETileStatus::OCCUPIED;
		}
		PieceArray.Add(Piece);
		KingGridPosition.Add(FVector2D(InX, InY));
		BlackPieceArray.Add(Piece);

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

void AGameField::PaintTiles(TArray<FVector2D> moves)
{
	for (int i = 0; i < moves.Num(); i++) {
		if (TileMap.Find(moves[i]) != nullptr && (*TileMap.Find(moves[i]))->GetGridPosition() != FVector2D(-1, -1)) {
			(*TileMap.Find(moves[i]))->StaticMeshComponent->SetMaterial(0, (*TileMap.Find(moves[i]))->Green);
		}
	}
}

TArray<FVector2D> AGameField::HighlightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove) {

	TArray<FVector2D> LegalMoves;

	switch (Nome) {

	case ENamePiece::PAWN:
		
		LegalMoves = PawnMoves(Nome, proprietario, position, FirstMove);
		break;

	case ENamePiece::TOWER:
		LegalMoves = TowerMoves(Nome, proprietario, position, false);
		break;

	case ENamePiece::KNIGHT:
		LegalMoves = KnightMoves(Nome, proprietario, position, false);
		break;


	case ENamePiece::BISHOP:
		LegalMoves = BishopMoves(Nome, proprietario, position, false);
		break;


	case ENamePiece::QUEEN:
		LegalMoves = QueenMoves(Nome, proprietario, position, false);
		break;


	case ENamePiece::KING:
		LegalMoves = KingMoves(Nome, proprietario, position, false);
		break;
	

			

	}


	return LegalMoves;

}

void AGameField::Update(ABasePiece* Piece, ATile* NewTile)
{
	//I change the status, playerOwner della tile su cui � ancora il pezzo
	//cerco la tile
	ATile* OldTile = *TileMap.Find(FVector2D(Piece->PieceGridPosition));
	OldTile->Status = ETileStatus::EMPTY;
	OldTile->PlayerOwner = -1;

	//cambio la gridpostion del pezzo
	Piece->PieceGridPosition = NewTile->GetGridPosition();

	//aggiorno la tile su cui andr� il pezzo : status, player owner
	NewTile->PlayerOwner = Piece->PlayerOwner;
	NewTile->Status = ETileStatus::OCCUPIED;

	if (Piece->Name == ENamePiece::KING) {
		Piece->GameField->KingGridPosition[Piece->PlayerOwner] = NewTile->TileGridPosition;
	}
}

void AGameField::SwapTile(ABasePiece* Piece, ATile* StartTile, ATile* EndTile)
{
	StartTile->Status = ETileStatus::EMPTY;
	StartTile->PlayerOwner = -1;

	EndTile->Status = ETileStatus::OCCUPIED;
	EndTile->PlayerOwner = Piece->PlayerOwner;

	if (Piece->Name == ENamePiece::KING) {
		KingGridPosition[Piece->PlayerOwner] = EndTile->TileGridPosition;
	}

}

void AGameField::RollBack(ABasePiece* Piece, ATile* StartTile, ATile* EndTile, int32 proprietario) 
{
	if (proprietario == -1) {
		StartTile->Status = ETileStatus::EMPTY;
		StartTile->PlayerOwner = -1;
	}
	else {
		StartTile->Status = ETileStatus::OCCUPIED;
		StartTile->PlayerOwner = proprietario;
	}


	EndTile->Status = ETileStatus::OCCUPIED;
	EndTile->PlayerOwner = Piece->PlayerOwner;

	if (Piece->Name == ENamePiece::KING) {
		KingGridPosition[Piece->PlayerOwner] = EndTile->TileGridPosition;
	}
}




void AGameField::Discoloration()
{
	for (int32 x = 0; x < Size; x++) {
		for (int32 y = 0; y < Size; y++) {
			if ( (x+y) % 2 == 0) {
				if ((*TileMap.Find(FVector2D(x, y)))->Black) {
					(*TileMap.Find(FVector2D(x, y)))->StaticMeshComponent->SetMaterial(0, (*TileMap.Find(FVector2D(x, y)))->Black);
				}
			}
			else {
				(*TileMap.Find(FVector2D(x, y)))->StaticMeshComponent->SetMaterial(0, (*TileMap.Find(FVector2D(x, y)))->White);
			}
		}
		
	}
}

TArray<FVector2D> AGameField::PawnMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;
	//nord direction
	if (proprietario == 0) {
		if (IsValidPosition(FVector2D(position.X + 1, position.Y))) {
			if ((*TileMap.Find(FVector2D(position.X + 1, position.Y)))->GetTileStatus() == ETileStatus::EMPTY) {
				LegalMoves.Add(FVector2D(position.X + 1, position.Y));
				if (IsValidPosition(FVector2D(position.X + 2, position.Y)) && !FirstMove) {
					if ((*TileMap.Find(FVector2D(position.X + 2, position.Y)))->GetTileStatus() == ETileStatus::EMPTY) {
						LegalMoves.Add(FVector2D(position.X + 2, position.Y));
					}
				}
			}
		}

		



		if (IsValidPosition(FVector2D(position.X + 1, position.Y - 1))) {
			if ((*TileMap.Find(FVector2D(position.X + 1, position.Y - 1)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + 1, position.Y - 1)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X + 1, position.Y - 1));
			}
		}

		if (IsValidPosition(FVector2D(position.X + 1, position.Y + 1))) {
			if ((*TileMap.Find(FVector2D(position.X + 1, position.Y + 1)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + 1, position.Y + 1)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X + 1, position.Y + 1));
			}
		}
	}

	if (proprietario == 1) {

		if(IsValidPosition(FVector2D(position.X -1, position.Y))) {
			if ((*TileMap.Find(FVector2D(position.X - 1, position.Y)))->GetTileStatus() == ETileStatus::EMPTY) {
				LegalMoves.Add(FVector2D(position.X - 1, position.Y));
				if (IsValidPosition(FVector2D(position.X - 2, position.Y)) && !FirstMove) {
					if ((*TileMap.Find(FVector2D(position.X - 2, position.Y)))->GetTileStatus() == ETileStatus::EMPTY) {
						LegalMoves.Add(FVector2D(position.X - 2, position.Y));
					}
				}
			}
		}

		



		if (IsValidPosition(FVector2D(position.X - 1, position.Y - 1))) {
			if ((*TileMap.Find(FVector2D(position.X - 1, position.Y - 1)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - 1, position.Y - 1)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X - 1, position.Y - 1));
			}
		}

		if (IsValidPosition(FVector2D(position.X - 1, position.Y + 1))) {
			if ((*TileMap.Find(FVector2D(position.X - 1, position.Y + 1)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - 1, position.Y + 1)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X - 1, position.Y + 1));
			}
		}

	}


	return LegalMoves;
}

TArray<FVector2D> AGameField::TowerMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;

	//nord direction
	for (int32 i = position.X + 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(i, position.Y))) {
			if ((*TileMap.Find(FVector2D(i, position.Y)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(i, position.Y)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(i, position.Y)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(i, position.Y)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(i, position.Y));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(i, position.Y));
			}
		}

	}
	//south direction
	for (int32 i = position.X - 1; i > -1; i--) {
		if (IsValidPosition(FVector2D(i, position.Y))) {
			if ((*TileMap.Find(FVector2D(i, position.Y)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(i, position.Y)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(i, position.Y)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(i, position.Y)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(i, position.Y));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(i, position.Y));
			}
		}

	}
	//est direction
	for (int32 i = position.Y + 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(position.X, i))) {
			if ((*TileMap.Find(FVector2D(position.X, i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X, i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X, i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X, i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X, i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X, i));
			}
		}

	}
	//west direction
	for (int32 i = position.Y - 1; i > -1; i--) {
		if (IsValidPosition(FVector2D(position.X, i))) {
			if ((*TileMap.Find(FVector2D(position.X, i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X, i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X, i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X, i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X, i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X, i));
			}
		}

	}

	return LegalMoves;
}

TArray<FVector2D> AGameField::KnightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;

	//nord direction
	if (IsValidPosition(FVector2D(position.X + 2, position.Y - 1)) && ((*TileMap.Find(FVector2D(position.X + 2, position.Y - 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 2, position.Y - 1)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X + 2, position.Y - 1));
	}
	if (IsValidPosition(FVector2D(position.X + 2, position.Y + 1)) && ((*TileMap.Find(FVector2D(position.X + 2, position.Y + 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 2, position.Y + 1)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X + 2, position.Y + 1));
	}
	//south direction
	if (IsValidPosition(FVector2D(position.X - 2, position.Y - 1)) && ((*TileMap.Find(FVector2D(position.X - 2, position.Y - 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 2, position.Y - 1)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X - 2, position.Y - 1));
	}
	if (IsValidPosition(FVector2D(position.X - 2, position.Y + 1)) && ((*TileMap.Find(FVector2D(position.X - 2, position.Y + 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 2, position.Y + 1)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X - 2, position.Y + 1));
	}
	//est directio
	if (IsValidPosition(FVector2D(position.X + 1, position.Y + 2)) && ((*TileMap.Find(FVector2D(position.X + 1, position.Y + 2)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 1, position.Y + 2)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X + 1, position.Y + 2));
	}
	if (IsValidPosition(FVector2D(position.X - 1, position.Y + 2)) && ((*TileMap.Find(FVector2D(position.X - 1, position.Y + 2)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 1, position.Y + 2)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X - 1, position.Y + 2));
	}
	//west direction
	if (IsValidPosition(FVector2D(position.X + 1, position.Y - 2)) && ((*TileMap.Find(FVector2D(position.X + 1, position.Y - 2)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 1, position.Y - 2)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X + 1, position.Y - 2));
	}
	if (IsValidPosition(FVector2D(position.X - 1, position.Y - 2)) && ((*TileMap.Find(FVector2D(position.X - 1, position.Y - 2)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 1, position.Y - 2)))->PlayerOwner != proprietario)) {
		LegalMoves.Add(FVector2D(position.X - 1, position.Y - 2));
	}

	return LegalMoves;
}

TArray<FVector2D> AGameField::BishopMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;

	//nord east direction: x increases, y increases
	for (int32 i = 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(position.X + i, position.Y + i))) {
			if ((*TileMap.Find(FVector2D(position.X + i, position.Y + i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + i, position.Y + i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X + i, position.Y + i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + i, position.Y + i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X + i, position.Y + i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X + i, position.Y + i));
			}
		}
		else break;
	}
	//nord-west direction: y decreases and x increases
	for (int32 i = 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(position.X + i, position.Y - i))) {
			if ((*TileMap.Find(FVector2D(position.X + i, position.Y - i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + i, position.Y - i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X + i, position.Y - i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X + i, position.Y - i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X + i, position.Y - i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X + i, position.Y - i));
			}
		}
		else break;

	}
	//south-west direction: x decreases and y decreases
	for (int32 i = 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(position.X - i, position.Y - i))) {
			if ((*TileMap.Find(FVector2D(position.X - i, position.Y - i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - i, position.Y - i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X - i, position.Y - i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - i, position.Y - i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X - i, position.Y - i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X - i, position.Y - i));
			}
		}
		else break;
	}
	//south-east direction: x decreases and y increases
	for (int32 i = 1; i < Size; i++) {
		if (IsValidPosition(FVector2D(position.X - i, position.Y + i))) {
			if ((*TileMap.Find(FVector2D(position.X - i, position.Y + i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - i, position.Y + i)))->PlayerOwner == proprietario) break;
			else if ((*TileMap.Find(FVector2D(position.X - i, position.Y + i)))->GetTileStatus() == ETileStatus::OCCUPIED && (*TileMap.Find(FVector2D(position.X - i, position.Y + i)))->PlayerOwner != proprietario) {
				LegalMoves.Add(FVector2D(position.X - i, position.Y + i));
				break;
			}
			else {
				LegalMoves.Add(FVector2D(position.X - i, position.Y + i));
			}
		}
		else break;

	}

	return LegalMoves;
}

TArray<FVector2D> AGameField::QueenMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;
	//re-use tower and bishop moves
	LegalMoves = TowerMoves(Nome, proprietario, position, false);
	LegalMoves.Append(BishopMoves(Nome, proprietario, position, false));

	return LegalMoves;
}

TArray<FVector2D> AGameField::KingMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove)
{
	TArray<FVector2D> LegalMoves;

	//nord direction
	if (IsValidPosition(FVector2D(position.X + 1, position.Y))) {
		if ((*TileMap.Find(FVector2D(position.X + 1, position.Y)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 1, position.Y)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X + 1, position.Y));
		}
	}
	 //south direction
	if (IsValidPosition(FVector2D(position.X - 1, position.Y))) {
		if ((*TileMap.Find(FVector2D(position.X - 1, position.Y)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 1, position.Y)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X - 1, position.Y));
		}
	}

	//est direction
	if (IsValidPosition(FVector2D(position.X, position.Y+1))) {
		if ((*TileMap.Find(FVector2D(position.X, position.Y+1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X, position.Y+1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X, position.Y+1));
		}
	}

	//west direction
	if (IsValidPosition(FVector2D(position.X, position.Y - 1))) {
		if ((*TileMap.Find(FVector2D(position.X, position.Y - 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X, position.Y - 1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X, position.Y - 1));
		}
	}

	//nord-est direction
	if (IsValidPosition(FVector2D(position.X+1, position.Y + 1))) {
		if ((*TileMap.Find(FVector2D(position.X+1, position.Y + 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X+1, position.Y + 1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X+1, position.Y + 1));
		}
	}

	//south-west direction
	if (IsValidPosition(FVector2D(position.X - 1, position.Y - 1))) {
		if ((*TileMap.Find(FVector2D(position.X - 1, position.Y - 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 1, position.Y - 1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X - 1, position.Y - 1));
		}
	}

	//south-east direction
	if (IsValidPosition(FVector2D(position.X - 1, position.Y + 1))) {
		if ((*TileMap.Find(FVector2D(position.X - 1, position.Y + 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X - 1, position.Y + 1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X - 1, position.Y + 1));
		}
	}

	//nord-west direction
	if (IsValidPosition(FVector2D(position.X + 1, position.Y - 1))) {
		if ((*TileMap.Find(FVector2D(position.X + 1, position.Y - 1)))->GetTileStatus() == ETileStatus::EMPTY || (*TileMap.Find(FVector2D(position.X + 1, position.Y - 1)))->PlayerOwner != proprietario) {
			LegalMoves.Add(FVector2D(position.X + 1, position.Y - 1));
		}
	}


	return LegalMoves;
}

void AGameField::Eaten(ABasePiece* Lived, ABasePiece* Dead)
{
	ATile* EndTile = *TileMap.Find(FVector2D(Dead->PieceGridPosition));
	//remove piece form PieceArray
	for (int32 i = 0; i < PieceArray.Num(); i++) {
		if (Dead == PieceArray[i]) {
			PieceArray.Remove(Dead);
		}
	}
	//remove piece from BlackPieceArray if required
	if (Dead->PlayerOwner == 1) {
		for (int32 i = 0; i < BlackPieceArray.Num(); i++) {
			if (Dead == BlackPieceArray[i]) {
				BlackPieceArray.Remove(Dead);
			}
		}
	}
	Dead->Destroy();

	Update(Lived, EndTile);
}

TArray<FVector2D> AGameField::LegalMoves(ABasePiece* Piece)
{
	TArray<FVector2D> IpoteticalMoves = Piece->PossibleMoves();

	TArray<FVector2D> Legal;

	for (int32 i = 0; i < IpoteticalMoves.Num(); i++) {

		//simulation of a piece
		ATile* StartTile = (*TileMap.Find(FVector2D(Piece->PieceGridPosition)));
		ATile* EndTile = (*TileMap.Find(FVector2D(IpoteticalMoves[i])));
		ABasePiece* temp = nullptr;
		if (EndTile->PlayerOwner != Piece->PlayerOwner) {
			for (int32 k = 0; k < PieceArray.Num(); k++) {
				if (PieceArray[k]->PieceGridPosition == EndTile->TileGridPosition) {
					temp = PieceArray[k];
					PieceArray.RemoveAt(k);
					break;
					
				}
			}
		}
		int32 OtherTileOwner = EndTile->PlayerOwner;
		SwapTile(Piece, StartTile, EndTile);

		//check if there are some problems
		for (int32 j = 0; j < PieceArray.Num(); j++) {
			if (PieceArray[j]->PlayerOwner != Piece->PlayerOwner) {
				TArray<FVector2D> EnemyMoves = PieceArray[j]->PossibleMoves();
				if (EnemyMoves.Find(FVector2D(KingGridPosition[Piece->PlayerOwner])) != -1) {
					IpoteticalMoves[i] = FVector2D (- 1, -1);
					
				}
			}
		}

		//go back to old situation
		RollBack(Piece, EndTile, StartTile, OtherTileOwner);
		if (temp != nullptr) {
			PieceArray.Add(temp);
		}
	}

	//delete all non-legal moves
	for (int32 i = 0; i < IpoteticalMoves.Num(); i++) {
		if (IpoteticalMoves[i] != FVector2D(-1, -1)) Legal.Add(IpoteticalMoves[i]);
	}

	return Legal;
}

bool AGameField::isCheckMate(int32 Player)
{	
	//if any piece is able to do almost one legal moves, the player is in checkmate situation
	for (int32 i = 0; i < PieceArray.Num(); i++) {
		//Take a piece
		if (PieceArray[i]->PlayerOwner == Player) {
			//calculate a legal moves
			if (!LegalMoves(PieceArray[i]).IsEmpty()) {
				return false;
			}
		}
	}
	return true;
}

void AGameField::Promotion(ABasePiece* Piece)
{
	if (Piece->PieceGridPosition.X == Size - 1 || Piece->PieceGridPosition.X == 0) {
		FVector Location = AGameField::GetRelativeLocationByXYPosition(Piece->PieceGridPosition.X, Piece->PieceGridPosition.Y);
		
		//spawn a queen
		ABasePiece* NewQueen;
		NewQueen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotator(0.0f, 90.0f, 0.0f));
		const float PieceScale = TileSize / 100;
		NewQueen->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		NewQueen->ApplyMaterial(Piece->PieceGridPosition.X == 0);
		NewQueen->SetGridPosition(Piece->PieceGridPosition.X, Piece->PieceGridPosition.Y);
		NewQueen->PlayerOwner = Piece->PlayerOwner;
		(*TileMap.Find(FVector2D(NewQueen->PieceGridPosition.X, NewQueen->PieceGridPosition.Y)))->PlayerOwner = Piece->PlayerOwner;
		if (Piece->PieceGridPosition.X == 0) {
			BlackPieceArray.Add(Piece);
		}
		NewQueen->GameField = this;
		PieceArray.Add(NewQueen);

		//Update PieceArray
		for (int32 i = 0; i < PieceArray.Num(); i++) {
			if (Piece == PieceArray[i]) {
				PieceArray.Remove(Piece);
			}
		}
		//Update BlackPieceArray
		if (Piece->PlayerOwner == 1) {
			for (int32 i = 0; i < BlackPieceArray.Num(); i++) {
				if (Piece == BlackPieceArray[i]) {
					BlackPieceArray.Remove(Piece);
				}
			}
		}
		Piece->Destroy();

	}
}



