// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CppInteractInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class GAM312SURVIVALGAME_API UCppInteractInterface : public UInterface 
{
	GENERATED_BODY()
};

class GAM312SURVIVALGAME_API ICppInteractInterface
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
	
};
