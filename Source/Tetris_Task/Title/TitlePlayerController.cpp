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


	// ������ ���ε� Ű�Է� �� ����ϴ�.
	InputSystem->ClearAllMappings();
	// ��� �Է¼����� ���� ���� ó���Ǵ� �Է����� ���ڴ�.
	InputSystem->AddMappingContext(_MappingContext, 0);
}
