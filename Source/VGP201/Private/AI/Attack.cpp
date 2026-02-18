// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Attack.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* EnemyController = OwnerComp.GetAIOwner();

	//Method 1: Built in damage system
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UGameplayStatics::ApplyDamage(PlayerCharacter, 1.0f, EnemyController, EnemyController->GetPawn(), UDamageType::StaticClass());

	//Method 2: Calling playerhurt function directly
	//AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//PlayerCharacter->OnHurtPlayer(1.0f);

	//Method 3: Using Pawn 
	//AEnemyAICharacter* EnemyCharacter = Cast<AEnemyAICharacter>(EnemyController->GetPawn());
	//AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//PlayerCharacter->OnHurtPlayer(EnemyCharacter->DamageAmount);

	//Method 4: Using Blackboard
	//float BBDamageAmount = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("BBDamageAmount"));
	//AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//PlayerCharacter->OnHurtPlayer(BBDamageAmount);

	return EBTNodeResult::Succeeded;
}
