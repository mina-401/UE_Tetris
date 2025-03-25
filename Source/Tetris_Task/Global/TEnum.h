// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TEnum.generated.h"

UENUM(BlueprintType)
enum class ETBlock :uint8
{
	WALL,
	VOID,
	BLOCK,

};
enum class EBlockType
{
	BT_I,
	BT_L,
	BT_J,
	BT_Z,
	BT_S,
	BT_T,
	BT_O,
};
UCLASS()
class TETRIS_TASK_API UTEnum : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
