// Fill out your copyright notice in the Description page of Project Settings.

#include "shards.h"
#include "BreakableBox.h"


// Sets default values
ABreakableBox::ABreakableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABreakableBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}
