// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver/GameOverGameMode.h"

void AGameOverGameMode::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC && GameOverWidgetClass)
    {
        UGameOverWidget* Menu = CreateWidget<UGameOverWidget>(PC, GameOverWidgetClass);
        if (Menu)
        {
            Menu->AddToViewport();
            PC->bShowMouseCursor = true;

            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(Menu->TakeWidget());
            PC->SetInputMode(InputMode);
        }
    }
}