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
TArray<TArray<int>> ATitlePawn::GetBlockShape(EBlockType Shape)
{
    switch (Shape)
    {
    case EBlockType::BT_I:
        return { {1, 1, 1, 1} };
        break;
    case EBlockType::BT_L:
        return { {0, 0, 1}, {1, 1, 1} };
        break;
    case EBlockType::BT_J:
        return { {1, 0, 0}, {1, 1, 1} };
        break;
    case EBlockType::BT_Z:
        return { {1, 1, 0}, {0, 1, 1} };
        break;
    case EBlockType::BT_S:
        return { {0, 1, 1}, {1, 1, 0} };
        break;
    case EBlockType::BT_T:
        return { {0, 1, 0}, {1, 1, 1} };
        break;
    case EBlockType::BT_O:
        return { {1, 1}, {1, 1} };
        break;
    default:
        break;
    }
    return { {1,1,1,1} };
}
bool ATitlePawn::IsValidPosition(const TArray<TArray<int32>>& Shape, int OffsetX, int OffsetY, const TArray<TArray<int>>& Board)
{
    for (int y = 0; y < Shape.Num(); ++y)
    {
        for (int x = 0; x < Shape[y].Num(); ++x)
        {
            if (Shape[y][x] != 0) // 블록의 부분인 경우
            {
                int NewX = OffsetX + x;
                int NewY = OffsetY + y;

                // 경계 검사
                if (NewX < 0 || NewX >= Board[0].Num() || NewY >= Board.Num())
                {
                    return false;
                }

                // 블록 충돌 검사
                if (NewY >= 0 && Board[NewY][NewX] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
void ATitlePawn::MoveBlock(FVector2D MoveAxisVector)
{

        int x = Block->X;
        int y = Block->Y;

        TArray<TArray<int>> CurrentShape = GetBlockShape(BlockType);

        if (Controller != nullptr)
        {
            if (MoveAxisVector.Y >= 1) // 오른쪽 이동
            {
                if (IsValidPosition(CurrentShape, x + 1, y, TBlocks))
                {
                    Block->X += 1;
                }
            }
            else if (MoveAxisVector.Y <= -1) // 왼쪽 이동
            {
                if (IsValidPosition(CurrentShape, x - 1, y, TBlocks))
                {
                    Block->X -= 1;
                }
            }

            if (MoveAxisVector.X >= 1) // 아래로 이동
            {
                if (IsValidPosition(CurrentShape, x, y + 1, TBlocks))
                {
                    Block->Y += 1;
                }
            }
            else if (MoveAxisVector.X <= -1) // 위로 이동
            {
                if (IsValidPosition(CurrentShape, x, y - 1, TBlocks))
                {
                    Block->Y -= 1;
                }
            }

            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f %f Move"), MoveAxisVector.X, MoveAxisVector.Y));
        }

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
    Block->Y = Y-1;

}
// Called when the game starts or when spawned
void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();

    SetMapOutliner();
    SpawnTetrisBlock();
    CreateBlocks(X, Y);

}

// Called every frame
void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    int x = Block->X;
    int y = Block->Y;


    

    if (y == 0)
    {
        TBlocks[y][x] =1;
    }
    else if (TBlocks[y - 1][x]== 1)
    {
        TBlocks[y][x] = 1;
    }
    if (TBlocks[y][x] == 1)
    {
        SpawnTetrisBlock();
    }
}

void ATitlePawn::CreateBlocks(int _X, int _Y)
{
    TBlocks.SetNum(_Y);
    for (int y = 0; y < _Y; y++)
    {

        TBlocks[y].SetNum(_X);

        for (int x = 0; x < _X; x++)
        {
            TBlocks[y][x] = 0;
        }
    }
}
void ATitlePawn::Clear()
{
    TBlocks.Empty();
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


               //MoveBlock(MoveAxisVector);
               if (Controller != nullptr)
               {

                   int x = Block->X;
                   int y = Block->Y;

                   if (MoveAxisVector.Y >= 1)
                   {
                       int NextX = x + 1;
                       if (NextX > X - 1)
                       {
                           return;
                       }
                       Block->X = NextX;

                   }
                   else if (MoveAxisVector.Y <= -1)
                   {
                       int NextX = x - 1;

                       if (NextX < 0)
                       {
                           return;
                       }
                       Block->X = NextX;
                   }

                   else if (MoveAxisVector.X <= -1)
                   {
                       int NextY = y - 1;
                       if (NextY < 0)
                       {
                           return;
                       }
                       Block->Y = NextY;
                   }

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

