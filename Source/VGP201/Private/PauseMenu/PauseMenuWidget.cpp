// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu/PauseMenuWidget.h"


void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ResumeButton)
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::HandleResumeClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitClicked);
}

void UPauseMenuWidget::HandleResumeClicked()
{
    if (OnResumeClicked.IsBound())
    {
        OnResumeClicked.Execute();
    }

}

void UPauseMenuWidget::OnQuitClicked()
{
    AFPSProjectGameMode* GameMode =
        Cast<AFPSProjectGameMode>(UGameplayStatics::GetGameMode(this));

    if (GameMode)
    {
        GameMode->GoToMainMenu();
    }
}
