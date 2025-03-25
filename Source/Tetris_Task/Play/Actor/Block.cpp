// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Actor/Block.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global/TEnum.h"
// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = SceneComp;

	BlockComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestrisBlock"));
	BlockComp->SetupAttachment(RootComponent);

	BlockComp->SetRelativeRotation(FRotator(0, -89, 90));
	BlockComp->SetRelativeScale3D(FVector(1, 1, 1));

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FVector( 0.0f, X * -Scale,Y * Scale));
}

void ABlock::Move()
{
	// 입력키 누르면 내려옴 
}

