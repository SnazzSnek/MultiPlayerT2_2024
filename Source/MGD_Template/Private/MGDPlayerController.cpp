// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDPlayerController.h"

void AMGDPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	UE_LOG(LogTemp, Warning, TEXT("On Posses"))

	Pure_OnRepPosess(GetPawn());
}

void AMGDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);	

	if(HasAuthority())
		Pure_OnRepPosess(InPawn);
		
}