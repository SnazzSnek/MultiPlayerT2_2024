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
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();

	UFUNCTION(BlueprintPure,Category="Login")
	bool IsLoggedIn() const;

	UFUNCTION(BlueprintPure,Category="User")
	FString GetDisplayName() const;

	

	UFUNCTION(BlueprintPure,Category="Sessions")
	bool IsInSession() const;

// hosts a game using EOS, currently only LAN capable 
	UFUNCTION(BlueprintCallable,Category="Sessions")
	void HostGame(bool lan = true);



	// keyword only allows this class and derived/ child classes to run functions
    protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success,const FString& error);

	UFUNCTION(BlueprintImplementableEvent,Category="Session")
	void OnSessionCreateComplete(FName SessionName, bool bWasSucessful);
	
	
	// only this class can run private
    private:
	// runs when EOS login completes
	void EOSLoginComplete(int32  LocalUserNum,bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	void SessionCreateComplete(FName SessionName, bool bWasSuccesful);
	
	
};
