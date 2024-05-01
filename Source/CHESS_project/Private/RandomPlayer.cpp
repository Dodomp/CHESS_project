// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPlayer.h"

// Sets default values
ARandomPlayer::ARandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameInstance = Cast<UCHESS_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called when the game starts or when spawned
void ARandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARandomPlayer::OnTurn()
{
	ACHESS_GameMode* GameMode = (ACHESS_GameMode*)(GetWorld()->GetAuthGameMode());
	if (!GameMode->GField->isCheckMate(PlayerNumber)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Turn"));
			GameInstance->SetTurnMessage(TEXT("AI (Random) Turn"));

			FTimerHandle TimerHandle;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
					ACHESS_GameMode* GameMode = (ACHESS_GameMode*)(GetWorld()->GetAuthGameMode());
					AGameField* GField = GameMode->GField;
					TArray<FVector2D> Moves;
					ABasePiece* Piece;

					do {
						// Keep extracting moves randomly until finding a valid one
						// Randomly extract a black piece
						Piece = GetRandomBlackPiece(GameMode);

						// Calculate all moves for the black piece
						Moves = GField->LegalMoves(Piece);

					} while (Piece != nullptr && Moves.IsEmpty());


					// Randomly extract a valid move
					// Color the moves
					GField->PaintTiles(Moves);

					FVector2D EndTile = GetRandomMove(Moves);
					FVector EndPosition = GField->GetRelativeLocationByXYPosition(EndTile.X, EndTile.Y);

					if (GField->TileMap.FindRef(FVector2D(EndTile))->Status == ETileStatus::OCCUPIED) {
						ABasePiece* Dead = nullptr;
						for (int32 i = 0; i < GField->PieceArray.Num(); i++) {
							if (GField->PieceArray[i]->PieceGridPosition == EndTile) {
								Dead = GField->PieceArray[i];
								break;
							}
						}
						GField->Eaten(Piece, Dead);
						Piece->SetActorLocation(EndPosition);
						if (Piece->Name == ENamePiece::PAWN) {
							Piece->HasMoved = true;
							GField->Promotion(Piece);
						}
						GField->Discoloration();

						GameMode->TurnNextPlayer();
						
					}

					else {
						ATile* DestinationTile = GField->TileMap.FindRef(FVector2D(EndTile));
						GField->Update(Piece, DestinationTile);
						Piece->SetActorLocation(EndPosition);
						if (Piece->Name == ENamePiece::PAWN) {
							Piece->HasMoved = true;
							GField->Promotion(Piece);
						}
						GField->Discoloration();

						GameMode->TurnNextPlayer();
						
					}
			}, 3, false);

	}
	else {
		OnLose();
		for (int32 i = 0; i < GameMode->Players.Num(); i++)
		{
			if (i != GameMode->CurrentPlayer)
			{
				GameMode->Players[i]->OnWin();
			}
		}
	}
}

void ARandomPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Wins!"));
	GameInstance->SetTurnMessage(TEXT("AI Wins!"));
	GameInstance->IncrementScoreAiPlayer();
}

void ARandomPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Loses!"));
	GameInstance->SetTurnMessage(TEXT("AI Loses!"));
}


ABasePiece* ARandomPlayer::GetRandomBlackPiece(ACHESS_GameMode* GameMode)
{
	// Assume BlackPieceArray is a TArray of the desired type (e.g., TArray<int32> or TArray<classname>)
	// It must be accessible from this context (e.g., declared as a class member)
	TArray<ABasePiece*> Black = GameMode->GField->BlackPieceArray;

	// Check if the array is not empty
	if (Black.Num() > 0)
	{
		// Generate a random index within the range of the array
		int32 RandomIndex = FMath::RandRange(0, Black.Num() - 1);

		// Access the random element
		return Black[RandomIndex];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("L'array è vuoto."));
		return nullptr;
	}
}

FVector2D ARandomPlayer::GetRandomMove(TArray<FVector2D> Moves)
{
		// Generate a random index within the array's range
		int32 RandomIndex = FMath::RandRange(0, Moves.Num() - 1);

		// Access the random element
		return Moves[RandomIndex];
}



