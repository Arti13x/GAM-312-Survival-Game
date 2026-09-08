// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayerChar.h"

// Sets default values
ACppPlayerChar::ACppPlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*
	* did't work for some reason and wouldn't add a camera component to the blueprint character, so I added it in the blueprint instead
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->SetupAttachment(GetMesh(), "head");
	CameraComponent->bUsePawnControlRotation = true;
	*/

	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));

}

// Called when the game starts or when spawned
void ACppPlayerChar::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &ACppPlayerChar::DecreaseStats, 3.0f, true);
	
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

/*
* does not work with Input action system, so I moved it to the player controller and added an interface to the resource master
void ACppPlayerChar::FindObject()
{
	FHitResult HitResult;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (GetActorForwardVector() * 500.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		AResource_Master* HitResource = Cast<AResource_Master>(HitResult.GetActor());

		if (HitResource)
		{
			FString hitName = HitResource->resourceName;
			int resourceValue = HitResource->resourceAmount;

			HitResource->totalResourceAmount = HitResource->totalResourceAmount - resourceValue;

			if (HitResource) 
			{
				GiveResource(resourceValue, hitName);

				check(GEngine != nullptr);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Resource Collected"));
			}
			else
			{
				HitResource->Destroy();

				check(GEngine != nullptr);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Resource Depleted"));
			}
		}
	}

}
*/

void ACppPlayerChar::SetHealth(float value)
{
	if (Health + value < 100)
	{
		Health = Health + value;
	}
}

void ACppPlayerChar::SetStamina(float value)
{
	if (Stamina + value < 100)
	{
		Stamina = Stamina + value;
	}
}

void ACppPlayerChar::SetHunger(float value)
{
	if (Hunger + value < 100)
	{
		Hunger = Hunger + value;
	}
}

void ACppPlayerChar::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}

	SetStamina(10.0f);

	if (Hunger <= 0)
	{
		SetHealth(-5.0f);
	}
}

/*
* does not work with Input action system, so I moved it to the player controller and added an interface to the resource master
void ACppPlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}
	else if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}
	else if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}
*/

