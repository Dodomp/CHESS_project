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



	static const int32 NOT_ASSIGNED = -1;

	// BlueprintAssignable Usable with Multicast Delegates only. Exposes the property for assigning in Blueprints.
	// declare a variable of type FOnReset (delegate)
	//UPROPERTY(BlueprintAssignable)
		//FOnReset OnResetEvent;

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

	void PlacePeaces(int32 InX, int32 InY, AGameField* GF);

	// return a (x,y) position given a hit (click) on a field tile
	FVector2D GetPosition(const FHitResult& Hit);

	// return the array of tile pointers
	TArray<ATile*>& GetTileArray();

	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) position given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	// check if a position is a win position
	//bool IsWinPosition(const FVector2D Position) const;

	// check if is a win line
	//inline bool IsWinLine(const FVector2D Begin, const FVector2D End) const;

	// checking if is a valid field position
	inline bool IsValidPosition(const FVector2D Position) const;

	// get a line given a begin and end positions
	//TArray<int32> GetLine(const FVector2D Begin, const FVector2D End) const;

	// check if a line contains all equal elements
	//bool AllEqual(const TArray<int32>& Array) const;

	void PaintTiles(TArray<FVector2D> moves);

	TArray<FVector2D> HighlightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	void Update(ABasePiece* Piece, ATile* Tile);

	void Discoloration(TArray<FVector2D> TilesColorated);

	TArray<FVector2D> PawnMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> TowerMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> KnightMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> BishopMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> QueenMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);

	TArray<FVector2D> KingMoves(ENamePiece Nome, int32 proprietario, FVector2D position, bool FirstMove);



};
