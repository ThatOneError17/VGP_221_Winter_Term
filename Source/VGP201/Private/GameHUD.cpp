// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Widgets/SWeakWidget.h"

// Called when the game starts or when spawned
void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	//2. Slates Method of making UI
	//ShowSettingsMenu();

	// 3. UMG Method of making UI (See GameMenuWidget)
	SpawnGameMenu(StartingGameWidget);
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!CrosshairTexture) return;

	// Canvas Dimension
	float CanvasWidth = Canvas->ClipX;
	float CanvasHeight = Canvas->ClipY;
	FVector2D Center(CanvasWidth * 0.5f, CanvasHeight * 0.5f);

	// Crosshair Dimensions
	float CrosshairWidth = CrosshairTexture->GetSurfaceWidth();
	float CrosshairHeight = CrosshairTexture->GetSurfaceHeight();

	float AlignmentOffsetX = 2.5f;
	float AlignmentOffsetY = 3.0f;
	FVector2D CrosshairPosOffset(CrosshairWidth * AlignmentOffsetX, CrosshairHeight * AlignmentOffsetY);

	// Draw Settings
	FVector2D CrosshairDrawPosition = Center - CrosshairPosOffset;

	float CrosshairScale = 5.0f;
	FVector2D CrosshairSize(CrosshairWidth * CrosshairScale, CrosshairHeight * CrosshairScale);

	// Draw the crosshair
	FCanvasTileItem CrosshairItem(CrosshairDrawPosition, CrosshairTexture->GetResource(), CrosshairSize, FLinearColor::White);
	CrosshairItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(CrosshairItem);

}

void AGameHUD::ShowSettingsMenu()
{
	SettingsWidget = SNew(SSSettingsWidget).GameHUD(this).MyInt(1777);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(SettingsWidgetContainer, SWeakWidget).PossiblyNullContent(SettingsWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void AGameHUD::HideSettingsMenu()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(SettingsWidgetContainer.ToSharedRef());

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AGameHUD::SpawnGameMenu(TSubclassOf<UGameMenuWidget> NewGameMenuWidget)
{
	if (GameMenuWidgetContainer) {
		GameMenuWidgetContainer->RemoveFromParent();
		GameMenuWidgetContainer = nullptr;
	}

	GameMenuWidgetContainer = CreateWidget<UGameMenuWidget>(GetWorld(), NewGameMenuWidget);
	GameMenuWidgetContainer->AddToViewport();

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}