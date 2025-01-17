// Fill out your copyright notice in the Description page of Project Settings.

#include "shards.h"
#include "CameraOverrideRegion.h"
#include "TwoDimensionalMovementRegion.h"


// Sets default values
ATwoDimensionalMovementRegion::ATwoDimensionalMovementRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockedAxis = MovementRegionLockedAxis::XAXIS;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Region = CreateDefaultSubobject<UBoxComponent>(TEXT("Region"));
	//Region->AttachTo(Root);
	Region->SetupAttachment(Root);//4.12
	Region->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Region->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	path->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ATwoDimensionalMovementRegion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATwoDimensionalMovementRegion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

