// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CppInteractInterface.h"
#include "Resource_Master.generated.h"

UCLASS()
class GAM312SURVIVALGAME_API AResource_Master : public AActor, public ICppInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_Master();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	UPROPERTY(EditAnywhere)
	FString resourceName = "resource";

	UPROPERTY(EditAnywhere)
	int resourceAmount = 5;

	UPROPERTY(EditAnywhere)
	int totalResourceAmount = 100;

	UPROPERTY()
	FText tempText;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* ResourceNameText;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

};
