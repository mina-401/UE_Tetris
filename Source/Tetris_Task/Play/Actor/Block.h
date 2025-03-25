// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/TEnum.h"
#include "Block.generated.h"


UCLASS()
class TETRIS_TASK_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComp = nullptr;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BlockComp = nullptr;


	EBlockType BlockType = EBlockType::BT_O;

	ETBlock TBlockType = ETBlock::VOID;
	void Move();

	int X = 0;
	int Y = 0;
	float Scale = 80.0f;

};
