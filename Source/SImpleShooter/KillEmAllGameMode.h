// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameMode.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameMode
{
	GENERATED_BODY()
	UFUNCTION(blueprintCallable, Category = "KillEmAllGameMode")
	virtual void PawnKiled(APawn* PawnKilled) override;
private:
	void EndGame(bool bIsPlayerWinner);

};



