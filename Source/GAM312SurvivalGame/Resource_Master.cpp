// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Master.h"

// Sets default values
AResource_Master::AResource_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ResourceNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	ResourceNameText->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AResource_Master::BeginPlay()
{
	Super::BeginPlay();
	
	tempText = tempText.FromString(resourceName);

	ResourceNameText->SetText(tempText);

}

// Called every frame
void AResource_Master::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResource_Master::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted with %s"), *resourceName);

	if (totalResourceAmount > 0)
	{
		totalResourceAmount = totalResourceAmount - 5;

		if (resourceName == "Wood")
		{
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Wood Collected"));
		}
		else if (resourceName == "Stone")
		{
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Stone Collected"));
		}
		else if (resourceName == "Berry")
		{
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Berry Collected"));
		}
	}
	else
	{
		Destroy();
	}
}

