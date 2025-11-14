// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AiBehavior != nullptr)
	{
		RunBehaviorTree(AiBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), PlayerPawn->GetActorLocation());
		
	}
	
	
}
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
