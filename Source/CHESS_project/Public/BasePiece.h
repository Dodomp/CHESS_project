// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include <cstdint>
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "BasePiece.generated.h"



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

	AGameField* GameField;

	TArray<FVector2D> SuggestMoves;

	ENamePiece Name;

	void SetGridPosition(const double InX, const double InY);

	void SetPlayerOwner(const int32 TileOwner);

	void SetGameField(AGameField* GF);

	UFUNCTION(BlueprintCallable)
	void ApplyMaterial(bool value);
	
	virtual TArray<FVector2D> PossibleMoves();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
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
