// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePiece.generated.h"

UCLASS()
class CHESS_PROJECT_API ABasePiece : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePiece();

	int32 GetPlayerOwner();

	FVector2D GetGridPosition();

	void SetGridPosition(const double InX, const double InY);

	void SetPlayerOwner(const int32 TileOwner);



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
		int32 PlayerOwner;

	// (x, y) position of the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector2D PieceGridPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
