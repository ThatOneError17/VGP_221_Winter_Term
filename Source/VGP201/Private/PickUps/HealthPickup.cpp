// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/HealthPickup.h"
#include "Components/SphereComponent.h"
#include "FPSCharacter.h"

// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	CollisionSphere->SetSphereRadius(45.0f);	//May need to adjust size
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
	
}

void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
    if (Player)
    {
        Player->OnHealPlayer(HealAmount);
        Destroy();
    }
}

void AHealthPickup::Tick(float DeltaTime)
{
}

