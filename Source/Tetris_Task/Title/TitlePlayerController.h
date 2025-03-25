// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_TASK_API ATitlePlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext = nullptr;
protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
public:
	UFUNCTION(BlueprintCallable)
	void AddMappingContext(UInputMappingContext* _MappingContext);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetupInputComponentEvent();
};
