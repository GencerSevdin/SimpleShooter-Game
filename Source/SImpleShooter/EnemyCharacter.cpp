// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Gun.h"

 void AEnemyCharacter::BeginPlay() 
{
	Super::BeginPlay();
	for (auto Element : Guns)
	{
		
		GuntypeInArray->SetActorHiddenInGame(false);
		
	}
}
