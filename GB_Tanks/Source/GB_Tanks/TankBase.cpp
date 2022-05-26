// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankBaseController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Components/ArrowComponent.h"


DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);

// Sets default values
ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh,FAttachmentTransformRules::KeepRelativeTransform);
}

void ATankBase::BeginPlay() {
	Super::BeginPlay();
	
	TankController = Cast<ATankBaseController>(GetController());
	SetupCannon(CannonClassMain);
}

// Called every frame
void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Controlling tank movement actions (forward/rotation)
	ATankBase::TankMovement(DeltaTime);
	ATankBase::TurretRotation();
}

// Called to bind functionality to input
void ATankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// tank movement funcs
void ATankBase::GetForwardAxis(float AxisValue) {
	_targetForwardAxisValue = AxisValue;
};
void ATankBase::GetRotationAxis(float AxisValue) {
	_targetRotationAxisValue = AxisValue;
};

// tank tick funcs

// tank movement tick func
void ATankBase::TankMovement(float DeltaTime) {
	FVector forwardVector = GetActorForwardVector();
	
	FVector movementVector = forwardVector * _targetForwardAxisValue * fMoveSpeed * DeltaTime;

	AddActorWorldOffset(movementVector, true);
	
	float fDeltaRotationZ = _targetRotationAxisValue * this->fBodyRotationSpeed * DeltaTime;
	FRotator DeltaRotation;

	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;
	DeltaRotation.Yaw = fDeltaRotationZ;

	AddActorWorldRotation(DeltaRotation, true);
};

void ATankBase::TurretRotation() {
	if (TankController) {
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), TurretFacetoLocation);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, fTurretRotationSpeed));
	}
}

void ATankBase::OnCannonPickup(TSubclassOf<ACannon> newCannonClass)
{
	if (CannonMain) {
		if (newCannonClass == CannonMain->GetClass()) {
			return;
		}
	}
	
	if (CannonAlt) {
		if (newCannonClass == CannonAlt->GetClass()) {
			return;
		}
		else {
			FActorSpawnParameters params;
			params.Instigator = this;
			params.Owner = this;
			ACannon* PickedCannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
			PickedCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			ActiveCannon->Destroy();

			if (ActiveCannon == CannonMain) {
				CannonMain = PickedCannon;
			}
			else {
				CannonAlt = PickedCannon;
			}

			ActiveCannon = PickedCannon;
		}
	}
	else {
		CannonAlt = DuplicateObject(CannonMain, NULL);
		CannonMain->Destroy();
		
		FActorSpawnParameters params;
		params.Instigator = this;
		params.Owner = this;
		ACannon* PickedCannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
		PickedCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		CannonMain = PickedCannon;
		ActiveCannon = PickedCannon;
	}
}

void ATankBase::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (ActiveCannon)
	{
		ActiveCannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	ActiveCannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	ActiveCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	if (!CannonMain) {
		CannonMain = ActiveCannon;
	}
}

void ATankBase::Fire()
{
	if (ActiveCannon)
	{
		ActiveCannon->Fire();
	}
}

void ATankBase::FireSpecial()
{
	if (ActiveCannon)
	{
		ActiveCannon->FireSpecial();
	}
}


ACannon* ATankBase::GetActiveCannon() {
	return ActiveCannon;
}

void ATankBase::SwitchCannon() {
	if (CannonAlt && CannonMain) {
		isMainCannonSelected = !isMainCannonSelected;

		if (isMainCannonSelected) {
			ActiveCannon->Destroy();
			ActiveCannon = CannonMain;
		}
		else {
			ActiveCannon->Destroy();
			ActiveCannon = CannonAlt;
		}

		GEngine->AddOnScreenDebugMessage(13, 0.5f, FColor::Yellow, "Switch another canon");
		SetupCannon(ActiveCannon->GetClass());
	}
}