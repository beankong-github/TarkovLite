// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::DoFire()
{
    if(!IsValid(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon %s has no valid owner!"), *GetNameSafe(this));
		return;
	}
    
	FVector Start, Direction, End;
	UCameraComponent* CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
    if (CameraComponent != nullptr)
    {
       Start = GetOwner()->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
       Direction = GetOwner()->FindComponentByClass<UCameraComponent>()->GetForwardVector();
    }
    End = Start + Direction * 10000.f;
    
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (bHit)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
    }

    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 1.0f);
}

