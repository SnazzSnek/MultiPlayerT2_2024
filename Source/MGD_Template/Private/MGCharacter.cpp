// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMGCharacter::AMGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pRepPitch = 0.0f;
}

void AMGCharacter::Pure_MoveCharacter(const FVector2D Axis)
{
    // update the move axis
	pMoveAxis = Axis;

	// move character based on Y axis
	   AddMovementInput(GetActorRotation().Vector(),Axis.Y);

	// move character based on X axis	
	   AddMovementInput(FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y),Axis.X);

	
}

void AMGCharacter::Pure_RotateController(const FVector2D Axis)
{
	// Rotate controller yaw based on X axis
	AddControllerYawInput(Axis.X);

	// rotate controller pitch based on Y axis
	AddControllerPitchInput(-Axis.Y);

	// is pRepPitch 10 units difference from controllers pitch
	if (FMath::Abs(pRepPitch - GetControlRotation().Pitch) > 10.0f)
	{
		// are we the server?
		if (HasAuthority())
		{
			Multi_RepPitch(GetControlRotation().Pitch);
		}
		else
		{
			Server_RepPitch(GetControlRotation().Pitch);
		}
	}
	
}

void AMGCharacter::Server_RepPitch_Implementation(const float& Pitch)
{
    // run multicast to update all the clients
	Multi_RepPitch(Pitch);
}

void AMGCharacter::Multi_RepPitch_Implementation(const float& Pitch)
{
    // Update Pitch to Match the value
	pRepPitch = Pitch;
}
