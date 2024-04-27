// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Tile.h"
//#include "BasePiece.h"
#include <cstdint>
#include "GameFramework/Actor.h"
#include "GameField.generated.h"


enum class ENamePiece : uint8;
class ABasePiece;
class AThePawn;
class ATower;
class AKnight;
class ABishop;
class AQueen;
class AKing;



//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset);


UCLASS()
class CHESS_PROJECT_API AGameField : public AActor
{
	GENERATED_BODY()

public:
	// keeps track of tiles
	UPROPERTY(Transient)
		TArray<ATile*> TileArray;

	//given a position returns a tile
	UPROPERTY(Transient)
		TMap<FVector2D, ATile*> TileMap;

	UPROPERTY(Transient)
		TArray<ABasePiece*> PieceArray;

	UPROPERTY(Transient)
		TArray<ABasePiece*> BlackPieceArray;


	//in any moment I can find the black and white kings
	UPROPERTY(Transient)
		TArray<FVector2D>KingGridPosition;




	static const int32 NOT_ASSIGNED = -1;


	// size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Size;
	


	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATile> TileClass;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AThePawn> PawnClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATower> TowerClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AKnight> KnightClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABishop> BishopClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AQueen> QueenClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AKing> KingClass;



	// tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float PieceSize;


	// Sets default values for this actor's properties
	AGameField();

	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// remove all signs from the field
	UFUNCTION(BlueprintCallable)
		void ResetField();

	// generate an empty game field
	void GenerateField();

	// this method places all pieces at very start of the game
	void PlacePeaces(int32 InX, int32 InY, AGameField* GF);

	// return a (x,y) position given a hit (click) on a field tile
	FVector2D GetPosition(const FHitResult& Hit);

	// return the array of tile pointers
	TArray<ATile*>& GetTileArray();


	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) position given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;


	// checking if is a valid field position
	inline bool IsValidPosition(const FVector2D Position) const;

	
	//this method allow to change material when the player  selects a piece and visualizes all legal moves
	void PaintTiles(TArray<FVector2D> moves);

	// this method calculate legal moves for each each peach
	TArray<FVector2D> HighlightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	//when the player move his peace the new tile will became OCCUPIED as well as the player owner of tile.
	//It also update the PieceGridPosition of Piece and the KingGridPosition if required
	void Update(ABasePiece* Piece, ATile* Tile);

	//Method simulates one of the all legal moves of piece
	void SwapTile(ABasePiece* Piece, ATile* StartTile, ATile* EndTile);

	//After a simulation this method restores the old situation
	void RollBack(ABasePiece* Piece, ATile* StartTile, ATile* EndTile, int32 proprietario);


	//This method deletes all suggest and colors all tile in white and black
	void Discoloration();

	//Theese methods find all possible moves which different piecese are able to do

	TArray<FVector2D> PawnMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> TowerMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> KnightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> BishopMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> QueenMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> KingMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);


	//This method allow to capture a piece
	void Eaten(ABasePiece* Lived, ABasePiece* Dead);

	//After finding all possible moves for a picese, I delete all illegal moves such as a moves which puts the king in check situation
	TArray<FVector2D> LegalMoves(ABasePiece* Piece);

	//at the start of every turn this method controll if the current player is in chackmate situation
	bool isCheckMate(int32 Player);
	
	//When a pawn reach the end of game field, it transforms in a Queen
	void Promotion(ABasePiece* Piece);



};
