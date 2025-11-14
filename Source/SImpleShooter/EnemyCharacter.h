// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AEnemyCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;
	private:
	
	
};
