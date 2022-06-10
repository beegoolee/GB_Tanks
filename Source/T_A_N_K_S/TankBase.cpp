#include "TankBase.h"

ATankBase::ATankBase()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodySMesh);
	SpringArm->bDoCollisionTest = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	/*
	AimCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Aim Camera"));
	Camera->SetupAttachment(BodySMesh);
	*/
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankBase::AddCameraRotY(float rAxis)
{
	float newPitch = SpringArm->GetRelativeRotation().Pitch +  rAxis;
	newPitch = FMath::Clamp(newPitch, -89.0f, 89.0f);

	SpringArm->SetRelativeRotation(FRotator(newPitch, SpringArm->GetRelativeRotation().Yaw, 0));
}

void ATankBase::AddCameraRotX(float rAxis)
{
	float newYaw = SpringArm->GetRelativeRotation().Yaw + rAxis;

	SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeRotation().Pitch, newYaw, 0));
}

void ATankBase::SwitchCamera() {
	// тогглим аимную и обычную камеры TODO
}
