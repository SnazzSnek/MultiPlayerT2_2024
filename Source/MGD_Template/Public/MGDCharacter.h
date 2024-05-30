	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGDCharacter.generated.h"

UCLASS()
class MGD_TEMPLATE_API AMGDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMGDCharacter();

    // move the character based on an axis
	UFUNCTION(BlueprintCallable, Category="Movement")
	void Pure_MoveCharacter(const FVector2D Axis);

public:
	// move axis of the character
	FVector2D pMoveAxis; 
};
