// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP201_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    virtual void NativeConstruct() override;

    // Buttons bound in Blueprint
    UPROPERTY(meta = (BindWidget))
    UButton* PlayButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

    // Functions called when buttons are clicked
    UFUNCTION()
    void OnPlayClicked();

    UFUNCTION()
    void OnMainMenuQuitClicked();
	
};
