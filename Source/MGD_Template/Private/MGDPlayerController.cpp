// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDPlayerController.h"

void AMGDPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	Pure_OnRepPosess(GetPawn());
}

void AMGDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Pure_OnRepPosess(InPawn);
		
}