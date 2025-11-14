// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFrameWork/Controller.h"
void AKillEmAllGameMode::PawnKiled(APawn* PawnKilled)
{
	Super::PawnKiled(PawnKilled);

 	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
	//For loop over ShooterAI in world:
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	}
		//Is not dead ?
			//return
	//End game
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// Dunyada yer alan tum kontrolculeri tara
	for ( AController* Controller : TActorRange<AController>(GetWorld()))
	{
		//EndGame fonksiyonu cagirildiginda kazanan karaktere kontrolcunun  oyuncuya veya AI'ya ait olma kosuluna gore 
		//bool degiskenine true veya false olarak ekle
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		//bIsWinner degiskenine gore oyunun tamamlanip tamamlanmadigini belirle
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
