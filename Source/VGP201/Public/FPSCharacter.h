// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "FPSProjectile.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

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

};
