// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDCharacter.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMGDCharacter::AMGDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMGDCharacter::Pure_MoveCharacter(const FVector2D Axis)
{
    // update the move axis
	pMoveAxis = Axis;

	// move character based on Y axis
	   AddMovementInput(GetControlRotation().Vector(),Axis.Y);

	// move character based on X axis
	   AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y),Axis.X);

	
}

	
	
	

