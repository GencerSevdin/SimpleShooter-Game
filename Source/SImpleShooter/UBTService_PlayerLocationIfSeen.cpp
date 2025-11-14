// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_PlayerLocationIfSeen.h"

#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UUBTService_PlayerLocationIfSeen::UUBTService_PlayerLocationIfSeen()
{
	NodeName = "Player Location If Seen";
}

void UUBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;
	if (OwnerComp.GetAIOwner() == nullptr) return;
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) OwnerComp.GetBlackboardComponent()->
								SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn );
	else OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}