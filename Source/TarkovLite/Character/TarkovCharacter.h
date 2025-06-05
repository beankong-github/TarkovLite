// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "TarkovCharacter.generated.h"

class AWeaponBase;
class ATarkovCharacter;
/**
 * 
 */
UCLASS()
class TARKOVLITE_API ATarkovCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	AWeaponBase* CurrentWeapon;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;


protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for input */
	void Fire(const FInputActionValue& Value);

public:
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(TSubclassOf<AWeaponBase> WeaponToEquip, FName SocketName);

};
