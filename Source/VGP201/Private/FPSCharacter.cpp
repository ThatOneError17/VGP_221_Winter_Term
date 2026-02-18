// Fill out your copyright notice in the Description page of Project Settings.



#include "FPSCharacter.h"
#include "PauseMenu/PauseMenuWidget.h"	//I don't know why, but I had to include this here to avoid an error

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("FPSCharacter Constructor Called"));

	if (!FPSCameraComponent) 
	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera")); // Adds Component in the BP
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	if (!FPSMeshComponent) 
	{
		FPSMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMeshComponent->SetupAttachment(FPSCameraComponent);
		FPSMeshComponent->bCastDynamicShadow = false;
		FPSMeshComponent->CastShadow = false;
	}


	GetMesh()->SetOwnerNoSee(true);	

	//This is a crash test
	//int* CrashInt = nullptr;

	//UE_LOG(LogTemp, Warning, TEXT("%i"), *CrashInt);	//This was a crash test and it DID work, trust me
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AGameHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();
	HUD->GameMenuWidgetContainer->UpdateHealthBar(Health/MaxHealth);
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::OnMoveRight);

	PlayerInputComponent->BindAxis("LookHorizontal", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AFPSCharacter::PauseGame);
}
	

void AFPSCharacter::OnMoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::OnMoveRight(float Value)
{
	// Finish Move Right
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	// Have the character jump without usign Character::Jump()
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (!ProjectileClass) return;

	// Init relevant infomration for where the projectile will be
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(20.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	//MuzzleRotation.Pitch += 10.0f;

	// Start of spawning the projectile
	UWorld* World = GetWorld();
	if (!World)  return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Unity Instantiate
	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;

	// Launch spawned projectile in the camera rotation
	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);

	//OnHurtPlayer(10.0f);	//Debug for losing health when firing
}

void AFPSCharacter::OnHurtPlayer(float DamageAmount)
{
	if (DamageAmount <= 0.0f) 
		return;

	if (Health <= 0.0f)
		return;

	
	Health -= DamageAmount;

	AGameHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();
	HUD->GameMenuWidgetContainer->UpdateHealthBar(Health / MaxHealth);

	if (Health <= 0.0f)
	{
		OnPlayerDied.Broadcast();
	}
}

void AFPSCharacter::PauseGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	if (!GameIsPaused)
	{
		if (!PauseMenuClass) return; //safety check

		//Destroy previous instance if exists
		if (PauseMenu)
		{
			PauseMenu->RemoveFromParent();
			PauseMenu = nullptr;
		}

		//Create a new instance
		PauseMenu = CreateWidget<UPauseMenuWidget>(PC, PauseMenuClass);
		if (PauseMenu)
		{
			//Bind Resume button delegate
			PauseMenu->OnResumeClicked.BindUObject(this, &AFPSCharacter::PauseGame);

			//Add to viewport
			PauseMenu->AddToViewport();

			//Pause game
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			//Show mouse
			PC->bShowMouseCursor = true;

			//Set UI input mode
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(PauseMenu->GetCachedWidget());
			PC->SetInputMode(InputMode);

			GameIsPaused = true;
		}
	}
	else
	{
		//Remove and destroy pause menu
		if (PauseMenu)
		{
			PauseMenu->RemoveFromParent();
			PauseMenu = nullptr;	//Should hopefully fix the resume button issue
		}

		//Unpause game
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		// Hide mouse
		PC->bShowMouseCursor = false;

		//Game input mode
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

		GameIsPaused = false;
	}
}

float AFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	OnHurtPlayer(DamageAmount);
	return DamageAmount;
}

