// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

#define MGSESSION_NAME FName(TEXT("MGSESSION"))

void UMGGameInstance::Init()
{
	Super::Init();
	// this is the online subsystem
	// gives us access to all the online subsystem functions 
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	// if the oss ref returns null
	if (!ossRef)
		return;



	// this is the identity interface for EOS
	// we can get info about players acc from this interface
	// it also allows us to access authentication (login/logout)

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	// if the identity is null, exit the function

	if (!identityRef)
		return;

	// binding the login complete function to login complete, in the identity interface 
	identityRef->OnLoginCompleteDelegates->AddUObject(this, &UMGGameInstance::EOSLoginComplete);



	const IOnlineSessionPtr sessionRef = ossRef->GetSessionInterface();


	if (!sessionRef)
		return;

	sessionRef->OnCreateSessionCompleteDelegates.AddUObject(this, & UMGGameInstance::OnSessionCreateComplete);

	
}

void UMGGameInstance::LoginEOS()
{
	// this is the online subsystem
	// gives us access to all the online subsystem functions 
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

    // if the oss ref returns null
	if (!ossRef)
		return;



	// this is the identity interface for EOS
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

bool UMGGameInstance::IsLoggedIn() const
{
	// this is the online subsystem
	// gives us access to all the online subsystem functions 
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	// if the oss ref returns null
	if (!ossRef)
		return false;



	// this is the identity interface for EOS
	// we can get info about players acc from this interface
	// it also allows us to access authentication (login/logout)

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	// if the identity is null, exit the function

	if (!identityRef)
		return false;

	return identityRef->GetLoginStatus(0) == ELoginStatus::LoggedIn;
}

FString UMGGameInstance::GetDisplayName() const
{
	if (!IsLoggedIn())
		return FString(TEXT("Display"));

	// since logged in already checks that the interface exists we can skip a step straight to the identity
	const IOnlineIdentityPtr identityRef = Online::GetSubsystem(GetWorld())->GetIdentityInterface();

	return identityRef->GetPlayerNickname(0);
}

bool UMGGameInstance::IsInSession() const
{
	if(!IsLoggedIn())
		return false;

	
   // get the interface that interacts with sessions, so we can get session data
	const IOnlineSessionPtr sessionRef = Online::GetSubsystem(GetWorld())->GetSessionInterface();

	// make sure there is a session interface
	if (!sessionRef)
		return false;

	// get and locally store the session state
	EOnlineSessionState:: Type state = sessionRef->GetSessionState(MGSESSION_NAME) ;

	// if there is a session return true
	return state != EOnlineSessionState::NoSession;

	
	
}

void UMGGameInstance::HostGame(bool lan)
{
	// are we logged in
	if (!IsLoggedIn())
		return;

	// get session interface
	const IOnlineSessionPtr sessionRef =Online::GetSubsystem(GetWorld())->GetSessionInterface();

	if (!sessionRef)
		return;

	//define the settings of the session
	FOnlineSessionSettings settings;
	settings.NumPublicConnections = 4;
	settings.bIsLANMatch = lan;
	settings.bIsDedicated = false;
	settings.bAllowInvites = true;
	settings.bShouldAdvertise = true;
	settings.bUseLobbiesIfAvailable = true;
	settings.bUsesPresence = true;
	settings.Set(SEARCH_KEYWORDS, MGSESSION_NAME.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);


	// create the session using the settings and name we created
	sessionRef->CreateSession(0, MGSESSION_NAME, settings);
}

void UMGGameInstance::EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                       const FString& Error)
{
	OnLoginComplete(bWasSuccessful, Error);
}

void UMGGameInstance::SessionCreateComplete(FName SessionName, bool bWasSuccessful)
{
	EnableListenServer(true);
	OnSessionCreateComplete(bWasSuccessful);
}
