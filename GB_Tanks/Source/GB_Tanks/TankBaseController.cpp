// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBaseController.h"

ATankBaseController::ATankBaseController() {

}

void ATankBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this,
		&ATankBaseController::MoveForward);

	InputComponent->BindAxis("RotateBody", this,
		&ATankBaseController::Rotate);

	InputComponent->BindAxis("RotateTurret", this,
		&ATankBaseController::RotateTurret);
	
	/*
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this,
		&ATankBaseController::MoveForward);
		*/
}

void ATankBaseController::BeginPlay()
{
	Super::BeginPlay();
	this->TankBase = Cast<ATankBase>(GetPawn());
}

// tank body control
void ATankBaseController::MoveForward(float AxisValue)
{
	this->TankBase->GetForwardAxis(AxisValue);
}
void ATankBaseController::Rotate(float AxisValue)
{
	this->TankBase->GetRotationAxis(AxisValue);
}

// turret control
void ATankBaseController::RotateTurret(float AxisValue)
{
	this->TankBase->GetTurretRotationAxis(AxisValue);
}
void ATankBaseController::CanonFire()
{
	this->TankBase->CanonFire();
}