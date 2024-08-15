// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
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
	UMGGameInstance();

	
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

	// find a hosted game and if found join session
	UFUNCTION(BlueprintCallable,Category="Sessions")
	void FindAndJoinSession();

	// start a lobby game if one exists
	UFUNCTION(BlueprintCallable,Category="Sessions")
	void StartLobbyGameSkirmish();


	// function for starting lobby game, to play the skyscraper map
	UFUNCTION(BlueprintCallable,Category="Sessions")
	void StartLobbyGameSkyscraper();

	
	UFUNCTION(BlueprintCallable,Category="Session")
	void EndLobbyGame();

	// keyword only allows this class and derived/ child classes to run functions
    protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success,const FString& error);

	UFUNCTION(BlueprintImplementableEvent,Category="Sessions")
	void OnSessionCreateComplete( bool sucess);

	UFUNCTION(BlueprintImplementableEvent,Category="Sessions")
	void OnSessionJoinComplete(bool success);
	
	// only this class can run private
    private:
	// runs when EOS login completes
	void EOSLoginComplete(int32  LocalUserNum,bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	// run when the session create function completes
	void SessionCreateComplete(FName SessionName, bool bWasSuccessful);


	// runs when a find session function completes
	void SessionFindComplete(bool bWasSuccessful);

	// runs on session join complete
	void SessionJoinComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// when find sessions is run, this will fill with found sessions
	TSharedPtr<FOnlineSessionSearch> FoundSessions;

	
};
