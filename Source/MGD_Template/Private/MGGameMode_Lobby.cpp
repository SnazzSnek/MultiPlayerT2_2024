// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameMode_Lobby.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMGGameMode_Lobby::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

    // initialise an empty local array of player starts
	TArray<AActor*> PlayerStartArray;
	
	// get all the player starts and add them into the player start variable 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(),PlayerStartArray);

	
    // if there are no player starts stop function
	if (PlayerStartArray.IsEmpty())
		return;

	// looping through all of the actors in the array
	for (AActor* actorRef : PlayerStartArray)
	{
		// testing to make sure the actor is a player start
		if (APlayerStart* psRef = Cast<APlayerStart>(actorRef))
		{
			// assigning an index depending on the tag of the player start
			int playerStartIndex = 1;
			
			// assigning an index depending on the following 
		
			if(psRef->PlayerStartTag == FName("Player2"))
				playerStartIndex = 2;
			else if(psRef->PlayerStartTag == FName("Player3"))
				playerStartIndex = 3;
			else if (psRef->PlayerStartTag == FName("Player4"))
				playerStartIndex = 4;
             		
			// getting the number of players in a game, 
			int32 numPlayers = UGameplayStatics:: GetNumPlayerStates(GetWorld());

			// checking  if player start tag matches this player
			if(playerStartIndex == numPlayers)
			{
				// restart the player and assign it to correct player start
				RestartPlayerAtPlayerStart(NewPlayer, psRef);
				break;
			}

			
		}
	}
	

	
}
