// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GetRandomPatrolLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UGetRandomPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem)
	{
		NavSystem->K2_GetRandomPointInNavigableRadius(GetWorld(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), PatrolLocation, 2000.0f);
	}

	else
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("RandomPatrolLocation", PatrolLocation);

	return EBTNodeResult::Succeeded;
}