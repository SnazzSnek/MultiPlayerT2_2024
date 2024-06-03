// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDPlayerController.h"

void AMGDPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	PureOnRepPosses(GetPawn());
}

void AMGDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PureOnRepPosses(InPawn);



	
}