// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ControlPlayerHealth.h"

#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ControlPlayerHealth::UBTTask_ControlPlayerHealth()
{
	NodeName  = "Control Player Health";
}

EBTNodeResult::Type UBTTask_ControlPlayerHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	 Super::ExecuteTask(OwnerComp, NodeMemory);
	 if (OwnerComp.GetAIOwner() == nullptr)
	 {
		 return EBTNodeResult::Failed;
	 }
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (ShooterCharacter == nullptr) return EBTNodeResult::Failed;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"),ShooterCharacter->IsDead());
	
	return EBTNodeResult::Succeeded;
}
