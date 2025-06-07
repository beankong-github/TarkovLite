// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/BaseCharacter.h"
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void AWeaponBase::DoFire()
{
    if(!IsValid(GetOwner()))
	{
		UE_LOG(TarkovWeapon, Warning, TEXT("Weapon %s has no valid owner!"), *GetNameSafe(this));
		return;
	}
    
	// Debug line trace to simulate firing
	FVector Start, Direction, End;
	
    Start = GetFireStartLocation();
    Direction = GetFireDirection();
	ApplyRecoil(Direction);

    End = Start + Direction * 10000.f;
    
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (bHit)
    {
        UE_LOG(TarkovWeapon, Log, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
    }

    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 1.0f);

	PlayMuzzleEffect();
}

FVector AWeaponBase::GetFireStartLocation() const
{
	if (ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
	{
		if (UCameraComponent* CameraComponent = OwnerCharacter->GetFollowCamera())
		{
			return CameraComponent->GetComponentLocation();
		}
	}

	if (WeaponMesh->DoesSocketExist("Muzzle"))
	{
		return WeaponMesh->GetSocketLocation("Muzzle");
	}

	UE_LOG(TarkovWeapon, Warning, TEXT("Weapon %s has no valid fire start location!"), *GetNameSafe(this));
	return FVector();

}

FVector AWeaponBase::GetFireDirection() const
{
	if (ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
	{
		if (UCameraComponent* CameraComponent = OwnerCharacter->GetFollowCamera())
		{
			return CameraComponent->GetForwardVector();
		}
	}

	if (WeaponMesh->DoesSocketExist("Muzzle"))
	{
		return WeaponMesh->GetSocketRotation("Muzzle").Vector();
	}


	UE_LOG(TarkovWeapon, Warning, TEXT("Weapon %s has no valid fire direction!"), *GetNameSafe(this));
    return FVector();
}

void AWeaponBase::ApplyRecoil(FVector& Direction)
{
	Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(RecoilHorizontalDegree), FMath::DegreesToRadians(RecoilVerticalDegree));
}

void AWeaponBase::PlayMuzzleEffect()
{	
	// Spawn muzzle effects
	if (MuzzleFX)
	{
		MuzzleFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMesh, TEXT("Muzzle"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	}
	// Play fire sound
	if (FireSound)
	{
		UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, TEXT("Muzzle"));
	}
}

