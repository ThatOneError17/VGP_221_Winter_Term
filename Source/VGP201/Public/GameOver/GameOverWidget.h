// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP201_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    // Bind to the button in Blueprint
    UPROPERTY(meta = (BindWidget))
    UButton* ReturnToMenuButton;

    UFUNCTION()
    void OnReturnToMenuButtonClicked();
	
};
