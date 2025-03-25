// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitlePawn.h"
#include "Title/Actor/TitleScreen.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATitlePawn::ATitlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnLocation(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f); // 기본 회전값
	
	TS = GetWorld()->SpawnActor<ATitleScreen>(TSFactory, SpawnLocation, SpawnRotation);
	TS->CreateBlocks(5, 5);
	//TS->Render();
}

// Called every frame
void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TS->Clear();
    TS->Render();
}

// Called to bind functionality to input
void ATitlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInputComponent->BindActionValueLambda(MoveAction, ETriggerEvent::Triggered,
        [this](const FInputActionValue& _Value)
        {
            FVector2D MoveAxisVector = _Value.Get<FVector2D>();

           if (Controller != nullptr)
            {
                float Right = MoveAxisVector.Y;
                float Up = MoveAxisVector.X;

                if(Right>0)
                { }

                // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f Right"), Right));
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f %f Move"), MoveAxisVector.X, MoveAxisVector.Y));
            }
            
        });

 

}

