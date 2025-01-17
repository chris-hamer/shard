// Fill out your copyright notice in the Description page of Project Settings.

#include "shards.h"
#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CycleTime = 6.0f;
	MovementType = MovingPlatformType::LINEAR;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Generic/Environment/Misc/FloatingPlatform/platform"));
	Model->SetStaticMesh(MeshObj.Object);
	Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	RootComponent = Model;

	StartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Start Position"));
	//StartPosition->AttachTo(RootComponent);
	StartPosition->SetupAttachment(RootComponent);//4.12
	StartPosition->SetRelativeLocation(FVector::ZeroVector);

	EndPosition = CreateDefaultSubobject<USceneComponent>(TEXT("End Position"));
	//EndPosition->AttachTo(RootComponent);
	EndPosition->SetupAttachment(RootComponent);//4.12
	EndPosition->SetRelativeLocation(FVector::ZeroVector);

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	Model->SetWorldLocation(StartPosition->GetComponentLocation());
}

// Crappy makeshift numerical derivative function because I coluldn't find one in FMath.
float AMovingPlatform::nderiv(float x, float ctime, float (*f)(float,float), float c)
{
	return (((*f)(x + c, ctime) - (*f)(x, ctime)) / c);
}

// Defines wave motion where the platform's position changes sinusoidally with time.
float wave(float x, float ctime) {
	return (-FMath::Cos(2 * 3.14159 * x / ctime) + 1.0f) / (2.0f);
}

float wavevelocity(float x, float ctime) {
	return (3.14159 * FMath::Sin(2 * 3.14159 * x / ctime) / ctime);
}

// Defines linear motion where the platform's position changes linearly with time.
float linear(float x, float ctime) {
	return (2 * FMath::Abs(FMath::Fmod(x / ctime + 0.5f, 1.0f) - 0.5f));
}

// Defines blinking behavior where the platform switches back and forth between its start and end positions.
float blink(float x, float ctime) {
	if (x/ctime - FMath::FloorToInt(x/ctime) < 0.5f) {
		return 0.0f;
	}
	return 1.0f;
}

float onewaylinear(float x, float ctime) {
	if (x < ctime) {
		return linear(x, ctime);
	}
	return 1.0f;
}

// Called every frame
void AMovingPlatform::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	if (!OverrideMovement) {
		if (!Deactivated) {
			// Switch the function used depending on the editor setting.
			float(*f)(float, float) = &linear;
			float(*v)(float, float) = &linear;
			switch (MovementType) {
			case MovingPlatformType::LINEAR:
				f = &linear;
				break;
			case MovingPlatformType::WAVE:
				f = &wave;
				break;
			case MovingPlatformType::BLINK:
				f = &blink;
				break;
			case MovingPlatformType::ONEWAY:
				f = &blink;
				break;
			}

			// Increment the timer and find the platform's new position.
			timer += DeltaTime;
			FVector NewPosition = FMath::Lerp(StartPosition->GetComponentLocation(), EndPosition->GetComponentLocation(), f(timer, CycleTime));
			FVector OldPosition = Model->GetComponentLocation();

			if (HasVelocityFunction) {
				// Get the platform's velocity from a user-provided function.
				Velocity = FMath::Lerp(FVector::ZeroVector, EndPosition->GetComponentLocation() - StartPosition->GetComponentLocation(), v(timer, CycleTime));
			} else {
				// Estimate the platform's veloicty using a numerical derivative of its movement function.
				Velocity = FMath::Lerp(FVector::ZeroVector, EndPosition->GetComponentLocation() - StartPosition->GetComponentLocation(), nderiv(timer, CycleTime, f));
			}

			FVector start = StartPosition->GetComponentLocation();
			FVector end = EndPosition->GetComponentLocation();

			// Move the platform to its new location.
			Model->SetWorldLocation(NewPosition,false,(FHitResult*)nullptr);
			StartPosition->SetWorldLocation(start);
			EndPosition->SetWorldLocation(end);
		}
	} else {
		Velocity = (Model->GetComponentLocation() - PreviousLocation) / DeltaTime;
		PreviousLocation = Model->GetComponentLocation();
	}
}

void AMovingPlatform::Deactivate() {
	Deactivated = true;
}

void AMovingPlatform::Activate() {
	Deactivated = false;
}