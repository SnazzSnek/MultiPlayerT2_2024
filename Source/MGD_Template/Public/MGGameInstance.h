// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

// keyword allows other classes to run this function
public:
	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();



	// keyword only allows this class and derived/ child classes to run functions
    protected:

	
	// only this class can run private
    private:
	
	
};
