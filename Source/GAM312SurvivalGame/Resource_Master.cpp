// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Master.h"
#include "CppPlayerChar.h"
#include "Kismet/GameplayStatics.h"

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
	ACppPlayerChar* PlayerChar = Cast<ACppPlayerChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerChar->Stamina > 5.0f) 
	{
		if (totalResourceAmount > 0)
		{
			totalResourceAmount = totalResourceAmount - resourceAmount;

			if (resourceName == "Wood")
			{
				PlayerChar->ResourcesArray[0] += resourceAmount;
			}
			else if (resourceName == "Stone")
			{
				PlayerChar->ResourcesArray[1] += resourceAmount;
			}
			else if (resourceName == "Berry")
			{
				PlayerChar->ResourcesArray[2] += resourceAmount;
			}

			PlayerChar->SetStamina(-5.0f);
		}
		else
		{
			Destroy();
		}
	}
	else
	{
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough stamina to collect resource"));
	}
}

