// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Play/Actor/Block.h"
#include "TitleScreen.generated.h"


UCLASS()
class TETRIS_TASK_API ATitleScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATitleScreen();

	//~ATitleScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blocks")
	TArray<class ABlock*> Blocks;
	TArray<TArray<ETBlock>> TBlocks;

	UPROPERTY(EditAnywhere, Category = "Tetris")
	TSubclassOf<class ABlock> Block;

	int Y = 0;
	int X = 0;

	UFUNCTION(BlueprintCallable)
	void CreateBlocks(int _X, int _Y);
	UFUNCTION(BlueprintCallable)
	void SetBlock(int _X, int _Y,ETBlock _Type);
	UFUNCTION(BlueprintCallable)
	void Render();
	void Clear();
	
	TArray<class ABlock*> GetAllBlocks()
	{
		return Blocks;
	}

	TArray<TArray<ETBlock>> GetAllTBlocks()
	{
		return TBlocks;
	}


	//UFUNCTION()
	//void SetBlockX(int _X)
	//{
	//	block->X = _X;
	//}
	//void SetBlockY(int _Y)
	//{
	//	block->Y = _Y;
	//}
};
