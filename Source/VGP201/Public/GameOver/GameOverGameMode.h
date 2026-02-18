// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VGP201_API AGameOverGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    //I'm going to assign in blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameOverWidget> GameOverWidgetClass;
	
};
