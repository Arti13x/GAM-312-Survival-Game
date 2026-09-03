// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayerChar.h"

// Sets default values
ACppPlayerChar::ACppPlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACppPlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppPlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACppPlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

