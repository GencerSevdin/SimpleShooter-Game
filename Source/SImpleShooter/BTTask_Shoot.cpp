// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("OwnerComp.GetAIOwner() couldnt found"));
		return EBTNodeResult::Failed;
	}
	
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ShooterCharacter == nullptr )
	{
		UE_LOG(LogTemp, Log, TEXT("aaaa"));
		return EBTNodeResult::Failed;
	}
	
		ShooterCharacter->Fire();
	return EBTNodeResult::Succeeded;
}
