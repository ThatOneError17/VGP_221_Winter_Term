// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PlayButton)
        PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnMainMenuQuitClicked);
}

void UMainMenuWidget::OnPlayClicked()
{
    //Loads main level
    UGameplayStatics::OpenLevel(this, FName("GameLevel"));
}

void UMainMenuWidget::OnMainMenuQuitClicked()
{
    //Quit the game
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
