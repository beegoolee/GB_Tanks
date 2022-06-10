#include "MyTankController.h"

AMyTankController::AMyTankController()
{
}

void AMyTankController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("Forward", this,&AMyTankController::MoveForward);
	InputComponent->BindAxis("Rotation", this,&AMyTankController::Rotate);
	InputComponent->BindAxis("TurretRotation", this,&AMyTankController::RotateTurret);

	InputComponent->BindAxis("AltFire", this, &AMyTankController::AltFire);

	InputComponent->BindAxis("CameraRotationX", this, &AMyTankController::RotateCameraX);
	InputComponent->BindAxis("CameraRotationY", this, &AMyTankController::RotateCameraY);


	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyTankController::Fire);

	InputComponent->BindAction("SelectShot_1", IE_Pressed, this, &AMyTankController::SelectShot_1);
	InputComponent->BindAction("SelectShot_2", IE_Pressed, this, &AMyTankController::SelectShot_2);
	InputComponent->BindAction("SelectShot_3", IE_Pressed, this, &AMyTankController::SelectShot_3);
}

void AMyTankController::SelectShot_1()
{
	TankPawn->SelectShot_1();
}
void AMyTankController::SelectShot_2()
{
	TankPawn->SelectShot_2();
}
void AMyTankController::SelectShot_3()
{
	TankPawn->SelectShot_3();
}

void AMyTankController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankBase>(GetPawn());
}

void AMyTankController::MoveForward(float AxisValue)
{
	TankPawn->SetForwardAxis(AxisValue);
}

void AMyTankController::Rotate(float AxisValue)
{

	TankPawn->SetRotationAxis(AxisValue);
}

void AMyTankController::RotateCameraX(float AxisValue) {
	TankPawn->AddCameraRotX(AxisValue);
}

void AMyTankController::RotateCameraY(float AxisValue) {
	TankPawn->AddCameraRotY(AxisValue);
}

void AMyTankController::RotateTurret(float AxisValue)
{
	TankPawn->AddTurretRotation(AxisValue);
}



void AMyTankController::Fire()
{
	TankPawn->PrimaryFire();
}

void AMyTankController::AltFire(float AxisValue)
{
	if(AxisValue > 0)
		TankPawn->AltFire(AxisValue);
}