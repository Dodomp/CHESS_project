// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include <cstdint>
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "BasePiece.generated.h"






//Every Piece has a name
UENUM()
enum class ENamePiece : uint8
{
	KING UMETA(DisplayName = "King"), 
	QUEEN UMETA(DisplayName = "Queen"),
	BISHOP UMETA(DisplayName = "Bishop"), 
	KNIGHT UMETA(DisplayName = "Knight"), 
	TOWER UMETA(DisplayName = "Tower"), 
	PAWN UMETA(DisplayName = "Pawn"), 
	
};




UCLASS()
class CHESS_PROJECT_API ABasePiece : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ABasePiece();

	int32 GetPlayerOwner();

	FVector2D GetGridPosition();

	//every piece has a reference to GameField
	AGameField* GameField;

	//Every piece has an array of possible moves, initially empty
	TArray<FVector2D> SuggestMoves;

	ENamePiece Name;

	bool HasMoved;

	void SetGridPosition(const double InX, const double InY);

	void SetPlayerOwner(const int32 TileOwner);

	void SetGameField(AGameField* GF);


	//this function changes material to a piece (balck or white)
	UFUNCTION(BlueprintCallable)
	void ApplyMaterial(bool value);

	//this vitual function permitts to find all possible and legal moves for each pieces
	virtual TArray<FVector2D> PossibleMoves();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 PlayerOwner;

	// (x, y) position of the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector2D PieceGridPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
		UMaterialInterface* White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
		UMaterialInterface* Black;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
