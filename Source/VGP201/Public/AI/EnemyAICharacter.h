// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnemyAICharacter*, Enemy);	//Delegate to broadcast when the enemy dies, for updating score


UCLASS()
class VGP201_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnEnemyDied;	//Delegate to broadcast when the enemy dies, for updating score

	AEnemyAICharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnEnemyTakeDamage(float Amount);

	float DamageAmount = 10.0f;	

private:
	int Health = 100;

};
