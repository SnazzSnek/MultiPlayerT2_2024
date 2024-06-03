// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MGDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API AMGDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnRep_Pawn() override;

	virtual void OnPossess(APawn* InPawn) override;


protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Replication")
	void PureOnRepPosses(APawn* PossesedPawn);
	
};
