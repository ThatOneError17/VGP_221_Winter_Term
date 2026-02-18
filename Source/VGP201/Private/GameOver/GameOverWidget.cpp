// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver/GameOverWidget.h"

void UGameOverWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ReturnToMenuButton)
    {
        ReturnToMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnReturnToMenuButtonClicked);
    }
}

void UGameOverWidget::OnReturnToMenuButtonClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
