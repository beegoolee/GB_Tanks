// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBaseController.h"
#include "DrawDebugHelpers.h"

ATankBaseController::ATankBaseController() {
	bShowMouseCursor = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ATankBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this,
		&ATankBaseController::MoveForward);

	InputComponent->BindAxis("RotateBody", this,
		&ATankBaseController::Rotate);
	
	InputComponent->BindAction("Fire", IE_Pressed, this,
		&ATankBaseController::Fire);

	InputComponent->BindAction("FireSpecial", IE_Pressed, this,
		&ATankBaseController::FireSpecial);

	InputComponent->BindAction("SwitchCannon", IE_Pressed, this,
		&ATankBaseController::SwitchCannon);
}

void ATankBaseController::BeginPlay()
{
	Super::BeginPlay();
	this->TankBase = Cast<ATankBase>(GetPawn());
}

// tank body control
void ATankBaseController::MoveForward(float AxisValue)
{
	forwardCurrentAxis = FMath::Lerp(forwardCurrentAxis, AxisValue, TankBase->forwardMoveInterpKey);
	TankBase->GetForwardAxis(forwardCurrentAxis);
}
void ATankBaseController::Rotate(float AxisValue)
{
	rotateCurrentAxis = FMath::Lerp(rotateCurrentAxis, AxisValue, TankBase->rotateInterpKey);
	TankBase->GetRotationAxis(rotateCurrentAxis);
}

void ATankBaseController::SetMousePosition() {
	if (GetWorld()) {
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit) {
			MousePosition = Hit.ImpactPoint;
		}

		FVector TankPosition = TankBase->GetActorLocation();

		MousePosition.Z = TankPosition.Z;

		FVector dir = MousePosition - TankPosition;

		dir.Normalize();

		MousePosition = TankPosition + dir*10000;

		TankBase->TurretFacetoLocation = MousePosition;
	}
}

void ATankBaseController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	SetMousePosition();
}

void ATankBaseController::Fire()
{
	TankBase->Fire();
}

void ATankBaseController::FireSpecial()
{
	TankBase->FireSpecial();
}

void ATankBaseController::SwitchCannon()
{
	TankBase->SwitchCannon();
}