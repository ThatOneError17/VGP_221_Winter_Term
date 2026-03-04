// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/EnemyAICharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "GameFramework/Character.h"
class UPauseMenuWidget;
#include "FPSCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);

//class UCapsuleComponent;	Useless with the #Include above

UCLASS()
class VGP201_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;	//UCameraComponent pointer named FPSCameraComponent

	UPROPERTY(VisibleAnywhere)	
	USkeletalMeshComponent* FPSMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFPSProjectile> ProjectileClass;	//Let's you have subclass and it's children as well

	UPROPERTY(EditAnywhere)
	FOnPlayerDied OnPlayerDied;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	class UPauseMenuWidget* PauseMenu;
	bool GameIsPaused = false;	

	UFUNCTION()
	void OnMoveForward(float Value);

	UFUNCTION()
	void OnMoveRight(float Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void OnHurtPlayer(float DamageAmount);

	UFUNCTION()
	void OnHealPlayer(float HealAmount);

	UFUNCTION()
	void PauseGame();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	float Health = 100.0f;
	float MaxHealth = 100.0f;	//Should make this a health actor component later

};
