// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"

// Sets default values
AEnemyAIController::AEnemyAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!PawnSensing)
	{
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
	}

}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(StartingBehaviorTree);


	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject(TEXT("PlayerTarget"), PlayerPawn);
			BlackboardComp->SetValueAsFloat(TEXT("BBDamageAmount"), 10.0f);
		}
	}

}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(PlayerPawn);
	if (!PlayerCharacter) return;

	SetCanSeePlayer(true, PlayerCharacter);

}

void AEnemyAIController::SetCanSeePlayer(bool bCanSee, UObject* PlayerObject)
{
	UBlackboardComponent* BlackBoardComp = GetBlackboardComponent();
	BlackBoardComp->SetValueAsBool("CanSeePlayer", bCanSee);

	if(bCanSee)
	{
		BlackBoardComp->SetValueAsObject(TEXT("PlayerTarget"), PlayerObject);
	}

}

void AEnemyAIController::RunRetriggerableTimer()
{
	GetWorldTimerManager().ClearTimer(RetriggerableTimerHandle);
	//FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, nullptr);
	GetWorldTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}

