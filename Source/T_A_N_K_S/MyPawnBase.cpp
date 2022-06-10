#include "MyPawnBase.h"


AMyPawnBase::AMyPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UArrowComponent>(TEXT("Root"));
	RootComponent = Root;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collider"));

	BodySMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pawn body"));
	WreckedBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wrecked body"));
	WreckedBodyMesh->SetVisibility(false);

	BodySMesh->AttachToComponent(HitCollider, FAttachmentTransformRules::KeepRelativeTransform);
	WreckedBodyMesh->AttachToComponent(HitCollider, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider->ResetRelativeTransform();

	
	PrimaryShootVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PrimaryShootVFX"));
	PrimaryShootVFX->SetupAttachment(RootComponent);

	PrimaryShootSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("PrimaryShootSFX"));
	PrimaryShootSFX->SetupAttachment(RootComponent);

	AltShootVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AltShootVFX"));
	AltShootVFX->SetupAttachment(RootComponent);

	AltShootSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("AltShootSFX"));
	AltShootSFX->SetupAttachment(RootComponent);
}


void AMyPawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);
	Rotate(DeltaTime);
}

void AMyPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPawnBase::PrimaryFire()
{
	if (bPrimaryCanShoot) {
		bPrimaryCanShoot = false;

		FVector ShotSpawnLoc = BodySMesh->GetSocketLocation("BarrelEnd");
		FRotator ShotSpawnRot = BodySMesh->GetSocketRotation("BarrelEnd");
		FActorSpawnParameters params;
		params.Owner = this;

		SetAmmoPoints(-1, 0);
		/*
		PrimaryShootVFX->ActivateSystem();
		PrimaryShootSFX->Play(); */

		ACanonShot* canonShot = GetWorld()->SpawnActor<ACanonShot>(CanonShotClass, params);
		canonShot->SetActorLocation(ShotSpawnLoc);
		canonShot->SetActorRotation(ShotSpawnRot);

		canonShot->Start();

		if (iPrimaryAmmoCurrent > 0) {
			GetWorld()->GetTimerManager().SetTimer(
				_primaryReloadTimerHandle,
				this,
				&AMyPawnBase::ReloadPrimary,
				fPrimaryFireReloadTime,
				false,
				fPrimaryFireReloadTime
			);
		}
	}
}

void AMyPawnBase::ReloadAlt() {
	bAltCanShoot = true;
}

void AMyPawnBase::ReloadPrimary() {
	bPrimaryCanShoot = true;
}

void AMyPawnBase::AltFire(float axis)
{
	if (bAltCanShoot && bHaveAltFireMode) {
		bAltCanShoot = false;

		FVector ShotSpawnLoc = BodySMesh->GetSocketLocation("AltBarrelEnd");
		FRotator ShotSpawnRot = BodySMesh->GetSocketRotation("AltBarrelEnd");
		FActorSpawnParameters params;
		params.Owner = this;

		SetAmmoPoints(0, -1);
		/*
		AltShootVFX->ActivateSystem();
		AltShootSFX->Play();*/

		ACanonShot* altShot = GetWorld()->SpawnActor<ACanonShot>(AltShotClass, params);
		altShot->SetActorLocation(ShotSpawnLoc);
		altShot->SetActorRotation(ShotSpawnRot);

		altShot->Start();

		if (iAltAmmoCurrent > 0) {
			FTimerHandle _reloadTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				_reloadTimerHandle,
				this,
				&AMyPawnBase::ReloadAlt,
				fAltFireReloadTime,
				false,
				fAltFireReloadTime
			);
		}
	}
}

void AMyPawnBase::SetForwardAxis(float fAxis)
{
	float InterpolationKey = 0.1f;
	
	switch((int)fAxis) {
		case 1:
		case -1:
			InterpolationKey = 0.005f;
			break;
		default:
		case 0:
			InterpolationKey = 0.01f;
			break;
	}

	fCurrentMoveAxis = FMath::Lerp(fCurrentMoveAxis, fAxis, InterpolationKey);
}

void AMyPawnBase::MoveForward(float DeltaTime)
{
	float fAccelerationSpeed = (fCurrentMoveAxis < 0)? fMaxMovementSpeed_backward : fMaxMovementSpeed_forward;

	float CurrentSpeed = fCurrentMoveAxis * fAccelerationSpeed / DeltaTime;
	FVector NewLoc = HitCollider->GetComponentLocation() + HitCollider->GetForwardVector() * CurrentSpeed;
	HitCollider->SetWorldLocation(NewLoc);
}

void AMyPawnBase::SetRotationAxis(float rAxis)
{
	float InterpolationKey = 0.025f;

	fCurrentRotationAxis = FMath::Lerp(fCurrentRotationAxis, rAxis, InterpolationKey);
}

void AMyPawnBase::Rotate(float DeltaTime)
{
	float fDeltaRot = fCurrentRotationAxis * fMaxRotationSpeed / DeltaTime;
	HitCollider->AddLocalRotation(FRotator(0, fDeltaRot, 0));
}

void AMyPawnBase::TakeHit(float DamageValue)
{
	fCurrentHP -= DamageValue;
	fCurrentHP = FMath::Clamp(fCurrentHP, 0.0f, fMaxHP);

	if (fCurrentHP == 0.0f) {
		Death();
	}
}

void AMyPawnBase::Death()
{
	BodySMesh->SetVisibility(false);
	WreckedBodyMesh->SetVisibility(true);
}

void AMyPawnBase::AddTurretRotation(float rAxis) {
	fTurretRotationZ += rAxis * fTurretRotSpeed;
}

float AMyPawnBase::GetTurretRotationZ()
{
	return fTurretRotationZ;
}

void AMyPawnBase::SelectShot_1()
{
	CanonShotClass = ShotType_1;
	LoadNewShotType();
}

void AMyPawnBase::SelectShot_2()
{
	CanonShotClass = ShotType_2;
	LoadNewShotType();
}

void AMyPawnBase::SelectShot_3()
{
	CanonShotClass = ShotType_3;
	LoadNewShotType();
}

void AMyPawnBase::LoadNewShotType() {
	bPrimaryCanShoot = false;

	GetWorld()->GetTimerManager().ClearTimer(_primaryReloadTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		_primaryReloadTimerHandle,
		this,
		&AMyPawnBase::ReloadPrimary,
		fPrimaryFireReloadTime,
		false,
		fPrimaryFireReloadTime
	);
}

void AMyPawnBase::SetAmmoPoints(int iPrimaryAmmoAdded, int iAltAmmoAdded)
{
	iPrimaryAmmoCurrent += iPrimaryAmmoAdded;
	iPrimaryAmmoCurrent = FMath::Clamp(iPrimaryAmmoCurrent, 0, iMaxPrimaryAmmo);

	iAltAmmoCurrent += iAltAmmoAdded;
	iAltAmmoCurrent = FMath::Clamp(iAltAmmoCurrent, 0, iMaxAltAmmo);


	UE_LOG(LogTemp, Warning, TEXT("Primary cannon ammo points is %d, alt cannon ammo points is %d. "), iPrimaryAmmoCurrent, iAltAmmoCurrent);
}
