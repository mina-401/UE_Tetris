// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Global/TEnum.h>

#include "TitlePawn.generated.h"

UCLASS()
class TETRIS_TASK_API ATitlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATitlePawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateBlocks(int _X, int _Y);

	void Render();
	void Clear();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	void CheckBlock();

	EBlockType GetRandomBlockType()
	{
		// EBlockType�� �� ����
		int BlockTypeCount = 7; // BT_I���� BT_O���� �� 7��

		// ���� �õ� �ʱ�ȭ
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// 0���� BlockTypeCount - 1 ������ ���� �ε��� ����
		int randomIndex = std::rand() % BlockTypeCount;

		// ���� �ε����� EBlockType���� ��ȯ�Ͽ� ��ȯ
		return static_cast<EBlockType>(randomIndex);
	}

	TArray<TArray<int>> GetBlockShape(EBlockType Shape);
	bool IsValidPosition(const TArray<TArray<int32>>& Shape, int OffsetX, int OffsetY, const TArray<TArray<int>>& Board);
	void MoveBlock(FVector2D MoveAxisVector);
	void SetMapOutliner();

	void SpawnTetrisBlock();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int MapHeight = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int MapWidth = 0;

	UPROPERTY()
	class ALevelActor* LevelPlane = nullptr;

	TArray<TArray<int>> TBlocks;


	// Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALevelActor> LevelFactory;
	//void Setup()



	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATitleScreen> TSFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> BlockFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> JFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> IFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> LFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> OFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> SFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> TFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlock> ZFactory;

	UPROPERTY()
	class ATitleScreen* TS = nullptr;

	UPROPERTY()
	class ABlock* Block = nullptr;

	EBlockType BlockType = EBlockType::BT_I;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* RoatateAction = nullptr;

	int X = MapHeight;
	int Y = MapWidth;
	
};
