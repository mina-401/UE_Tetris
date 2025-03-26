// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/Actor/TitleScreen.h"
#include "Play/Actor/Block.h"
#include "Global/TEnum.h"
// Sets default values
ATitleScreen::ATitleScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATitleScreen::CreateBlocks(int _X, int _Y)
{
    X = _X;
    Y = _Y;
    TBlocks.SetNum(_Y);
    for (int y = 0; y < _Y; y++)
    {

        TBlocks[y].SetNum(_X);

        for (int x = 0; x < _X; x++)
        {
            TBlocks[y][x] = ETBlock::VOID;

           
        }

    }
   
  //  Render();
}
void ATitleScreen::SetBlock(int _X, int _Y, ETBlock _Type)
{

    TBlocks[_Y][_X] = _Type;
}
void ATitleScreen::Render()
{
    for (int y = 0; y < Y; y++)
    {

        for (int x = 0; x < X; x++)
        {
            // (0, 0, 0) 위치에 스폰
           
            FVector SpawnLocation(0.0f, 0.0f, 0.0f);
            FRotator SpawnRotation(0.0f, 0.0f, 0.0f); // 기본 회전값
           

            ABlock* block = nullptr;

            switch (TBlocks[y][x])
            {
            case ETBlock::WALL:
                break;
            case ETBlock::VOID:
                break;
            case ETBlock::BLOCK:
                block=GetWorld()->SpawnActor<ABlock>(Block, SpawnLocation, SpawnRotation);
                block->Y = y;
                block->X = x;

                Blocks.Add(block);

                block = nullptr;
                break;
            default:
                break;
            }
   
        }
    }
}

void ATitleScreen::Clear()
{
    for (ABlock* b : Blocks)
    {
        b->Destroy();
    }


    Blocks.Empty();

   
   //for (int y = 0; y < Y; y++)
   //{


   //    for (int x = 0; x < X; x++)
   //    {
   //        TBlocks[y][x] = ETBlock::VOID;


   //    }

   //}
    //SetBlock(0, 0, ETBlock::BLOCK);
    //SetBlock(1, 0, ETBlock::BLOCK);
   
}

// Called when the game starts or when spawned
void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATitleScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Render();

}



