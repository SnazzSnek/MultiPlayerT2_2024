// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UMGGameInstance::LoginEOS()
{
	// this is the online subsystem
	// gives us access to all of the online subsystem functions 
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

    // if the oss ref returns null
	if (!ossRef)
		return;



	// this is the indentity interface for EOS
	// we can get info about players acc from this interface
	// it also allows us to access authentication (login/logout)

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	// if the identity is null, exit the function

	if (!identityRef)
		return;


	// this sets up the type of account credentials that the login will expect
	// this account portal is a login portal that opens when you try to login
	FOnlineAccountCredentials accCreds;
	accCreds.Id = FString();
	accCreds.Token = FString();
	accCreds.Type = FString(TEXT("accountportal"));

	// run the login portal
	identityRef->Login(0,accCreds);
}
