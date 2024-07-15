// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MGGameMode_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API AMGGameMode_Lobby : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
};
