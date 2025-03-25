// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitlePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATitlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetupInputComponentEvent();
}

void ATitlePlayerController::AddMappingContext(UInputMappingContext* _MappingContext)
{
	if (nullptr == GetLocalPlayer())
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());


	// 기존에 매핑된 키입력 다 지웁니다.
	InputSystem->ClearAllMappings();
	// 모든 입력순서중 가장 먼저 처리되는 입력으로 보겠다.
	InputSystem->AddMappingContext(_MappingContext, 0);
}
