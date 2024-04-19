// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "GameField.h"
//#include "Tile.h"
#include "ThePawn.h"
#include "CHESS_GameMode.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values
AHumanPlayer::AHumanPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// create a camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//set the camera as RootComponent
	//SetRootComponent(Camera);
	// get the game instance reference
	GameInstance = Cast<UCHESS_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// default init values
	PlayerNumber = -1;
	Color = EColor::NotDefined;

	TempPiece = nullptr;

}
//Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHumanPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Daje"));
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

void AHumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	GameInstance->IncrementScoreHumanPlayer();
}

void AHumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}

void AHumanPlayer::OnClick()
{
	//ABasePiece* CurrPiece;
	//ATile* CurrTile;
	UE_LOG(LogTemp, Error, TEXT("OnClick passa1"));
	ACHESS_GameMode* GameMode = Cast<ACHESS_GameMode>(GetWorld()->GetAuthGameMode());
	//Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
	FHitResult Hit = FHitResult(ForceInit);
	// GetHitResultUnderCursor function sends a ray from the mouse position and gives the corresponding hit results
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	if (!GameMode->GField->isCheckMate(PlayerNumber)) {
		if (Hit.bBlockingHit && IsMyTurn)
		{
			if (GameMode->GField->isCheckMate(PlayerNumber)) {

			}
			if (ABasePiece* CurrPiece = Cast<ABasePiece>(Hit.GetActor())) {

				if (CurrPiece != TempPiece && TempPiece != nullptr && CurrPiece->PlayerOwner == GameMode->CurrentPlayer) {
					DeleteSuggestion(TempPiece);
				}

				if (CurrPiece->PlayerOwner == GameMode->CurrentPlayer) {
					TempPiece = CurrPiece;
					//TempMoves = TempPiece->PossibleMoves();
					//faccio il controllo e tolgo le mosse che potrebbero mettere in scacco il re
					TempMoves = FindLegalMoves(TempPiece);
					CurrPiece->GameField->PaintTiles(TempMoves);



				}

				if (CurrPiece != TempPiece && TempPiece != nullptr && CurrPiece->PlayerOwner != GameMode->CurrentPlayer) {

					Eat(TempPiece, CurrPiece);
					GameMode->SetCellSign(PlayerNumber);
					IsMyTurn = false;
				}

			}
			if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
			{
				if (TempMoves.Find(FVector2D(CurrTile->GetGridPosition())) != INDEX_NONE) {
					if (TempPiece != nullptr) {
						AGameField* GF = TempPiece->GameField;
						FVector EndPosition = GF->GetRelativeLocationByXYPosition(CurrTile->GetGridPosition().X, CurrTile->GetGridPosition().Y);
						UpdateTiles(TempPiece, CurrTile);
						TempPiece->SetActorLocation(EndPosition);
						DeleteSuggestion(TempPiece);
						TempMoves.Empty();
						TempPiece = nullptr;
						GameMode->TurnNextPlayer();
						IsMyTurn = false;

					}
				}
			}
		}
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

void AHumanPlayer::UpdateTiles(ABasePiece* Piece, ATile* Tile) {
	//devo aggiornare lo status, il playerOwner
	AGameField* GameField = Piece->GameField;
	GameField->Update(Piece, Tile);

}


void AHumanPlayer::DeleteSuggestion(ABasePiece* Piece) {

	AGameField* GameField = Piece->GameField;
	GameField->Discoloration();

}

void AHumanPlayer::Eat(ABasePiece* Lived, ABasePiece* Dead)
{
	AGameField* GF = TempPiece->GameField;
	FVector EndPosition = GF->GetRelativeLocationByXYPosition(Dead->GetGridPosition().X, Dead->GetGridPosition().Y);
	GF->Eaten(Lived, Dead);
	TempPiece->SetActorLocation(EndPosition);
	DeleteSuggestion(TempPiece);
	TempMoves.Empty();
	TempPiece = nullptr;

}

TArray<FVector2D> AHumanPlayer::FindLegalMoves(ABasePiece* Piece)
{
	return Piece->GameField->LegalMoves(Piece);
}
