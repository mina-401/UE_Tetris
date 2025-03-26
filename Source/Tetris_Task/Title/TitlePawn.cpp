// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitlePawn.h"
#include "Title/Actor/TitleScreen.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Play/Actor/LevelActor.h"
#include "Global/TEnum.h"


// Sets default values
ATitlePawn::ATitlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void ATitlePawn::SetMapOutliner()
{
    FVector Location = { 0.0, 0.0, 0.0 };

    for (int j = 0; j < MapHeight; ++j)
    {
      
            for (int i = 0; i < MapWidth; i++)
            {
                Location = { 0.0, i * -80.0f, j * 80.0f };
                LevelPlane = GetWorld()->SpawnActor<ALevelActor>(LevelFactory);
                LevelPlane->SetActorLocation(Location);
            }
    
            for (int i = 0; i < MapWidth; i = i + MapWidth - 1)
            {
                Location = { 0.0, i * -80.0f, j * 80.0f };
                LevelPlane = GetWorld()->SpawnActor<ALevelActor>(LevelFactory);
                LevelPlane->SetActorLocation(Location);
            }
    

    }

    X = MapHeight;
    Y = MapWidth;
}
void ATitlePawn::SpawnTetrisBlock()
{
    FVector SpawnLocation(0.0f, 0.0f, 0.0f);
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f); // 기본 회전값


    BlockType = GetRandomBlockType();
    switch (BlockType)
    {
    case EBlockType::BT_I:

        Block = GetWorld()->SpawnActor<ABlock>(IFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_L:
        Block = GetWorld()->SpawnActor<ABlock>(LFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_J:
        Block = GetWorld()->SpawnActor<ABlock>(JFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_Z:
        Block = GetWorld()->SpawnActor<ABlock>(ZFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_S:
        Block = GetWorld()->SpawnActor<ABlock>(SFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_T:
        Block = GetWorld()->SpawnActor<ABlock>(TFactory, SpawnLocation, SpawnRotation);
        break;
    case EBlockType::BT_O:
        Block = GetWorld()->SpawnActor<ABlock>(OFactory, SpawnLocation, SpawnRotation);
        break;
    default:
        break;
    }


    Block->X = 0;
    Block->Y = Y;

}
// Called when the game starts or when spawned
void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();

    SetMapOutliner();
    SpawnTetrisBlock();


}

// Called every frame
void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void ATitlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


    bool IsbMoving = false;

    EnhancedInputComponent->BindActionValueLambda(MoveAction, ETriggerEvent::Started,
        [this,&IsbMoving](const FInputActionValue& _Value)
        {
            IsbMoving = true;

        });
    EnhancedInputComponent->BindActionValueLambda(MoveAction, ETriggerEvent::Triggered,
        [this,&IsbMoving](const FInputActionValue& _Value)
        {
            if (IsbMoving == true)
            {
                FVector2D MoveAxisVector = _Value.Get<FVector2D>();

                if (Controller != nullptr)
                {
                    float Right = MoveAxisVector.Y;
                    float Up = MoveAxisVector.X;


                    int x = Block->X;
                    int y = Block->Y;

                    if (Right >= 1)
                    {
                        int NextX = x + 1;
                        if (NextX > X - 1)
                        {
                            return;
                        }
                        Block->X = NextX;

                    }
                    else if (Right <= -1)
                    {
                        int NextX = x - 1;

                        if (NextX < 0)
                        {
                            return;
                        }
                        Block->X = NextX;
                    }

                    else if (Up <= -1)
                    {
                        int NextY = y - 1;
                        if (NextY < 0)
                        {
                            return;
                        }
                        Block->Y = NextY;
                    }

                    else if (Up >= 1)
                    {
                        int NextY = y + 1;
                        if (NextY > Y-1)
                        {
                            return;
                        }
                        Block->Y = NextY;
                    }

                    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f Right"), Right));
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f %f Move"), MoveAxisVector.X, MoveAxisVector.Y));
                }

                IsbMoving = false;
            }
            


            
            
        });

    EnhancedInputComponent->BindActionValueLambda(RoatateAction, ETriggerEvent::Started,
        [this, &IsbMoving](const FInputActionValue& _Value)
        {
            IsbMoving = true;

        });
    EnhancedInputComponent->BindActionValueLambda(RoatateAction, ETriggerEvent::Triggered,
        [this, &IsbMoving](const FInputActionValue& _Value)
        {
            if (IsbMoving == true)
            {
                
                bool IsRotate = _Value.Get<bool>();

                if (true == IsRotate)
                {
                    Block->AddActorLocalRotation(FRotator(0, 0, 90.0f));
                }
                
                IsbMoving = false;
            }

        });

}

