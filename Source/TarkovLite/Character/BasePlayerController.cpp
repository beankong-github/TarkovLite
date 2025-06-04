// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"


void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
