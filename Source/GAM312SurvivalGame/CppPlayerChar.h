// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_Master.h"
#include "CppPlayerChar.generated.h"


UCLASS()
class GAM312SURVIVALGAME_API ACppPlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACppPlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	//add a camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;


	//add health, stamina, and hunger stats for the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f;

	//add resources for the player
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Wood = 0;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Stone = 0;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Berry = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		TArray<int> ResourcesArray;

	UPROPERTY(EditAnywhere, Category = "Resources")
		TArray<FString> ResourcesNameArray;

	/* does not work with Input action system, so I moved it to the player controller and added an interface to the resource master
	UFUNCTION()
	void FindObject();
	*/

	UFUNCTION(BlueprintCallable)
		void SetHealth(float value);

	UFUNCTION(BlueprintCallable)
		void SetStamina(float value);

	UFUNCTION(BlueprintCallable)
		void SetHunger(float value);

	UFUNCTION()
		void DecreaseStats();

	/* does not work with Input action system, so I moved it to the player controller and added an interface to the resource master
	UFUNCTION()
		void GiveResource(float amount, FString resourceType);
	*/
};
