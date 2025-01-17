// Fill out your copyright notice in the Description page of Project Settings.

#include "shards.h"
#include "RotatingPlatform.h"

ARotatingPlatform::ARotatingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	AngularPeriod = 4;

	Center = CreateDefaultSubobject<USceneComponent>(TEXT("Center"));
	//Center->AttachTo(RootComponent);
	Center->SetupAttachment(RootComponent);//4.12
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float angularfrequency = 1.0f / AngularPeriod;
	if (!Deactivated) {
		Model->AddLocalRotation(FQuat(FVector::UpVector, (SpinDirection == RotatingPlatformDirection::CW ? 1 : -1) * (2.0f * 3.14159f) * angularfrequency * DeltaTime), false, (FHitResult*)nullptr, ETeleportType::None);
	}
}

