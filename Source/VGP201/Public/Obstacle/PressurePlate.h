// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AI/EnemyAICharacter.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlateStateChanged);	//Will let the door know when to update it's array

UCLASS()
class VGP201_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(VisibleAnywhere)	//Triggers when enemy steps on
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PlateMesh;	//Going to attempt to chnage it visually when stepped on

	UPROPERTY(BlueprintReadOnly)	//If stepped on
	bool bIsActive = false;

	UPROPERTY(BlueprintAssignable)	//Will let the door know when to update it's array
	FOnPlateStateChanged OnPlateStateChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
