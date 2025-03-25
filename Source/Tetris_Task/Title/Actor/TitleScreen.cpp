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

        SetBlock(0, 0, ETBlock::BLOCK);
    }
    Blocks.SetNum(_Y);
    for (int y = 0; y < _Y; y++)
    {

        Blocks[y].SetNum(_X);

        for (int x = 0; x < _X; x++)
        {
            Blocks[y][x] = nullptr;
        }

       
    }
    
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
            // (0, 0, 0) ��ġ�� ����
           
            FVector SpawnLocation(0.0f, 0.0f, 0.0f);
            FRotator SpawnRotation(0.0f, 0.0f, 0.0f); // �⺻ ȸ����
            ABlock* block = GetWorld()->SpawnActor<ABlock>(Block, SpawnLocation, SpawnRotation);

            if (block == nullptr) return;

            block->Y = y;
            block->X = x;

            switch (TBlocks[y][x])
            {
            case ETBlock::WALL:
                break;
            case ETBlock::VOID:
                break;
            case ETBlock::BLOCK:
                
                break;
            default:
                break;
            }


           
            
        }
    }
}

void ATitleScreen::Clear()
{
    //TBlocks.Empty();
   
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

    for (int y = 0; y < Y; y++)
    {


        for (int x = 0; x < X; x++)
        {
            
        }

    }

}



