// Fill out your copyright notice in the Description page of Project Settings.

#include "shards.h"
#include "Stick.h"
#include "EngineUtils.h" 

// Sets default values
AStick::AStick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StickModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Models/Environment/Dais"));
	StickModel->SetStaticMesh(MeshObj.Object);
	StickModel->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	StickModel->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	StickModel->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	StickModel->SetCastShadow(false);
	StickModel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StickModel;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->AttachTo(RootComponent);
	PointLight->SetRelativeLocation(FVector(0.0f, 0.0f, 6.8f));
	PointLight->Intensity = 1385.76f;
	PointLight->AttenuationRadius = 1006.83f;
	PointLight->LightColor = FColor(230, 255, 235);

	Here = CreateDefaultSubobject<USceneComponent>(TEXT("Here"));
	//Here->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	PostTeleportVelocity = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AStick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStick::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	gohere = Here->GetComponentLocation();
	
}
