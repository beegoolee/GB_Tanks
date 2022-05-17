// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

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
}


// Called every frame
void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Controlling tank movement actions (forward/rotation)
	ATankBase::TankMovement();
	ATankBase::TurretRotation();
}



// Called to bind functionality to input
void ATankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// tank movement funcs
void ATankBase::GetForwardAxis(float AxisValue) {
	this->_targetForwardAxisValue = AxisValue;
};
void ATankBase::GetRotationAxis(float AxisValue) {
	this->_targetRotationAxisValue = AxisValue;
};

// tank combat funcs
void ATankBase::CanonFire() {
	// shooting start point + location for particle FX spawn + linetrace start location
	FVector canonFireStartLoc = TurretMesh->GetSocketLocation("BarrelEnd");

	// shooting target point, end target for linetrace
	FVector canonFireEndLoc = canonFireStartLoc + (TurretMesh->GetForwardVector() * this->fShootingRange);

};

void ATankBase::GetTurretRotationAxis(float AxisValue) {
	this->_targetTurretRotationAxisValue = AxisValue;
};


// tank tick funcs

// tank movement tick func
void ATankBase::TankMovement() {
	FVector forwardVector = GetActorForwardVector();
	
	FVector movementVector = forwardVector * this->_targetForwardAxisValue * this->fMoveSpeed;

	AddActorWorldOffset(movementVector, true);
	
	float fDeltaRotationZ = _targetRotationAxisValue * this->fBodyRotationSpeed;
	FRotator DeltaRotation;

	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;
	DeltaRotation.Yaw = fDeltaRotationZ;

	AddActorWorldRotation(DeltaRotation, true);
};

// turret control tick func
void ATankBase::TurretRotation() {
	float fDeltaRotationZ = _targetTurretRotationAxisValue * this->fBodyRotationSpeed;
	FRotator DeltaRotation;

	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;
	DeltaRotation.Yaw = fDeltaRotationZ;

	TurretMesh->AddLocalRotation(DeltaRotation);
};