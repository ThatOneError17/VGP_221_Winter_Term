// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UpdateHealthBar(1.0f);
	//SetScoreText(0);
	//SetTimerText(60);

	//Example of adding buttons dynamically
	//for (int i = 0; i < 4; i++) {
		//UUserWidget* Widget = CreateWidget(GetWorld(), ButtonWidgetClass);
		//ButtonContainer->AddChild(Widget);

		//UButtonWidget* ButtonWidget = Cast<UButtonWidget>(Widget);
		//ButtonWidget->SetText(i + 1);
	//}
}

void UGameMenuWidget::UpdateHealthBar(float HealthPercent)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(HealthPercent);
}

void UGameMenuWidget::SetScoreText(int amount)
{
	if (!ScoreText) return;

	UIScore += amount;
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("SCORE: %d"), UIScore)));
}

void UGameMenuWidget::SetTimerText(int timer)
{
	if (!TimerText) return;

	TimerText->SetText(FText::FromString(FString::Printf(TEXT("TIME: %d"), timer)));
}
