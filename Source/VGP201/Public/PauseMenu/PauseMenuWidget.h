// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "FPSProjectGameMode.h"
#include "PauseMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class VGP201_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

    virtual void NativeConstruct() override;

    //Bind to buttons created in Blueprint
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UFUNCTION()
    void OnQuitClicked();

    UFUNCTION()
    void HandleResumeClicked();

   

public:
    //Delegate to call when resume is clicked
    DECLARE_DELEGATE(FOnResumeClicked);
	FOnResumeClicked OnResumeClicked;   //For FPSCharacter to bind to, so that the character can unpause the game when resume is clicked

};
