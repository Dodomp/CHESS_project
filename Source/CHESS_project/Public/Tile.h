// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"
#include "Tile.generated.h"



UENUM()
enum class ETileStatus : uint8
{
	EMPTY     UMETA(DisplayName = "Empty"),
	OCCUPIED      UMETA(DisplayName = "Occupied"),
};



UCLASS()
class CHESS_PROJECT_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//COSTRUTTORE
	ATile();

	// set the player owner and the status of a tile
	void SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus);

	// get the tile status
	ETileStatus GetTileStatus();

	// get the tile owner
	int32 GetOwner();

	// set the (x, y) position
	void SetGridPosition(const double InX, const double InY);

	// get the (x, y) position
	FVector2D GetGridPosition();

	UStaticMeshComponent* GetStaticMeshComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;

//protected:

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ETileStatus Status;

	//intero per capire di chi � la tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 PlayerOwner;

	// (x, y) position of the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector2D TileGridPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
		UMaterialInterface* White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
		UMaterialInterface* Black;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
		UMaterialInterface* Green;

	




//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
