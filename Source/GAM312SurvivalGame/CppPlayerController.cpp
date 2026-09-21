// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "CppInteractInterface.h"
#include "kismet/GameplayStatics.h"
#include "CppPlayerChar.h"
#include "GameFramework/Character.h"

ACppPlayerController::ACppPlayerController()
{
	bShowMouseCursor = false;
}

void ACppPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}

	}
}

void ACppPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{ 
		//bind actions so they work with the input system
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACppPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACppPlayerController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACppPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACppPlayerController::StopJumping);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACppPlayerController::Interact);
		EnhancedInputComponent->BindAction(RotateBuildingAction, ETriggerEvent::Started, this, &ACppPlayerController::RotateBuilding);
	}
}

//allow player to move forward/back and left/right based on input from the player
void ACppPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	//get the control rotation of the player and use it to determine the forward and right direction for movement
	const FRotator ControlRot = ControlledPawn->GetControlRotation();
	const FRotator YawRotation(0.f, ControlRot.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//add movement input to the controlled pawn based on the movement vector and the forward and right direction
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
}

//allow player to look around based on input from the player
void ACppPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

//start the jump action when input by the player
void ACppPlayerController::Jump(const FInputActionValue& Value)
{
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->Jump();
	}
}

//stop the jump action
void ACppPlayerController::StopJumping(const FInputActionValue& Value)
{
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->StopJumping();
	}
}

void ACppPlayerController::Interact()
{
	FHitResult HitResult;
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + (PlayerCameraManager->GetActorForwardVector() * 500.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	ACppPlayerChar* PlayerChar = Cast<ACppPlayerChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerChar->isBuilding == false) 
	{
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (AActor* HitActor = HitResult.GetActor())
			{
				UGameplayStatics::SpawnDecalAtLocation(GetWorld(), PlayerChar->hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

				if (HitActor->GetClass()->ImplementsInterface(UCppInteractInterface::StaticClass()))
				{
					if (ICppInteractInterface* Interface = Cast<ICppInteractInterface>(HitActor))
					{
						Interface->Interact();
					}
				}
			}
		}
	}
	else
	{
		PlayerChar->isBuilding = false;
	}
	
}

void ACppPlayerController::RotateBuilding()
{
	ACppPlayerChar* PlayerChar = Cast<ACppPlayerChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerChar->isBuilding)
	{
		PlayerChar->RotateBuilding();
	}
}
