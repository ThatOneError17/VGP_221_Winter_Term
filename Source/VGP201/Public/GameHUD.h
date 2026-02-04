// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "GUI/SlateExample/SSSettingsWidget.h"
#include "GameHUD.generated.h"


UCLASS()
class VGP201_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//1. HUD Method of making UI
	virtual void DrawHUD() override;

	//2. Slates Method of making UI
	TSharedPtr<class SSSettingsWidget> SettingsWidget;
	TSharedPtr<class SWidget> SettingsWidgetContainer;

	void ShowSettingsMenu();
	void HideSettingsMenu();


public:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
	
};
