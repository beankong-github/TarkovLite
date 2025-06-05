// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TarkovCharacter.h"
#include "EnhancedInputComponent.h"
#include "Weapon/WeaponBase.h"


void ATarkovCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATarkovCharacter::Fire);
	}

}

void ATarkovCharacter::EquipWeapon(TSubclassOf<AWeaponBase> WeaponToEquip, FName SocketName)
{
	if (!IsValid(WeaponToEquip.Get()))
	{
		UE_LOG(TarkovCharacter, Warning, TEXT("CurrentWeapon is not set for %s"), *GetNameSafe(this));
	}
	else
	{
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponToEquip);
		if (CurrentWeapon)
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->SetInstigator(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
			UE_LOG(TarkovCharacter, Log, TEXT("Weapon %s attached to character %s"), *GetNameSafe(CurrentWeapon), *GetNameSafe(this));
		}
		else
		{
			UE_LOG(TarkovCharacter, Error, TEXT("Failed to load weapon %s for character %s"), *WeaponToEquip.Get()->GetName(), *GetNameSafe(this));
		}
	}
}


void ATarkovCharacter::Fire(const FInputActionValue& Value)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->DoFire();
	}
	else
	{
		UE_LOG(TarkovCharacter, Warning, TEXT("CurrentWeapon is not set for %s"), *GetNameSafe(this));
	}
}
