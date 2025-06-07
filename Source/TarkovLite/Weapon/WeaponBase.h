// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class ABaseCharacter;
class USoundBase;
UCLASS()
class TARKOVLITE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Recoil")
	float RecoilHorizontalDegree;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Recoil")
	float RecoilVerticalDegree;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* MuzzleFX;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Effects")
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Effects")
	USoundBase* FireSound;

public:	
	// Sets default values for this actor's properties
	AWeaponBase();

public:
	void DoFire();
	
private:
	FVector GetFireStartLocation() const;
	FVector GetFireDirection() const;
	void ApplyRecoil(FVector& Direction);

	void PlayMuzzleEffect();
};
