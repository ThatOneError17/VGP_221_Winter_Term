// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuGameMode.h"

void AMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("MainMenuGameMode BeginPlay"));

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC && MainMenuClass)
    {
        UMainMenuWidget* Menu = CreateWidget<UMainMenuWidget>(PC, MainMenuClass);
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