// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TARKOVLITE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:	
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	


	
};
